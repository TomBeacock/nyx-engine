#include "renderer_impl.h"

#include "exception.h"
#include "nyx/log.h"
#include "nyx/string/string_util.h"
#include "nyx/system/window.h"
#include "system/msw/window_impl.h"

#include <d3dcompiler.h>

#include <array>

using Microsoft::WRL::ComPtr;

namespace Nyx::D3D12 {
struct Vertex {
    Nyx::Math::Float3 position;
    Nyx::Math::Float3 color;
};

void get_hardware_adapter(IDXGIFactory4 *factory, IDXGIAdapter1 **adapter);

RendererImpl::RendererImpl()
    : viewport(),
      scissor_rect(),
      use_warp_device(false),
      rtv_desc_size(),
      vertex_buffer_view(),
      index_buffer_view(),
      constant_buffer_data(),
      cbv_data_begin(nullptr),
      frame_index(),
      fence_event(),
      fence_values()
{
    this->constant_buffer_data.model = Math::Float4x4::identity;
    this->constant_buffer_data.projection = Math::Float4x4::identity;
}

RendererImpl::~RendererImpl()
{
    wait_for_gpu();
    CloseHandle(this->fence_event);
}

void RendererImpl::init(const Window &window)
{
    Nat32 width = window.get_client_width();
    Nat32 height = window.get_client_height();

    this->viewport = {
        0.0f,
        0.0f,
        static_cast<float>(width),
        static_cast<float>(height),
        0.0f,
        1.0f};
    this->scissor_rect = {
        0, 0, static_cast<long>(width), static_cast<long>(height)};
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    this->constant_buffer_data.projection =
        Math::orthographic(4.0f * aspect, 4.0f, -1.0f, 1.0f);

    const Nyx::MSW::WindowImpl &window_impl =
        dynamic_cast<const Nyx::MSW::WindowImpl &>(window.get_impl());
    load_pipeline(width, height, window_impl.get_hwnd());
    load_assets();
}

void RendererImpl::update()
{
    static Math::Quaternion rotation{};
    rotation = Math::rotate(rotation, 0.1f, Math::Float3::up);
    this->constant_buffer_data.model = Math::transformation(
        Math::Float3(0.0f, 0.0f, 0.5f), rotation, Math::Float3::one);
    memcpy(
        this->cbv_data_begin,
        &this->constant_buffer_data,
        sizeof(this->constant_buffer_data));
}

void RendererImpl::render()
{
    record_command_list();
    std::array<ID3D12CommandList *, 1> command_lists = {
        this->command_list.Get(),
    };
    this->command_queue->ExecuteCommandLists(
        static_cast<UINT>(command_lists.size()), command_lists.data());
    DX::ThrowIfFailed(this->swap_chain->Present(1, 0));
    move_to_next_frame();
}

void RendererImpl::resize(Nat32 width, Nat32 height)
{
    wait_for_gpu();

    for (UINT i = 0; i < frame_count; i++) {
        this->render_targets[i].Reset();
        this->fence_values[i] = this->fence_values[this->frame_index];
    }

    DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
    this->swap_chain->GetDesc(&swap_chain_desc);
    this->swap_chain->ResizeBuffers(
        this->frame_count,
        static_cast<UINT>(width),
        static_cast<UINT>(height),
        swap_chain_desc.BufferDesc.Format,
        swap_chain_desc.Flags);

    this->frame_index = this->swap_chain->GetCurrentBackBufferIndex();

    this->viewport = {
        0.0f,
        0.0f,
        static_cast<float>(width),
        static_cast<float>(height),
        0.0f,
        1.0f};
    this->scissor_rect = {
        0, 0, static_cast<long>(width), static_cast<long>(height)};
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    this->constant_buffer_data.projection =
        Math::orthographic(4.0f * aspect, 4.0f, -1.0f, 1.0f);

    load_size_dependent_resources();
}

void RendererImpl::load_pipeline(Nat32 width, Nat32 height, HWND handle)
{
    // Enable debug layer
#if defined(NYX_DEBUG)
    {
        ComPtr<ID3D12Debug> debug_controller;
        if (SUCCEEDED(
                D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)))) {
            debug_controller->EnableDebugLayer();
        }
    }
#endif

    ComPtr<IDXGIFactory4> factory;
    DX::ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

    // Create device
    {
        if (this->use_warp_device) {
            ComPtr<IDXGIAdapter> warp_adapter;
            DX::ThrowIfFailed(
                factory->EnumWarpAdapter(IID_PPV_ARGS(&warp_adapter)));
            DX::ThrowIfFailed(D3D12CreateDevice(
                warp_adapter.Get(),
                D3D_FEATURE_LEVEL_11_0,
                IID_PPV_ARGS(&this->device)));
        } else {
            ComPtr<IDXGIAdapter1> hardware_adapter;
            get_hardware_adapter(factory.Get(), &hardware_adapter);
            DX::ThrowIfFailed(D3D12CreateDevice(
                hardware_adapter.Get(),
                D3D_FEATURE_LEVEL_11_0,
                IID_PPV_ARGS(&this->device)));
        }
    }

    // Create command queue
    {
        D3D12_COMMAND_QUEUE_DESC queue_desc{
            .Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
            .Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
            .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
        };
        DX::ThrowIfFailed(this->device->CreateCommandQueue(
            &queue_desc, IID_PPV_ARGS(&this->command_queue)));
    }

    // Create swap chain
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc{
            .BufferDesc{
                .Width = width,
                .Height = height,
                .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
            },
            .SampleDesc{
                .Count = 1,
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = this->frame_count,
            .OutputWindow = handle,
            .Windowed = TRUE,
            .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
        };

        ComPtr<IDXGISwapChain> swap_chain;
        DX::ThrowIfFailed(factory->CreateSwapChain(
            this->command_queue.Get(), &swap_chain_desc, &swap_chain));
        DX::ThrowIfFailed(swap_chain.As(&this->swap_chain));

        // Don't support fullscreen transitions
        DX::ThrowIfFailed(
            factory->MakeWindowAssociation(handle, DXGI_MWA_NO_ALT_ENTER));

        this->frame_index = this->swap_chain->GetCurrentBackBufferIndex();
    }

    // Create descriptor heaps
    {
        // Render target view heap
        D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc{
            .Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
            .NumDescriptors = this->frame_count,
            .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
        };
        DX::ThrowIfFailed(this->device->CreateDescriptorHeap(
            &rtv_heap_desc, IID_PPV_ARGS(&this->rtv_heap)));
        this->rtv_desc_size = this->device->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        // Constant buffer descriptor heap
        D3D12_DESCRIPTOR_HEAP_DESC cbv_heap_desc{
            .Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
            .NumDescriptors = 1,
            .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
        };
        DX::ThrowIfFailed(this->device->CreateDescriptorHeap(
            &cbv_heap_desc, IID_PPV_ARGS(&this->cbv_heap)));
    }

    // Create command allocators
    {
        for (UINT i = 0; i < this->frame_count; i++) {
            DX::ThrowIfFailed(this->device->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT,
                IID_PPV_ARGS(&this->command_allocators[i])));
        }
    }
}

void RendererImpl::load_assets()
{
    // Create root signature
    {
        std::array<CD3DX12_DESCRIPTOR_RANGE1, 1> ranges{};
        ranges[0].Init(
            D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
            1,
            0,
            0,
            D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
        std::array<CD3DX12_ROOT_PARAMETER1, 1> root_params{};
        root_params[0].InitAsDescriptorTable(
            static_cast<UINT>(ranges.size()),
            ranges.data(),
            D3D12_SHADER_VISIBILITY_VERTEX);

        D3D12_ROOT_SIGNATURE_FLAGS root_signature_flags =
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC root_signature_desc{};
        root_signature_desc.Init_1_1(
            static_cast<UINT>(root_params.size()),
            root_params.data(),
            0,
            nullptr,
            root_signature_flags);

        ComPtr<ID3DBlob> signature;
        ComPtr<ID3DBlob> error;
        DX::ThrowIfFailed(D3D12SerializeVersionedRootSignature(
            &root_signature_desc, &signature, &error));
        DX::ThrowIfFailed(this->device->CreateRootSignature(
            0,
            signature->GetBufferPointer(),
            signature->GetBufferSize(),
            IID_PPV_ARGS(&this->root_signature)));
    }

    // Create pipeline state
    {
        // Compile shaders
        ComPtr<ID3DBlob> vertex_shader;
        ComPtr<ID3DBlob> pixel_shader;

        LPCWSTR path = L"" NYX_ENGINE_RES_DIR "shaders/default.hlsl";

#if defined(NYX_DEBUG) || defined(NYX_DEBUG_INFO_ONLY)
        UINT compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
        ComPtr<ID3DBlob> error;
        if (FAILED(D3DCompileFromFile(
                path,
                nullptr,
                nullptr,
                "VSMain",
                "vs_5_0",
                compile_flags,
                0,
                &vertex_shader,
                &error))) {
            NYX_ENGINE_ERROR(
                "{}", static_cast<char *>(error->GetBufferPointer()));
            throw std::exception();
        }
        if (FAILED(D3DCompileFromFile(
                path,
                nullptr,
                nullptr,
                "PSMain",
                "ps_5_0",
                compile_flags,
                0,
                &pixel_shader,
                &error))) {
            NYX_ENGINE_ERROR(
                "{}", static_cast<char *>(error->GetBufferPointer()));
            throw std::exception();
        }
#else
        DX::ThrowIfFailed(D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "VSMain",
            "vs_5_0",
            0,
            0,
            &vertex_shader,
            nullptr));
        DX::ThrowIfFailed(D3DCompileFromFile(
            path,
            nullptr,
            nullptr,
            "PSMain",
            "ps_5_0",
            0,
            0,
            &pixel_shader,
            nullptr));
#endif

        // Define vertex input layout
        std::array<D3D12_INPUT_ELEMENT_DESC, 2> input_element_descs = {
            D3D12_INPUT_ELEMENT_DESC{
                .SemanticName = "POSITION",
                .SemanticIndex = 0,
                .Format = DXGI_FORMAT_R32G32B32_FLOAT,
                .InputSlot = 0,
                .AlignedByteOffset = 0,
                .InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
                .InstanceDataStepRate = 0,
            },
            D3D12_INPUT_ELEMENT_DESC{
                .SemanticName = "COLOR",
                .SemanticIndex = 0,
                .Format = DXGI_FORMAT_R32G32B32_FLOAT,
                .InputSlot = 0,
                .AlignedByteOffset = 12,
                .InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
                .InstanceDataStepRate = 0,
            },
        };

        // Create pipeline state object (PSO)
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc{
            .pRootSignature = this->root_signature.Get(),
            .VS =
                D3D12_SHADER_BYTECODE{
                    .pShaderBytecode = reinterpret_cast<UINT8 *>(
                        vertex_shader->GetBufferPointer()),
                    .BytecodeLength = vertex_shader->GetBufferSize(),
                },
            .PS =
                D3D12_SHADER_BYTECODE{
                    .pShaderBytecode = reinterpret_cast<UINT8 *>(
                        pixel_shader->GetBufferPointer()),
                    .BytecodeLength = pixel_shader->GetBufferSize(),
                },
            .BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT),
            .SampleMask = UINT_MAX,
            .RasterizerState =
                D3D12_RASTERIZER_DESC{
                    .FillMode = D3D12_FILL_MODE_SOLID,
                    .CullMode = D3D12_CULL_MODE_BACK,
                    .FrontCounterClockwise = TRUE,
                    .DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
                    .DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
                    .SlopeScaledDepthBias =
                        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
                    .DepthClipEnable = TRUE,
                    .MultisampleEnable = FALSE,
                    .AntialiasedLineEnable = FALSE,
                    .ForcedSampleCount = 0,
                    .ConservativeRaster =
                        D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
                },
            .DepthStencilState =
                D3D12_DEPTH_STENCIL_DESC{
                    .DepthEnable = FALSE,
                    .StencilEnable = FALSE,
                },
            .InputLayout =
                D3D12_INPUT_LAYOUT_DESC{
                    .pInputElementDescs = input_element_descs.data(),
                    .NumElements =
                        static_cast<UINT>(input_element_descs.size()),
                },
            .PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
            .NumRenderTargets = 1,
            .RTVFormats = {DXGI_FORMAT_R8G8B8A8_UNORM},
            .SampleDesc =
                DXGI_SAMPLE_DESC{
                    .Count = 1,
                },
        };
        DX::ThrowIfFailed(this->device->CreateGraphicsPipelineState(
            &pso_desc, IID_PPV_ARGS(&this->pipeline_state)));
    }

    // Create command list
    {
        ComPtr<ID3D12CommandAllocator> command_allocator =
            this->command_allocators[this->frame_index];
        DX::ThrowIfFailed(this->device->CreateCommandList(
            0,
            D3D12_COMMAND_LIST_TYPE_DIRECT,
            command_allocator.Get(),
            this->pipeline_state.Get(),
            IID_PPV_ARGS(&this->command_list)));
        DX::ThrowIfFailed(this->command_list->Close());
    }

    load_size_dependent_resources();

    // Create vertex buffer
    {
        std::array<Vertex, 4> vertex_data = {
            Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            Vertex{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            Vertex{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},
            Vertex{{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        };
        const size_t vertex_data_size = vertex_data.size() * sizeof(Vertex);

        // TODO: Replace with more efficient heap upload method
        CD3DX12_HEAP_PROPERTIES heap_props(D3D12_HEAP_TYPE_UPLOAD);
        auto res_desc =
            CD3DX12_RESOURCE_DESC::Buffer(static_cast<UINT>(vertex_data_size));
        DX::ThrowIfFailed(this->device->CreateCommittedResource(
            &heap_props,
            D3D12_HEAP_FLAG_NONE,
            &res_desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&this->vertex_buffer)));

        // Copy vertex data to vertex buffer
        UINT8 *vertex_data_begin = nullptr;
        CD3DX12_RANGE read_range(0, 0);
        DX::ThrowIfFailed(this->vertex_buffer->Map(
            0, &read_range, reinterpret_cast<void **>(&vertex_data_begin)));
        memcpy(vertex_data_begin, vertex_data.data(), vertex_data_size);
        this->vertex_buffer->Unmap(0, nullptr);

        // Initialize vertex buffer view
        this->vertex_buffer_view.BufferLocation =
            this->vertex_buffer->GetGPUVirtualAddress();
        this->vertex_buffer_view.StrideInBytes =
            static_cast<UINT>(sizeof(Vertex));
        this->vertex_buffer_view.SizeInBytes =
            static_cast<UINT>(vertex_data_size);
    }

    // Create index buffer
    {
        std::array<UINT, 6> index_data = {0, 1, 2, 0, 2, 3};
        const size_t index_data_size = index_data.size() * sizeof(UINT);

        // TODO: Replace with more efficient heap upload method
        CD3DX12_HEAP_PROPERTIES heap_props(D3D12_HEAP_TYPE_UPLOAD);
        auto res_desc =
            CD3DX12_RESOURCE_DESC::Buffer(static_cast<UINT>(index_data_size));
        DX::ThrowIfFailed(this->device->CreateCommittedResource(
            &heap_props,
            D3D12_HEAP_FLAG_NONE,
            &res_desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&this->index_buffer)));

        // Copy index data to index buffer
        UINT8 *index_data_begin = nullptr;
        CD3DX12_RANGE read_range(0, 0);
        DX::ThrowIfFailed(this->index_buffer->Map(
            0, &read_range, reinterpret_cast<void **>(&index_data_begin)));
        memcpy(index_data_begin, index_data.data(), index_data_size);
        this->index_buffer->Unmap(0, nullptr);

        // Initialize index buffer view
        this->index_buffer_view.BufferLocation =
            this->index_buffer->GetGPUVirtualAddress();
        this->index_buffer_view.Format = DXGI_FORMAT_R32_UINT;
        this->index_buffer_view.SizeInBytes =
            static_cast<UINT>(index_data_size);
    }

    // Create constant buffer
    {
        const UINT buffer_size = sizeof(ConstantBufferData);
        CD3DX12_HEAP_PROPERTIES heap_props(D3D12_HEAP_TYPE_UPLOAD);
        auto res_desc = CD3DX12_RESOURCE_DESC::Buffer(buffer_size);
        DX::ThrowIfFailed(this->device->CreateCommittedResource(
            &heap_props,
            D3D12_HEAP_FLAG_NONE,
            &res_desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&this->constant_buffer)));

        D3D12_CONSTANT_BUFFER_VIEW_DESC cbv_desc = {
            .BufferLocation = this->constant_buffer->GetGPUVirtualAddress(),
            .SizeInBytes = buffer_size,
        };
        this->device->CreateConstantBufferView(
            &cbv_desc, this->cbv_heap->GetCPUDescriptorHandleForHeapStart());

        CD3DX12_RANGE read_range(0, 0);
        DX::ThrowIfFailed(this->constant_buffer->Map(
            0, &read_range, reinterpret_cast<void **>(&this->cbv_data_begin)));
        memcpy(
            this->cbv_data_begin,
            &this->constant_buffer_data,
            sizeof(this->constant_buffer_data));
    }

    // Create synchronization objects
    {
        UINT64 &fence_value = this->fence_values[this->frame_index];
        DX::ThrowIfFailed(this->device->CreateFence(
            fence_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->fence)));
        fence_value++;

        // Create an event handle
        this->fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (this->fence_event == nullptr) {
            DX::ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }

        // Wait for the command list to execute
        wait_for_gpu();
    }
}

void RendererImpl::load_size_dependent_resources()
{
    // Create frame resources
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_heap_handle(
            this->rtv_heap->GetCPUDescriptorHandleForHeapStart());

        for (UINT i = 0; i < this->frame_count; i++) {
            DX::ThrowIfFailed(this->swap_chain->GetBuffer(
                i, IID_PPV_ARGS(&this->render_targets[i])));
            this->device->CreateRenderTargetView(
                this->render_targets[i].Get(), nullptr, rtv_heap_handle);
            rtv_heap_handle.Offset(1, this->rtv_desc_size);
        }
    }
}

void RendererImpl::record_command_list()
{
    DX::ThrowIfFailed(this->command_allocators[this->frame_index]->Reset());
    DX::ThrowIfFailed(this->command_list->Reset(
        this->command_allocators[this->frame_index].Get(),
        this->pipeline_state.Get()));

    // Set necessary state.
    this->command_list->SetGraphicsRootSignature(this->root_signature.Get());
    this->command_list->RSSetViewports(1, &this->viewport);
    this->command_list->RSSetScissorRects(1, &this->scissor_rect);
    std::array<ID3D12DescriptorHeap *, 1> heaps = {cbv_heap.Get()};
    this->command_list->SetDescriptorHeaps(
        static_cast<UINT>(heaps.size()), heaps.data());
    this->command_list->SetGraphicsRootDescriptorTable(
        0, this->cbv_heap->GetGPUDescriptorHandleForHeapStart());

    // Indicate that the back buffer will be used as a render target
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        this->render_targets[this->frame_index].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);
    this->command_list->ResourceBarrier(1, &barrier);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(
        this->rtv_heap->GetCPUDescriptorHandleForHeapStart(),
        this->frame_index,
        this->rtv_desc_size);
    this->command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

    // Record commands
    const float clear_color[] = {0.0f, 0.0f, 0.0f, 1.0f};
    this->command_list->ClearRenderTargetView(
        rtv_handle, clear_color, 0, nullptr);
    this->command_list->IASetPrimitiveTopology(
        D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->command_list->IASetVertexBuffers(0, 1, &this->vertex_buffer_view);
    this->command_list->IASetIndexBuffer(&this->index_buffer_view);
    this->command_list->DrawIndexedInstanced(6, 1, 0, 0, 0);

    // Indicate that the back buffer will now be used to present
    barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        this->render_targets[this->frame_index].Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT);
    this->command_list->ResourceBarrier(1, &barrier);

    DX::ThrowIfFailed(this->command_list->Close());
}

void RendererImpl::wait_for_gpu()
{
    const UINT64 fence = this->fence_values[this->frame_index];
    DX::ThrowIfFailed(this->command_queue->Signal(this->fence.Get(), fence));

    DX::ThrowIfFailed(this->fence->SetEventOnCompletion(
        this->fence_values[this->frame_index], this->fence_event));
    WaitForSingleObjectEx(this->fence_event, INFINITE, FALSE);

    this->fence_values[this->frame_index]++;
}

void RendererImpl::move_to_next_frame()
{
    const UINT64 fence = this->fence_values[this->frame_index];
    DX::ThrowIfFailed(this->command_queue->Signal(this->fence.Get(), fence));

    this->frame_index = this->swap_chain->GetCurrentBackBufferIndex();

    if (this->fence->GetCompletedValue() <
        this->fence_values[this->frame_index]) {
        DX::ThrowIfFailed(this->fence->SetEventOnCompletion(
            this->fence_values[this->frame_index], this->fence_event));
        WaitForSingleObjectEx(this->fence_event, INFINITE, FALSE);
    }
    this->fence_values[this->frame_index] = fence + 1;
}

void get_hardware_adapter(IDXGIFactory4 *factory, IDXGIAdapter1 **adapter)
{
    *adapter = nullptr;
    for (UINT i = 0;; i++) {
        // Check for remaining adapters
        IDXGIAdapter1 *found_adapter = nullptr;
        if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(i, &found_adapter)) {
            break;
        }

        // Check to see if the adapter supports Direct3D 12
        if (SUCCEEDED(D3D12CreateDevice(
                found_adapter,
                D3D_FEATURE_LEVEL_11_0,
                _uuidof(ID3D12Device),
                nullptr))) {
            *adapter = found_adapter;
#if defined(NYX_DEBUG) || defined(NYX_DEBUG_INFO_ONLY)
            DXGI_ADAPTER_DESC adapter_desc;
            found_adapter->GetDesc(&adapter_desc);
            NYX_ENGINE_INFO(
                "GPU Description:\nName: {}\nVendor ID: {}\nVRAM: {}",
                reinterpret_cast<const char *>(
                    wstring_to_utf8(std::wstring(adapter_desc.Description))
                        .data()),
                adapter_desc.VendorId,
                adapter_desc.DedicatedVideoMemory);
#endif
            return;
        }
        found_adapter->Release();
    }
}
}  // namespace Nyx::D3D12
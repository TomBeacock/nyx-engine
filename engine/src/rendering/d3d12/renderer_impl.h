#pragma once

#include "nyx/math.h"
#include "nyx/types.h"
#include "rendering/renderer_impl.h"

// clang-format off
#include <directx/d3dx12.h>
// clang-format on

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace Nyx {
class Window;
}

namespace Nyx::D3D12 {
class RendererImpl : public Nyx::RendererImpl {
  private:
    struct ConstantBufferData {
        Nyx::Math::Float4x4 model;
        Nyx::Math::Float4x4 projection;
        float padding[32];
    };
    static_assert(
        (sizeof(ConstantBufferData) % 256) == 0,
        "Constant buffer must be 256-byte aligned");

  public:
    RendererImpl();
    ~RendererImpl();

    virtual void init(const Window &window) override;
    virtual void update() override;
    virtual void render() override;
    virtual void resize(Nat32 width, Nat32 height) override;

  private:
    void load_pipeline(Nat32 width, Nat32 height, HWND handle);
    void load_assets();
    void load_size_dependent_resources();
    void record_command_list();
    void wait_for_gpu();
    void move_to_next_frame();

  private:
    static const UINT frame_count = 2;

  private:
    // Pipeline objects
    D3D12_VIEWPORT viewport;
    D3D12_RECT scissor_rect;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> swap_chain;
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    Microsoft::WRL::ComPtr<ID3D12Resource> render_targets[frame_count];
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator>
        command_allocators[frame_count];
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> root_signature;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> cbv_heap;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipeline_state;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
    bool use_warp_device;
    UINT rtv_desc_size;

    // App resources
    Microsoft::WRL::ComPtr<ID3D12Resource> vertex_buffer;
    Microsoft::WRL::ComPtr<ID3D12Resource> index_buffer;
    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
    D3D12_INDEX_BUFFER_VIEW index_buffer_view;
    Microsoft::WRL::ComPtr<ID3D12Resource> constant_buffer;
    ConstantBufferData constant_buffer_data;
    UINT8 *cbv_data_begin;

    // Synchronization objects
    UINT frame_index;
    HANDLE fence_event;
    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    UINT64 fence_values[frame_count];
};
}  // namespace Nyx::D3D12
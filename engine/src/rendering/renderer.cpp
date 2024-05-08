#include "renderer.h"

#include "nyx/system/window.h"

#ifdef NYX_GRAPHICS_D3D12
#include "d3d12/renderer_impl.h"
using RendererImplType = Nyx::D3D12::RendererImpl;
#else
#error Unsupported graphics api
#endif

namespace Nyx {
Renderer::Renderer() : renderer_impl(std::make_unique<RendererImplType>()) {}

Renderer::~Renderer() {}

void Renderer::init(const Window &window)
{
    this->renderer_impl->init(window);
}

void Renderer::render()
{
    this->renderer_impl->render();
}
}  // namespace Nyx
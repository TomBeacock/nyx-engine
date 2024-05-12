#pragma once

#include <memory>

namespace Nyx {
class Window;
class RendererImpl;
}  // namespace Nyx

namespace Nyx {
class Renderer {
  public:
    Renderer();
    ~Renderer();

    /**
     * @brief Initialize the renderer.
     */
    void init(const Window &window);

    /**
     * @brief Update the renderer state.
     */
    void update();

    /**
     * @brief Render the next frame.
     */
    void render();

  private:
    std::unique_ptr<RendererImpl> renderer_impl;
};
}  // namespace Nyx
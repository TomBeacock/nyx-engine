#pragma once

#include "nyx/types.h"

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

    /**
     * @brief Resize the renderer's output.
     * @param width New width.
     * @param height New height.
     */
    void resize(Nat32 width, Nat32 height);

  private:
    std::unique_ptr<RendererImpl> renderer_impl;
};
}  // namespace Nyx
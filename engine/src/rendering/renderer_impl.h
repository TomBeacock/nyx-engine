#pragma once

#include "nyx/types.h"

#include <cstdint>

namespace Nyx {
class Window;
}

namespace Nyx {
class RendererImpl {
  public:
    virtual void init(const Window &window) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    /**
     * @brief Resize the renderer's output.
     * @param width New width.
     * @param height New height.
     */
    virtual void resize(Nat32 width, Nat32 height) = 0;

  protected:
    RendererImpl();
};
}  // namespace Nyx
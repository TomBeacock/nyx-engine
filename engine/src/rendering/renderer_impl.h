#pragma once

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

  protected:
    RendererImpl();
};
}  // namespace Nyx
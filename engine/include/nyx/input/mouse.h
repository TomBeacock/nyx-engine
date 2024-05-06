#pragma once

namespace Nyx {
class Mouse {
  public:
    static bool isCursorVisible() { return Mouse::visible; }
    static void setCursorVisible(bool visible) { Mouse::visible = visible; }
    static bool isCursorLocked() { return Mouse::locked; }
    static void setCursorLocked(bool locked) { Mouse::locked = locked; }

  private:
    static bool visible;
    static bool locked;
};
}  // namespace Nyx
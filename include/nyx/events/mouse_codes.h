#pragma once

#include <cstdint>
#include <ostream>

namespace Nyx {
enum class MouseButton : uint8_t {
    None = 0,
    Left = 1,
    Right = 2,
    Middle = 3,
    X1 = 4,
    X2 = 5,
};

inline std::ostream &operator<<(std::ostream &os, MouseButton mouse_button)
{
    switch (mouse_button) {
        case MouseButton::Left: return os << "Mouse Button: Left";
        case MouseButton::Right: return os << "Mouse Button: Right";
        case MouseButton::Middle: return os << "Mouse Button: Middle";
        case MouseButton::X1: return os << "Mouse Button: X1";
        case MouseButton::X2: return os << "Mouse Button: X2";
    }
    return os << "Mouse Button: Unknown";
}
}  // namespace Nyx
#pragma once

#include <cstdint>
#include <format>
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

inline std::string to_string(MouseButton mouse_button)
{
    switch (mouse_button) {
        case Nyx::MouseButton::Left: return "Left";
        case Nyx::MouseButton::Right: return "Right";
        case Nyx::MouseButton::Middle: return "Middle";
        case Nyx::MouseButton::X1: return "X1";
        case Nyx::MouseButton::X2: return "X2";
    }
    return "Unknown";
}

inline std::ostream &operator<<(std::ostream &os, MouseButton mouse_button)
{
    return os << to_string(mouse_button);
}

}  // namespace Nyx

template <>
struct std::formatter<Nyx::MouseButton> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(
        const Nyx::MouseButton &mouse_button, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", Nyx::to_string(mouse_button));
    }
};
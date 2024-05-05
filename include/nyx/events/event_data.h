#pragma once

#include "key_codes.h"
#include "mouse_codes.h"
#include "nyx/math.h"

namespace Nyx {
struct KeyEventData {
    KeyCode key_code;
    ScanCode scan_code;

    KeyEventData(KeyCode key_code, ScanCode scan_code)
        : key_code(key_code), scan_code(scan_code)
    {}
};

struct MouseButtonEventData {
    MouseButton mouse_button;
    Math::Int2 position;

    MouseButtonEventData(MouseButton mouse_button, const Math::Int2 &position)
        : mouse_button(mouse_button), position(position)
    {}
};

struct MouseWheelEventData {
    Math::Float2 delta;

    MouseWheelEventData(const Math::Float2 &delta) : delta(delta) {}
};

struct MouseMotionEventData {
    Math::Float2 position;
    Math::Float2 delta;

    MouseMotionEventData(
        const Math::Float2 &position, const Math::Float2 &delta)
        : position(position), delta(delta)
    {}
};
}  // namespace Nyx
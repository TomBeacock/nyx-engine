#pragma once

#include "msw.h"

#include <cstdint>

namespace Nyx {
enum class KeyCode : uint16_t;
enum class ScanCode : uint16_t;
enum class MouseButton : uint8_t;
}  // namespace Nyx

namespace Nyx::MSW {
Nyx::KeyCode translate_key_code(USHORT key_code);
Nyx::ScanCode translate_scan_code(USHORT scan_code);
Nyx::MouseButton translate_mouse_button(USHORT mouse_button);
}  // namespace Nyx::MSW
#pragma once

#include <cstdint>

namespace Nyx {
/// Natural number of system wide precision
using Nat = unsigned int;
/// Natural number of 8-bit precision
using Nat8 = uint8_t;
/// Natural number of 16-bit precision
using Nat16 = uint16_t;
/// Natural number of 32-bit precision
using Nat32 = uint32_t;
/// Natural number of 64-bit precision
using Nat64 = uint64_t;

/// Integer number of system wide precision
using Int = int;
/// Integer number of 8-bit precision
using Int8 = int8_t;
/// Integer number of 16-bit precision
using Int16 = int16_t;
/// Integer number of 32-bit precision
using Int32 = int32_t;
/// Integer number of 64-bit precision
using Int64 = int64_t;

#ifndef NYX_USE_DOUBLE_PRECISION
/// Floating-point number of project defined precision
using Float = float;
#else
/// Floating-point number of project defined precision
using Float = double
#endif
/// Floating-point number of 32-bit precision
using Float32 = float;
/// Floating-point number of 64-bit precision
using Float64 = double;
/// Floating-point number of 128-bit precision
using Float128 = long double;

/// Character of 8-bit precision
using Char8 = char8_t;
/// Character of 16-bit precision
using Char16 = char16_t;
/// Character of 32-bit precision
using Char32 = char32_t;
}  // namespace Nyx
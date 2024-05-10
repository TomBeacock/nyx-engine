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
/// Real number of project defined precision
using Real = float;
#else
/// Real number of project defined precision
using Real = double
#endif
/// Real number of 32-bit precision
using Real32 = float;
/// Real number of 64-bit precision
using Real64 = double;
/// Real number of 128-bit precision
using Real128 = long double;

/// Character of 8-bit precision
using Char8 = char8_t;
/// Character of 16-bit precision
using Char16 = char16_t;
/// Character of 32-bit precision
using Char32 = char32_t;
}  // namespace Nyx
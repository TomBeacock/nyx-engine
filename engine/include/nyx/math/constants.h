#pragma once

#include <limits>
#include <numbers>

namespace Nyx::Math {
using std::numbers::e;
using std::numbers::egamma;
using std::numbers::inv_pi;
using std::numbers::inv_sqrt3;
using std::numbers::inv_sqrtpi;
using std::numbers::ln10;
using std::numbers::ln2;
using std::numbers::log10e;
using std::numbers::log2e;
using std::numbers::phi;
using std::numbers::pi;
using std::numbers::sqrt2;
using std::numbers::sqrt3;
constexpr inline double epsilon = std::numeric_limits<double>::epsilon();
}  // namespace Nyx::Math
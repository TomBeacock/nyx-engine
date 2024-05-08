#pragma once

#include <string>

namespace Nyx::MSW {
std::wstring utf8_to_wstring(const std::u8string &str);
}  // namespace Nyx::MSW
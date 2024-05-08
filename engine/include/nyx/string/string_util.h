#pragma once

#include <string>

namespace Nyx {
/**
 * Converts a utf8 string to wide string
 *
 * @param str Utf8 string
 *
 * @return Wide string
 */
std::wstring utf8_to_wstring(const std::u8string &str);

/**
 * Converts a wide string to utf8 string
 *
 * @param str Wide string
 *
 * @return Utf8 string
 */
std::u8string wstring_to_utf8(const std::wstring &str);
}  // namespace Nyx
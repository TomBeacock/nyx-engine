#include "string_util.h"

#include <cuchar>

std::wstring Nyx::MSW::utf8_to_wstring(const std::u8string &str)
{
    std::wstring result;
    for (auto it = str.begin(); it != str.end();) {
        if ((*it & 0x80) == 0) {
            result += static_cast<wchar_t>(*it++);
        } else if ((*it & 0xE0) == 0xC0) {
            result += static_cast<wchar_t>(*it++ & 0x1F) << 6 |
                      static_cast<wchar_t>(*it++ & 0x3F);
        } else if ((*it & 0xF0) == 0xE0) {
            result += static_cast<wchar_t>(*it++ & 0x0F) << 12 |
                      static_cast<wchar_t>(*it++ & 0x3F) << 6 |
                      static_cast<wchar_t>(*it++ & 0x3F);
        } else {
            wchar_t c[2]{0xD800, 0xD800};
            c[0] |= static_cast<wchar_t>(*it++ & 0x07) << 8 |
                    static_cast<wchar_t>(*it++ & 0x3F) << 2 |
                    static_cast<wchar_t>(*it & 0x3F) >> 4;
            c[0] |= static_cast<wchar_t>(*it++ & 0x0F) << 6 |
                    static_cast<wchar_t>(*it++ & 0x3F);
            result += c;
        }
    }
    return result;
}

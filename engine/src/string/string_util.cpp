#include "nyx/string/string_util.h"

std::wstring Nyx::utf8_to_wstring(const std::u8string &str)
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
            wchar_t c[3]{0xD800, 0xDC00, '\0'};
            c[0] |= static_cast<wchar_t>(*it++ & 0x07) << 8 |
                    static_cast<wchar_t>(*it++ & 0x3F) << 2 |
                    static_cast<wchar_t>(*it & 0x3F) >> 4;
            c[1] |= static_cast<wchar_t>(*it++ & 0x0F) << 6 |
                    static_cast<wchar_t>(*it++ & 0x3F);
            result += c;
        }
    }
    return result;
}

std::u8string Nyx::wstring_to_utf8(const std::wstring &str)
{
    std::u8string result;
    for (auto it = str.begin(); it != str.end();) {
        char32_t code_point = 0;
        if ((*it & 0xFC00) == 0xD800) {
            code_point |= (*it++ & 0x03FF) << 10 | (*it++ & 0x03FF);
        } else {
            code_point |= *it++;
        }
        if ((code_point & 0xFFFFFF80) == 0) {
            result += static_cast<char8_t>(code_point);
        } else if ((code_point & 0xFFFFF800) == 0) {
            result += 0xC0 + static_cast<char8_t>(code_point >> 6);
            result += 0x80 + static_cast<char8_t>(code_point & 0x3F);
        } else if ((code_point & 0xFFFF0000) == 0) {
            result += 0xD0 + static_cast<char8_t>(code_point >> 12);
            result += 0x80 + static_cast<char8_t>(code_point >> 6 & 0x3F);
            result += 0x80 + static_cast<char8_t>(code_point & 0x3F);
        } else {
            result += 0xF0 + static_cast<char8_t>(code_point >> 18);
            result += 0x80 + static_cast<char8_t>(code_point >> 12 & 0x3F);
            result += 0x80 + static_cast<char8_t>(code_point >> 6 & 0x3F);
            result += 0x80 + static_cast<char8_t>(code_point & 0x3F);
        }
    }
    return result;
}

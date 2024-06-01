#include "key_codes.h"

namespace Nyx {
inline std::string to_string(KeyCode key_code)
{
    return std::format("{}", key_code);
}

inline std::string to_string(ScanCode scan_code)
{
    return std::format("{}", scan_code);
}

inline std::ostream &operator<<(std::ostream &os, KeyCode key_code)
{
    return os << to_string(key_code);
}

inline std::ostream &operator<<(std::ostream &os, ScanCode scan_code)
{
    return os << to_string(scan_code);
}
}  // namespace Nyx
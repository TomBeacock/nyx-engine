#include "event.h"

namespace Nyx {
template <typename T>
inline Event::Event(const T &data)
{
    static_assert(is_event_type<T>, "T must be a subtype of Nyx::Event");
    if constexpr (is_event_type<T>) {
        this->data = data;
    }
}

template <typename T>
bool Event::is() const
{
    static_assert(is_event_type<T>, "T must be a subtype of Nyx::Event");
    if constexpr (is_event_type<T>) {
        return std::holds_alternative<T>(this->data);
    }
}

template <typename T>
const T *Event::get_if() const
{
    static_assert(is_event_type<T>, "T must be a subtype of Nyx::Event");
    if constexpr (is_event_type<T>) {
        return std::get_if<T>(&this->data);
    }
}

inline Event::operator bool() const
{
    return !is<Empty>();
}
}  // namespace Nyx
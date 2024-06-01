#pragma once

namespace Nyx::Math {
template <typename T>
struct QuaternionT;

template <size_t L, typename T>
struct VectorT;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
T roll(const QuaternionT<T> &q);

template <typename T>
T pitch(const QuaternionT<T> &q);

template <typename T>
T yaw(const QuaternionT<T> &q);

template <typename T>
VectorT<3, T> to_euler_angles(const QuaternionT<T> &q);

template <typename T>
QuaternionT<T> rotate(
    const QuaternionT<T> &q,
    const T &angle,
    const VectorT<3, T> &axis);

template <size_t L, typename T>
constexpr std::string to_string(const QuaternionT<T> &vq);

template <size_t L, typename T>
inline std::ostream &operator<<(std::ostream &os, const QuaternionT<T> &q);
}  // namespace Nyx::Math

template <typename T>
struct std::formatter<Nyx::Math::QuaternionT<T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const Nyx::Math::QuaternionT<T> &q, std::format_context &ctx)
        const
    {
        return std::format_to(ctx.out(), "[{},{},{},{}]", q.x, q.y, q.z, q.w);
    }
};

#include "quaternion_func.inl"
#pragma once

#include <ostream>
#include <string>

namespace Nyx::Math {
template <size_t L, typename T>
struct VectorT;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <size_t L, typename T>
constexpr T angle(const VectorT<L, T> &v1, const VectorT<L, T> &v2);

template <size_t L, typename T>
constexpr T distance(const VectorT<L, T> &v1, const VectorT<L, T> &v2);

template <size_t L, typename T>
constexpr T dot(const VectorT<L, T> &v1, const VectorT<L, T> &v2);

template <size_t L, typename T>
constexpr VectorT<L, T> lerp(
    const VectorT<L, T> &v1,
    const VectorT<L, T> &v2,
    float t);

template <size_t L, typename T>
constexpr T magnitude(const VectorT<L, T> &v);

template <size_t L, typename T>
constexpr VectorT<L, T> normalize(const VectorT<L, T> &v);

template <size_t L, typename T>
constexpr VectorT<L, T> reflect(
    const VectorT<L, T> &v,
    const VectorT<L, T> &normal);

template <size_t L, typename T>
constexpr T sqr_magnitude(const VectorT<L, T> &v);

template <size_t L, typename T>
constexpr std::string to_string(const VectorT<L, T> &v);

template <size_t L, typename T>
inline std::ostream &operator<<(std::ostream &os, const VectorT<L, T> &v);
}  // namespace Nyx::Math

template <typename T>
struct std::formatter<Nyx::Math::VectorT<2, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const Nyx::Math::VectorT<2, T> &v, std::format_context &ctx)
        const
    {
        return std::format_to(ctx.out(), "[{},{}]", v.x, v.y);
    }
};

template <typename T>
struct std::formatter<Nyx::Math::VectorT<3, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const Nyx::Math::VectorT<3, T> &v, std::format_context &ctx)
        const
    {
        return std::format_to(ctx.out(), "[{},{},{}]", v.x, v.y, v.z);
    }
};

template <typename T>
struct std::formatter<Nyx::Math::VectorT<4, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const Nyx::Math::VectorT<4, T> &v, std::format_context &ctx)
        const
    {
        return std::format_to(ctx.out(), "[{},{},{},{}]", v.x, v.y, v.z, v.w);
    }
};

#include "vector_func.inl"
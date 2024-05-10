#include "common.h"
#include "trigonometric.h"
#include "vector_func.h"

#include <format>

namespace Nyx::Math {
template <typename T>
constexpr T angle(const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return acos(clamp(dot(v1, v2), static_cast<T>(-1), static_cast<T>(1)));
}

template <size_t L, typename T>
constexpr T distance(const VectorT<L, T> &v1, const VectorT<L, T> &v2)
{
    return magnitude(v2 - v1);
}

template <typename T>
constexpr T dot(const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
constexpr T dot(const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
constexpr T dot(const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <size_t L, typename T>
constexpr VectorT<L, T> lerp(
    const VectorT<L, T> &v1, const VectorT<L, T> &v2, float t)
{
    return v1 + (v2 - v1) * t;
}

template <size_t L, typename T>
constexpr T magnitude(const VectorT<L, T> &v)
{
    return static_cast<T>(std::sqrt(sqr_magnitude(v)));
}

template <size_t L, typename T>
constexpr VectorT<L, T> normalize(const VectorT<L, T> &v)
{
    return v / magnitude(v);
}

template <size_t L, typename T>
constexpr VectorT<L, T> reflect(
    const VectorT<L, T> &v, const VectorT<L, T> &normal)
{
    return v - normal * dot(v, normal) * static_cast<T>(2);
}

template <size_t L, typename T>
constexpr T sqr_magnitude(const VectorT<L, T> &v)
{
    return dot(v, v);
}

template <size_t L, typename T>
constexpr std::string to_string(const VectorT<L, T> &v)
{
    return std::format("{}", v);
}

template <size_t L, typename T>
std::ostream &operator<<(std::ostream &os, const VectorT<L, T> &v)
{
    return os << to_string(v);
}
}  // namespace Nyx::Math

template <typename T>
constexpr auto std::formatter<Nyx::Math::VectorT<2, T>>::parse(
    std::format_parse_context &ctx)
{
    return ctx.begin();
}

template <typename T>
auto std::formatter<Nyx::Math::VectorT<2, T>>::format(
    const Nyx::Math::VectorT<2, T> &v, std::format_context &ctx) const
{
    return std::format_to(ctx.out(), "[{},{}]", v.x, v.y);
}

template <typename T>
constexpr auto std::formatter<Nyx::Math::VectorT<3, T>>::parse(
    std::format_parse_context &ctx)
{
    return ctx.begin();
}

template <typename T>
auto std::formatter<Nyx::Math::VectorT<3, T>>::format(
    const Nyx::Math::VectorT<3, T> &v, std::format_context &ctx) const
{
    return std::format_to(ctx.out(), "[{},{},{}]", v.x, v.y, v.z);
}

template <typename T>
constexpr auto std::formatter<Nyx::Math::VectorT<4, T>>::parse(
    std::format_parse_context &ctx)
{
    return ctx.begin();
}

template <typename T>
auto std::formatter<Nyx::Math::VectorT<4, T>>::format(
    const Nyx::Math::VectorT<4, T> &v, std::format_context &ctx) const
{
    return std::format_to(ctx.out(), "[{},{},{},{}]", v.x, v.y, v.z, v.w);
}
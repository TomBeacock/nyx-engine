#pragma once

#include <ostream>
#include <string>

namespace Nyx::Math {
template <size_t L, typename T>
struct Vector;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <size_t L, typename T>
constexpr T angle(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
constexpr T distance(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
constexpr T dot(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
constexpr Vector<L, T> lerp(
    const Vector<L, T> &v1, const Vector<L, T> &v2, float t);

template <size_t L, typename T>
constexpr T magnitude(const Vector<L, T> &v);

template <size_t L, typename T>
constexpr Vector<L, T> normalize(const Vector<L, T> &v);

template <size_t L, typename T>
constexpr Vector<L, T> reflect(
    const Vector<L, T> &v, const Vector<L, T> &normal);

template <size_t L, typename T>
constexpr T sqr_magnitude(const Vector<L, T> &v);

template <size_t L, typename T>
constexpr std::string to_string(const Vector<L, T> &v);

template <size_t L, typename T>
std::ostream &operator<<(std::ostream &os, const Vector<L, T> &v);
}  // namespace Nyx::Math

template <typename T>
struct std::formatter<Nyx::Math::Vector<2, T>> {
    constexpr auto parse(std::format_parse_context &ctx);

    auto format(
        const Nyx::Math::Vector<2, T> &v, std::format_context &ctx) const;
};

template <typename T>
struct std::formatter<Nyx::Math::Vector<3, T>> {
    constexpr auto parse(std::format_parse_context &ctx);

    auto format(
        const Nyx::Math::Vector<3, T> &v, std::format_context &ctx) const;
};

template <typename T>
struct std::formatter<Nyx::Math::Vector<4, T>> {
    constexpr auto parse(std::format_parse_context &ctx);

    auto format(
        const Nyx::Math::Vector<4, T> &v, std::format_context &ctx) const;
};

#include "vector_func.inl"
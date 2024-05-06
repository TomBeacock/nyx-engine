#pragma once

#include <format>

namespace Nyx::Math {
template <size_t L, typename T>
struct Vector;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Float4 = Vector<4, float>;
using Double4 = Vector<4, double>;
using Int4 = Vector<4, int>;
using UInt4 = Vector<4, unsigned int>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct Vector<4, T> {
    T x, y, z, w;

    const static Vector<4, T> zero;
    const static Vector<4, T> one;

    Vector() = default;
    template <typename TX, typename TY, typename TZ, typename TW>
    Vector(TX x, TY y, TZ z, TW w);
    template <typename U>
    explicit Vector(U scalar);
    template <typename U>
    Vector(const Vector<2, U> &v);
    template <typename U>
    Vector(const Vector<3, U> &v);
    template <typename U>
    Vector(const Vector<4, U> &v);

    template <typename U>
    Vector<4, T> &operator=(U scalar);
    template <typename U>
    Vector<4, T> &operator=(const Vector<4, U> &v);
    template <typename U>
    Vector<4, T> &operator+=(U scalar);
    template <typename U>
    Vector<4, T> &operator+=(const Vector<4, U> &v);
    template <typename U>
    Vector<4, T> &operator-=(U scalar);
    template <typename U>
    Vector<4, T> &operator-=(const Vector<4, U> &v);
    template <typename U>
    Vector<4, T> &operator*=(U scalar);
    template <typename U>
    Vector<4, T> &operator*=(const Vector<4, U> &v);
    template <typename U>
    Vector<4, T> &operator/=(U scalar);
    template <typename U>
    Vector<4, T> &operator/=(const Vector<4, U> &v);

    T &operator[](size_t i);
    const T &operator[](size_t i) const;
};

template <typename T>
Vector<4, T> operator+(const Vector<4, T> &v);
template <typename T>
Vector<4, T> operator-(const Vector<4, T> &v);

template <typename T>
Vector<4, T> operator+(const Vector<4, T> &v, T scalar);
template <typename T>
Vector<4, T> operator+(T scalar, const Vector<4, T> &v);
template <typename T>
Vector<4, T> operator+(const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
Vector<4, T> operator-(const Vector<4, T> &v, T scalar);
template <typename T>
Vector<4, T> operator-(T scalar, const Vector<4, T> &v);
template <typename T>
Vector<4, T> operator-(const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
Vector<4, T> operator*(const Vector<4, T> &v, T scalar);
template <typename T>
Vector<4, T> operator*(T scalar, const Vector<4, T> &v);
template <typename T>
Vector<4, T> operator*(const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
Vector<4, T> operator/(const Vector<4, T> &v, T scalar);
template <typename T>
Vector<4, T> operator/(T scalar, const Vector<4, T> &v);
template <typename T>
Vector<4, T> operator/(const Vector<4, T> &v1, const Vector<4, T> &v2);

template <typename T>
bool operator==(const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
bool operator!=(const Vector<4, T> &v1, const Vector<4, T> &v2);

template <typename T>
struct std::formatter<Vector<4, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(
        const Nyx::Math::Vector<4, T> &v, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "[{},{},{},{}]", v.x, v.y, v.z, v.w);
    }
};
}  // namespace Nyx::Math

#include "vector4.inl"
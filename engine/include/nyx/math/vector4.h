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

    constexpr Vector() = default;
    template <typename TX, typename TY, typename TZ, typename TW>
    constexpr Vector(TX x, TY y, TZ z, TW w);
    template <typename U>
    constexpr explicit Vector(U scalar);
    template <typename U>
    constexpr Vector(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector(const Vector<3, U> &v);
    template <typename U>
    constexpr Vector(const Vector<4, U> &v);

    template <typename U>
    constexpr Vector<4, T> &operator=(U scalar);
    template <typename U>
    constexpr Vector<4, T> &operator=(const Vector<4, U> &v);
    template <typename U>
    constexpr Vector<4, T> &operator+=(U scalar);
    template <typename U>
    constexpr Vector<4, T> &operator+=(const Vector<4, U> &v);
    template <typename U>
    constexpr Vector<4, T> &operator-=(U scalar);
    template <typename U>
    constexpr Vector<4, T> &operator-=(const Vector<4, U> &v);
    template <typename U>
    constexpr Vector<4, T> &operator*=(U scalar);
    template <typename U>
    constexpr Vector<4, T> &operator*=(const Vector<4, U> &v);
    template <typename U>
    constexpr Vector<4, T> &operator/=(U scalar);
    template <typename U>
    constexpr Vector<4, T> &operator/=(const Vector<4, U> &v);

    constexpr T &operator[](size_t i);
    constexpr const T &operator[](size_t i) const;
};

template <typename T>
constexpr Vector<4, T> operator+(const Vector<4, T> &v);
template <typename T>
constexpr Vector<4, T> operator-(const Vector<4, T> &v);

template <typename T>
constexpr Vector<4, T> operator+(const Vector<4, T> &v, T scalar);
template <typename T>
constexpr Vector<4, T> operator+(T scalar, const Vector<4, T> &v);
template <typename T>
constexpr Vector<4, T> operator+(
    const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
constexpr Vector<4, T> operator-(const Vector<4, T> &v, T scalar);
template <typename T>
constexpr Vector<4, T> operator-(T scalar, const Vector<4, T> &v);
template <typename T>
constexpr Vector<4, T> operator-(
    const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
constexpr Vector<4, T> operator*(const Vector<4, T> &v, T scalar);
template <typename T>
constexpr Vector<4, T> operator*(T scalar, const Vector<4, T> &v);
template <typename T>
constexpr Vector<4, T> operator*(
    const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
constexpr Vector<4, T> operator/(const Vector<4, T> &v, T scalar);
template <typename T>
constexpr Vector<4, T> operator/(T scalar, const Vector<4, T> &v);
template <typename T>
constexpr Vector<4, T> operator/(
    const Vector<4, T> &v1, const Vector<4, T> &v2);

template <typename T>
constexpr bool operator==(const Vector<4, T> &v1, const Vector<4, T> &v2);
template <typename T>
constexpr bool operator!=(const Vector<4, T> &v1, const Vector<4, T> &v2);
}  // namespace Nyx::Math

#include "vector4.inl"
#pragma once

#include <format>

namespace Nyx::Math {
template <size_t L, typename T>
struct Vector;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Float2 = Vector<2, float>;
using Double2 = Vector<2, double>;
using Int2 = Vector<2, int>;
using UInt2 = Vector<2, unsigned int>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct Vector<2, T> {
    T x, y;

    const static Vector<2, T> zero;
    const static Vector<2, T> one;
    const static Vector<2, T> left;
    const static Vector<2, T> right;
    const static Vector<2, T> up;
    const static Vector<2, T> down;

    constexpr Vector() = default;
    template <typename TX, typename TY>
    constexpr Vector(TX x, TY y);
    template <typename U>
    constexpr explicit Vector(U scalar);
    template <typename U>
    constexpr Vector(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector(const Vector<3, U> &v);
    template <typename U>
    constexpr Vector(const Vector<4, U> &v);

    template <typename U>
    constexpr Vector<2, T> &operator=(U scalar);
    template <typename U>
    constexpr Vector<2, T> &operator=(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector<2, T> &operator+=(U scalar);
    template <typename U>
    constexpr Vector<2, T> &operator+=(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector<2, T> &operator-=(U scalar);
    template <typename U>
    constexpr Vector<2, T> &operator-=(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector<2, T> &operator*=(U scalar);
    template <typename U>
    constexpr Vector<2, T> &operator*=(const Vector<2, U> &v);
    template <typename U>
    constexpr Vector<2, T> &operator/=(U scalar);
    template <typename U>
    constexpr Vector<2, T> &operator/=(const Vector<2, U> &v);

    constexpr T &operator[](size_t i);
    constexpr const T &operator[](size_t i) const;
};

template <typename T>
constexpr Vector<2, T> operator+(const Vector<2, T> &v);
template <typename T>
constexpr Vector<2, T> operator-(const Vector<2, T> &v);

template <typename T>
constexpr Vector<2, T> operator+(const Vector<2, T> &v, T scalar);
template <typename T>
constexpr Vector<2, T> operator+(T scalar, const Vector<2, T> &v);
template <typename T>
constexpr Vector<2, T> operator+(
    const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
constexpr Vector<2, T> operator-(const Vector<2, T> &v, T scalar);
template <typename T>
constexpr Vector<2, T> operator-(T scalar, const Vector<2, T> &v);
template <typename T>
constexpr Vector<2, T> operator-(
    const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
constexpr Vector<2, T> operator*(const Vector<2, T> &v, T scalar);
template <typename T>
constexpr Vector<2, T> operator*(T scalar, const Vector<2, T> &v);
template <typename T>
constexpr Vector<2, T> operator*(
    const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
constexpr Vector<2, T> operator/(const Vector<2, T> &v, T scalar);
template <typename T>
constexpr Vector<2, T> operator/(T scalar, const Vector<2, T> &v);
template <typename T>
constexpr Vector<2, T> operator/(
    const Vector<2, T> &v1, const Vector<2, T> &v2);

template <typename T>
constexpr bool operator==(const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
constexpr bool operator!=(const Vector<2, T> &v1, const Vector<2, T> &v2);
}  // namespace Nyx::Math

#include "vector2.inl"
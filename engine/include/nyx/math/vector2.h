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

    Vector() = default;
    template <typename TX, typename TY>
    Vector(TX x, TY y);
    template <typename U>
    explicit Vector(U scalar);
    template <typename U>
    Vector(const Vector<2, U> &v);
    template <typename U>
    Vector(const Vector<3, U> &v);
    template <typename U>
    Vector(const Vector<4, U> &v);

    template <typename U>
    Vector<2, T> &operator=(U scalar);
    template <typename U>
    Vector<2, T> &operator=(const Vector<2, U> &v);
    template <typename U>
    Vector<2, T> &operator+=(U scalar);
    template <typename U>
    Vector<2, T> &operator+=(const Vector<2, U> &v);
    template <typename U>
    Vector<2, T> &operator-=(U scalar);
    template <typename U>
    Vector<2, T> &operator-=(const Vector<2, U> &v);
    template <typename U>
    Vector<2, T> &operator*=(U scalar);
    template <typename U>
    Vector<2, T> &operator*=(const Vector<2, U> &v);
    template <typename U>
    Vector<2, T> &operator/=(U scalar);
    template <typename U>
    Vector<2, T> &operator/=(const Vector<2, U> &v);

    T &operator[](size_t i);
    const T &operator[](size_t i) const;
};

template <typename T>
Vector<2, T> operator+(const Vector<2, T> &v);
template <typename T>
Vector<2, T> operator-(const Vector<2, T> &v);

template <typename T>
Vector<2, T> operator+(const Vector<2, T> &v, T scalar);
template <typename T>
Vector<2, T> operator+(T scalar, const Vector<2, T> &v);
template <typename T>
Vector<2, T> operator+(const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
Vector<2, T> operator-(const Vector<2, T> &v, T scalar);
template <typename T>
Vector<2, T> operator-(T scalar, const Vector<2, T> &v);
template <typename T>
Vector<2, T> operator-(const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
Vector<2, T> operator*(const Vector<2, T> &v, T scalar);
template <typename T>
Vector<2, T> operator*(T scalar, const Vector<2, T> &v);
template <typename T>
Vector<2, T> operator*(const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
Vector<2, T> operator/(const Vector<2, T> &v, T scalar);
template <typename T>
Vector<2, T> operator/(T scalar, const Vector<2, T> &v);
template <typename T>
Vector<2, T> operator/(const Vector<2, T> &v1, const Vector<2, T> &v2);

template <typename T>
bool operator==(const Vector<2, T> &v1, const Vector<2, T> &v2);
template <typename T>
bool operator!=(const Vector<2, T> &v1, const Vector<2, T> &v2);

template <typename T>
struct std::formatter<Vector<2, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(
        const Nyx::Math::Vector<2, T> &v, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "[{},{}]", v.x, v.y);
    }
};
}  // namespace Nyx::Math

#include "vector2.inl"
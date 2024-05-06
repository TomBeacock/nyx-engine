#pragma once

#include <format>

namespace Nyx::Math {
template <size_t L, typename T>
struct Vector;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Float3 = Vector<3, float>;
using Double3 = Vector<3, double>;
using Int3 = Vector<3, int>;
using UInt3 = Vector<3, unsigned int>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct Vector<3, T> {
    T x, y, z;

    const static Vector<3, T> zero;
    const static Vector<3, T> one;
    const static Vector<3, T> left;
    const static Vector<3, T> right;
    const static Vector<3, T> up;
    const static Vector<3, T> down;
    const static Vector<3, T> forward;
    const static Vector<3, T> back;

    Vector() = default;
    template <typename TX, typename TY, typename TZ>
    Vector(TX x, TY y, TZ z);
    template <typename U>
    explicit Vector(U scalar);
    template <typename U>
    Vector(const Vector<2, U> &v);
    template <typename U>
    Vector(const Vector<3, U> &v);
    template <typename U>
    Vector(const Vector<4, U> &v);

    template <typename U>
    Vector<3, T> &operator=(U scalar);
    template <typename U>
    Vector<3, T> &operator=(const Vector<3, U> &v);
    template <typename U>
    Vector<3, T> &operator+=(U scalar);
    template <typename U>
    Vector<3, T> &operator+=(const Vector<3, U> &v);
    template <typename U>
    Vector<3, T> &operator-=(U scalar);
    template <typename U>
    Vector<3, T> &operator-=(const Vector<3, U> &v);
    template <typename U>
    Vector<3, T> &operator*=(U scalar);
    template <typename U>
    Vector<3, T> &operator*=(const Vector<3, U> &v);
    template <typename U>
    Vector<3, T> &operator/=(U scalar);
    template <typename U>
    Vector<3, T> &operator/=(const Vector<3, U> &v);

    T &operator[](size_t i);
    const T &operator[](size_t i) const;
};

template <typename T>
Vector<3, T> operator+(const Vector<3, T> &v);
template <typename T>
Vector<3, T> operator-(const Vector<3, T> &v);

template <typename T>
Vector<3, T> operator+(const Vector<3, T> &v, T scalar);
template <typename T>
Vector<3, T> operator+(T scalar, const Vector<3, T> &v);
template <typename T>
Vector<3, T> operator+(const Vector<3, T> &v1, const Vector<3, T> &v2);
template <typename T>
Vector<3, T> operator-(const Vector<3, T> &v, T scalar);
template <typename T>
Vector<3, T> operator-(T scalar, const Vector<3, T> &v);
template <typename T>
Vector<3, T> operator-(const Vector<3, T> &v1, const Vector<3, T> &v2);
template <typename T>
Vector<3, T> operator*(const Vector<3, T> &v, T scalar);
template <typename T>
Vector<3, T> operator*(T scalar, const Vector<3, T> &v);
template <typename T>
Vector<3, T> operator*(const Vector<3, T> &v1, const Vector<3, T> &v2);
template <typename T>
Vector<3, T> operator/(const Vector<3, T> &v, T scalar);
template <typename T>
Vector<3, T> operator/(T scalar, const Vector<3, T> &v);
template <typename T>
Vector<3, T> operator/(const Vector<3, T> &v1, const Vector<3, T> &v2);

template <typename T>
bool operator==(const Vector<3, T> &v1, const Vector<3, T> &v2);
template <typename T>
bool operator!=(const Vector<3, T> &v1, const Vector<3, T> &v2);

template <typename T>
struct std::formatter<Vector<3, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(
        const Nyx::Math::Vector<3, T> &v, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "[{},{},{}]", v.x, v.y, v.z);
    }
};
}  // namespace Nyx::Math

#include "vector3.inl"
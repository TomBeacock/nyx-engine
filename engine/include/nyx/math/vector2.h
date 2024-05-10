#pragma once

#include "nyx/types.h"

namespace Nyx::Math {
template <size_t L, typename T>
struct VectorT;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Nat2 = VectorT<2, Nat>;
using Int2 = VectorT<2, Int>;
using Real2 = VectorT<2, Real>;
using Vector2 = Real2;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct VectorT<2, T> {
    T x, y;

    const static VectorT<2, T> zero;
    const static VectorT<2, T> one;
    const static VectorT<2, T> left;
    const static VectorT<2, T> right;
    const static VectorT<2, T> up;
    const static VectorT<2, T> down;

    constexpr VectorT() = default;
    template <typename TX, typename TY>
    constexpr VectorT(TX x, TY y);
    template <typename U>
    constexpr explicit VectorT(U scalar);
    template <typename U>
    constexpr VectorT(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT(const VectorT<4, U> &v);

    template <typename U>
    constexpr VectorT<2, T> &operator=(U scalar);
    template <typename U>
    constexpr VectorT<2, T> &operator=(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT<2, T> &operator+=(U scalar);
    template <typename U>
    constexpr VectorT<2, T> &operator+=(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT<2, T> &operator-=(U scalar);
    template <typename U>
    constexpr VectorT<2, T> &operator-=(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT<2, T> &operator*=(U scalar);
    template <typename U>
    constexpr VectorT<2, T> &operator*=(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT<2, T> &operator/=(U scalar);
    template <typename U>
    constexpr VectorT<2, T> &operator/=(const VectorT<2, U> &v);

    constexpr T &operator[](size_t i);
    constexpr const T &operator[](size_t i) const;
};

template <typename T>
constexpr VectorT<2, T> operator+(const VectorT<2, T> &v);
template <typename T>
constexpr VectorT<2, T> operator-(const VectorT<2, T> &v);

template <typename T>
constexpr VectorT<2, T> operator+(const VectorT<2, T> &v, T scalar);
template <typename T>
constexpr VectorT<2, T> operator+(T scalar, const VectorT<2, T> &v);
template <typename T>
constexpr VectorT<2, T> operator+(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2);
template <typename T>
constexpr VectorT<2, T> operator-(const VectorT<2, T> &v, T scalar);
template <typename T>
constexpr VectorT<2, T> operator-(T scalar, const VectorT<2, T> &v);
template <typename T>
constexpr VectorT<2, T> operator-(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2);
template <typename T>
constexpr VectorT<2, T> operator*(const VectorT<2, T> &v, T scalar);
template <typename T>
constexpr VectorT<2, T> operator*(T scalar, const VectorT<2, T> &v);
template <typename T>
constexpr VectorT<2, T> operator*(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2);
template <typename T>
constexpr VectorT<2, T> operator/(const VectorT<2, T> &v, T scalar);
template <typename T>
constexpr VectorT<2, T> operator/(T scalar, const VectorT<2, T> &v);
template <typename T>
constexpr VectorT<2, T> operator/(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2);

template <typename T>
constexpr bool operator==(const VectorT<2, T> &v1, const VectorT<2, T> &v2);
template <typename T>
constexpr bool operator!=(const VectorT<2, T> &v1, const VectorT<2, T> &v2);
}  // namespace Nyx::Math

#include "vector2.inl"
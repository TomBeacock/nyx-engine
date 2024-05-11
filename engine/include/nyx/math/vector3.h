#pragma once

#include "nyx/types.h"

namespace Nyx::Math {
template <size_t L, typename T>
struct VectorT;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
using Vector3 = VectorT<3, T>;
using Nat3 = Vector3<Nat>;
using Int3 = Vector3<Int>;
using Float3 = Vector3<Float>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct VectorT<3, T> {
    T x, y, z;

    const static VectorT<3, T> zero;
    const static VectorT<3, T> one;
    const static VectorT<3, T> left;
    const static VectorT<3, T> right;
    const static VectorT<3, T> up;
    const static VectorT<3, T> down;
    const static VectorT<3, T> forward;
    const static VectorT<3, T> back;

    constexpr VectorT() = default;
    template <typename TX, typename TY, typename TZ>
    constexpr VectorT(TX x, TY y, TZ z);
    template <typename U>
    constexpr explicit VectorT(U scalar);
    template <typename U>
    constexpr VectorT(const VectorT<2, U> &v);
    template <typename U>
    constexpr VectorT(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT(const VectorT<4, U> &v);

    template <typename U>
    constexpr VectorT<3, T> &operator=(U scalar);
    template <typename U>
    constexpr VectorT<3, T> &operator=(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT<3, T> &operator+=(U scalar);
    template <typename U>
    constexpr VectorT<3, T> &operator+=(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT<3, T> &operator-=(U scalar);
    template <typename U>
    constexpr VectorT<3, T> &operator-=(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT<3, T> &operator*=(U scalar);
    template <typename U>
    constexpr VectorT<3, T> &operator*=(const VectorT<3, U> &v);
    template <typename U>
    constexpr VectorT<3, T> &operator/=(U scalar);
    template <typename U>
    constexpr VectorT<3, T> &operator/=(const VectorT<3, U> &v);

    constexpr T &operator[](size_t i);
    constexpr const T &operator[](size_t i) const;
};

template <typename T>
constexpr VectorT<3, T> operator+(const VectorT<3, T> &v);
template <typename T>
constexpr VectorT<3, T> operator-(const VectorT<3, T> &v);

template <typename T>
constexpr VectorT<3, T> operator+(const VectorT<3, T> &v, T scalar);
template <typename T>
constexpr VectorT<3, T> operator+(T scalar, const VectorT<3, T> &v);
template <typename T>
constexpr VectorT<3, T> operator+(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2);
template <typename T>
constexpr VectorT<3, T> operator-(const VectorT<3, T> &v, T scalar);
template <typename T>
constexpr VectorT<3, T> operator-(T scalar, const VectorT<3, T> &v);
template <typename T>
constexpr VectorT<3, T> operator-(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2);
template <typename T>
constexpr VectorT<3, T> operator*(const VectorT<3, T> &v, T scalar);
template <typename T>
constexpr VectorT<3, T> operator*(T scalar, const VectorT<3, T> &v);
template <typename T>
constexpr VectorT<3, T> operator*(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2);
template <typename T>
constexpr VectorT<3, T> operator/(const VectorT<3, T> &v, T scalar);
template <typename T>
constexpr VectorT<3, T> operator/(T scalar, const VectorT<3, T> &v);
template <typename T>
constexpr VectorT<3, T> operator/(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2);

template <typename T>
constexpr bool operator==(const VectorT<3, T> &v1, const VectorT<3, T> &v2);
template <typename T>
constexpr bool operator!=(const VectorT<3, T> &v1, const VectorT<3, T> &v2);
}  // namespace Nyx::Math

#include "vector3.inl"
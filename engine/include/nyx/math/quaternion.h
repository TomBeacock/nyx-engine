#pragma once

#include "nyx/types.h"

namespace Nyx::Math {
template <typename T>
struct QuaternionT;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Quaternion = QuaternionT<Float>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct QuaternionT {
    T x, y, z, w;

    const static QuaternionT<T> zero;
    const static QuaternionT<T> one;
    const static QuaternionT<T> identity;

    constexpr QuaternionT();
    constexpr QuaternionT(const QuaternionT<T> &q);
    template <typename U>
    constexpr QuaternionT(const QuaternionT<U> &q);
    template <typename TX, typename TY, typename TZ, typename TW>
    constexpr QuaternionT(TX x, TY y, TZ z, TW w);

    template <typename U>
    constexpr QuaternionT<T> &operator=(const QuaternionT<U> &q);
    template <typename U>
    constexpr QuaternionT<T> &operator+=(const QuaternionT<U> &q);
    template <typename U>
    constexpr QuaternionT<T> &operator-=(const QuaternionT<U> &q);
    template <typename U>
    constexpr QuaternionT<T> &operator*=(U scalar);
    template <typename U>
    constexpr QuaternionT<T> &operator*=(const QuaternionT<U> &q);
    template <typename U>
    constexpr QuaternionT<T> &operator/=(U scalar);

    constexpr T &operator[](size_t i);
    constexpr const T &operator[](size_t i) const;
};

template <typename T>
constexpr QuaternionT<T> operator+(const QuaternionT<T> &q);
template <typename T>
constexpr QuaternionT<T> operator-(const QuaternionT<T> &q);

template <typename T>
constexpr QuaternionT<T> operator+(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2);
template <typename T>
constexpr QuaternionT<T> operator-(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2);
template <typename T>
constexpr QuaternionT<T> operator*(const QuaternionT<T> &q, T scalar);
template <typename T>
constexpr QuaternionT<T> operator*(T scalar, const QuaternionT<T> &q);
template <typename T>
constexpr QuaternionT<T> operator*(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2);
template <typename T>
constexpr QuaternionT<T> operator/(const QuaternionT<T> &q, T scalar);
template <typename T>
constexpr QuaternionT<T> operator/(T scalar, const QuaternionT<T> &q);

template <typename T>
constexpr bool operator==(const QuaternionT<T> &q1, const QuaternionT<T> &q2);
template <typename T>
constexpr bool operator!=(const QuaternionT<T> &q1, const QuaternionT<T> &q2);
}  // namespace Nyx::Math

#include "quaternion.inl"
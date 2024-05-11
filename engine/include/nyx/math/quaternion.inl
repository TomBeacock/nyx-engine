#include "nyx/assert.h"
#include "quaternion.h"

namespace Nyx::Math {
template <typename T>
const QuaternionT<T> QuaternionT<T>::zero = QuaternionT<T>(0, 0, 0, 0);
template <typename T>
const QuaternionT<T> QuaternionT<T>::one = QuaternionT<T>(1, 1, 1, 1);
template <typename T>
const QuaternionT<T> QuaternionT<T>::identity = QuaternionT<T>(0, 0, 0, 1);

template <typename T>
constexpr QuaternionT<T>::QuaternionT() : x(0), y(0), z(0), w(1)
{}

template <typename T>
constexpr QuaternionT<T>::QuaternionT(const QuaternionT<T> &q)
    : x(q.x), y(q.y), z(q.z), w(q.w)
{}

template <typename T>
template <typename U>
constexpr QuaternionT<T>::QuaternionT(const QuaternionT<U> &q)
    : x(static_cast<T>(q.x)),
      y(static_cast<T>(q.y)),
      z(static_cast<T>(q.z)),
      w(static_cast<T>(q.w))
{}

template <typename T>
template <typename TX, typename TY, typename TZ, typename TW>
constexpr QuaternionT<T>::QuaternionT(TX x, TY y, TZ z, TW w)
    : x(static_cast<T>(x)),
      y(static_cast<T>(y)),
      z(static_cast<T>(z)),
      w(static_cast<T>(w))
{}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator=(const QuaternionT<U> &q)
{
    this->x = static_cast<T>(q.x);
    this->y = static_cast<T>(q.y);
    this->z = static_cast<T>(q.z);
    this->w = static_cast<T>(q.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator+=(const QuaternionT<U> &q)
{
    this->x += static_cast<T>(q.x);
    this->y += static_cast<T>(q.y);
    this->z += static_cast<T>(q.z);
    this->w += static_cast<T>(q.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator-=(const QuaternionT<U> &q)
{
    this->x -= static_cast<T>(q.x);
    this->y -= static_cast<T>(q.y);
    this->z -= static_cast<T>(q.z);
    this->w -= static_cast<T>(q.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    this->z *= static_cast<T>(scalar);
    this->w *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator*=(const QuaternionT<U> &q)
{
    const QuaternionT<T> q1(*this);
    const QuaternionT<T> q2(q);
    this->x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    this->y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
    this->z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
    this->w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    return *this;
}

template <typename T>
template <typename U>
constexpr QuaternionT<T> &QuaternionT<T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    this->z /= static_cast<T>(scalar);
    this->w /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
constexpr T &QuaternionT<T>::operator[](size_t i)
{
    NYX_ENGINE_ASSERT(
        i >= 0 && i < 4, "Cannot access value, i should be in range [0-3]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}
template <typename T>
constexpr const T &QuaternionT<T>::operator[](size_t i) const
{
    NYX_ENGINE_ASSERT(
        i >= 0 && i < 4, "Cannot access value, i should be in range [0-3]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}

template <typename T>
constexpr QuaternionT<T> operator+(const QuaternionT<T> &q)
{
    return q;
}

template <typename T>
constexpr QuaternionT<T> operator-(const QuaternionT<T> &q)
{
    return QuaternionT<T>(-q.x, -q.y, -q.z, -q.w);
}

template <typename T>
constexpr QuaternionT<T> operator+(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2)
{
    return QuaternionT<T>(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w);
}

template <typename T>
constexpr QuaternionT<T> operator-(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2)
{
    return QuaternionT<T>(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w);
}

template <typename T>
constexpr QuaternionT<T> operator*(const QuaternionT<T> &q, T scalar)
{
    return QuaternionT<T>(
        q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar);
}

template <typename T>
constexpr QuaternionT<T> operator*(T scalar, const QuaternionT<T> &q)
{
    return QuaternionT<T>(
        scalar * q.x, scalar * q.y, scalar * q.z, scalar * q.w);
}

template <typename T>
constexpr QuaternionT<T> operator*(
    const QuaternionT<T> &q1, const QuaternionT<T> &q2)
{
    return Quaternion<T>(q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
        q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
}

template <typename T>
constexpr QuaternionT<T> operator/(const QuaternionT<T> &q, T scalar)
{
    return QuaternionT<T>(
        q.x / scalar, q.y / scalar, q.z / scalar, q.w / scalar);
}

template <typename T>
constexpr QuaternionT<T> operator/(T scalar, const QuaternionT<T> &q)
{
    return VectorT<4, T>(
        scalar / q.x, scalar / q.y, scalar / q.z, scalar / q.w);
}

template <typename T>
constexpr bool operator==(const QuaternionT<T> &q1, const QuaternionT<T> &q2)
{
    return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}
template <typename T>
constexpr bool operator!=(const QuaternionT<T> &q1, const QuaternionT<T> &q2)
{
    return !(q1 == q2);
}
}  // namespace Nyx::Math
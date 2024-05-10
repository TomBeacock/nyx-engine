#include "nyx/assert.h"
#include "vector3.h"

namespace Nyx::Math {
template <typename T>
const VectorT<3, T> VectorT<3, T>::zero =
    VectorT<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const VectorT<3, T> VectorT<3, T>::one =
    VectorT<3, T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
template <typename T>
const VectorT<3, T> VectorT<3, T>::left =
    VectorT<3, T>(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const VectorT<3, T> VectorT<3, T>::right =
    VectorT<3, T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const VectorT<3, T> VectorT<3, T>::up =
    VectorT<3, T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
template <typename T>
const VectorT<3, T> VectorT<3, T>::down =
    VectorT<3, T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));
template <typename T>
const VectorT<3, T> VectorT<3, T>::forward =
    VectorT<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
template <typename T>
const VectorT<3, T> VectorT<3, T>::back =
    VectorT<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));

template <typename T>
template <typename TX, typename TY, typename TZ>
constexpr VectorT<3, T>::VectorT(TX x, TY y, TZ z)
    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
{}

template <typename T>
template <typename U>
constexpr VectorT<3, T>::VectorT(U scalar)
    : x(static_cast<T>(scalar)),
      y(static_cast<T>(scalar)),
      z(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
constexpr VectorT<3, T>::VectorT(const VectorT<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z()
{}

template <typename T>
template <typename U>
constexpr VectorT<3, T>::VectorT(const VectorT<3, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
template <typename U>
constexpr VectorT<3, T>::VectorT(const VectorT<4, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    this->z = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator=(const VectorT<3, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    this->z = static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    this->z += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator+=(const VectorT<3, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    this->z += static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    this->z -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator-=(const VectorT<3, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    this->z -= static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    this->z *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator*=(const VectorT<3, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    this->z *= static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    this->z /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<3, T> &VectorT<3, T>::operator/=(const VectorT<3, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    this->z /= static_cast<T>(v.z);
    return *this;
}

template <typename T>
constexpr T &VectorT<3, T>::operator[](size_t i)
{
    NYX_ASSERT(
        i >= 0 && i < 3, "Cannot access value, i should be in range [0-2]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}
template <typename T>
constexpr const T &VectorT<3, T>::operator[](size_t i) const
{
    NYX_ASSERT(
        i >= 0 && i < 3, "Cannot access value, i should be in range [0-2]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}

template <typename T>
constexpr VectorT<3, T> operator+(const VectorT<3, T> &v)
{
    return v;
}

template <typename T>
constexpr VectorT<3, T> operator-(const VectorT<3, T> &v)
{
    return VectorT<3, T>(-v.x, -v.y, -v.z);
}
template <typename T>
constexpr VectorT<3, T> operator+(const VectorT<3, T> &v, T scalar)
{
    return VectorT<3, T>(v.x + scalar, v.y + scalar, v.z + scalar);
}

template <typename T>
constexpr VectorT<3, T> operator+(T scalar, const VectorT<3, T> &v)
{
    return VectorT<3, T>(scalar + v.x, scalar + v.y, scalar + v.z);
}

template <typename T>
constexpr VectorT<3, T> operator+(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return VectorT<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
constexpr VectorT<3, T> operator-(const VectorT<3, T> &v, T scalar)
{
    return VectorT<3, T>(v.x - scalar, v.y - scalar, v.z - scalar);
}

template <typename T>
constexpr VectorT<3, T> operator-(T scalar, const VectorT<3, T> &v)
{
    return VectorT<3, T>(scalar - v.x, scalar - v.y, scalar - v.z);
}

template <typename T>
constexpr VectorT<3, T> operator-(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return VectorT<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
constexpr VectorT<3, T> operator*(const VectorT<3, T> &v, T scalar)
{
    return VectorT<3, T>(v.x * scalar, v.y * scalar, v.z * scalar);
}

template <typename T>
constexpr VectorT<3, T> operator*(T scalar, const VectorT<3, T> &v)
{
    return VectorT<3, T>(scalar * v.x, scalar * v.y, scalar * v.z);
}

template <typename T>
constexpr VectorT<3, T> operator*(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return VectorT<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
constexpr VectorT<3, T> operator/(const VectorT<3, T> &v, T scalar)
{
    return VectorT<3, T>(v.x / scalar, v.y / scalar, v.z / scalar);
}

template <typename T>
constexpr VectorT<3, T> operator/(T scalar, const VectorT<3, T> &v)
{
    return VectorT<3, T>(scalar / v.x, scalar / v.y, scalar / v.z);
}

template <typename T>
constexpr VectorT<3, T> operator/(
    const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return VectorT<3, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
constexpr bool operator==(const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
constexpr bool operator!=(const VectorT<3, T> &v1, const VectorT<3, T> &v2)
{
    return !(v1 == v2);
}
}  // namespace Nyx::Math
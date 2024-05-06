#include "vector3.h"

#include <cassert>
#include <cmath>

namespace Nyx::Math {
template <typename T>
const Vector<3, T> Vector<3, T>::zero =
    Vector<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector<3, T> Vector<3, T>::one =
    Vector<3, T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
template <typename T>
const Vector<3, T> Vector<3, T>::left =
    Vector<3, T>(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector<3, T> Vector<3, T>::right =
    Vector<3, T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector<3, T> Vector<3, T>::up =
    Vector<3, T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
template <typename T>
const Vector<3, T> Vector<3, T>::down =
    Vector<3, T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));
template <typename T>
const Vector<3, T> Vector<3, T>::forward =
    Vector<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
template <typename T>
const Vector<3, T> Vector<3, T>::back =
    Vector<3, T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));

template <typename T>
template <typename TX, typename TY, typename TZ>
Vector<3, T>::Vector(TX x, TY y, TZ z)
    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
{}

template <typename T>
template <typename U>
Vector<3, T>::Vector(U scalar)
    : x(static_cast<T>(scalar)),
      y(static_cast<T>(scalar)),
      z(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
Vector<3, T>::Vector(const Vector<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z()
{}

template <typename T>
template <typename U>
inline Vector<3, T>::Vector(const Vector<3, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
template <typename U>
Vector<3, T>::Vector(const Vector<4, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
{}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    this->z = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator=(const Vector<3, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    this->z = static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    this->z += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator+=(const Vector<3, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    this->z += static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    this->z -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator-=(const Vector<3, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    this->z -= static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    this->z *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator*=(const Vector<3, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    this->z *= static_cast<T>(v.z);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    this->z /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<3, T> &Vector<3, T>::operator/=(const Vector<3, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    this->z /= static_cast<T>(v.z);
    return *this;
}

template <typename T>
inline T &Vector<3, T>::operator[](size_t i)
{
    assert(i >= 0 && i < 3);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}
template <typename T>
inline const T &Vector<3, T>::operator[](size_t i) const
{
    assert(i >= 0 && i < 3);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}

template <typename T>
inline Vector<3, T> operator+(const Vector<3, T> &v)
{
    return v;
}

template <typename T>
inline Vector<3, T> operator-(const Vector<3, T> &v)
{
    return Vector<3, T>(-v.x, -v.y, -v.z);
}
template <typename T>
Vector<3, T> operator+(const Vector<3, T> &v, T scalar)
{
    return Vector<3, T>(v.x + scalar, v.y + scalar, v.z + scalar);
}

template <typename T>
Vector<3, T> operator+(T scalar, const Vector<3, T> &v)
{
    return Vector<3, T>(scalar + v.x, scalar + v.y, scalar + v.z);
}

template <typename T>
Vector<3, T> operator+(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return Vector<3, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
Vector<3, T> operator-(const Vector<3, T> &v, T scalar)
{
    return Vector<3, T>(v.x - scalar, v.y - scalar, v.z - scalar);
}

template <typename T>
Vector<3, T> operator-(T scalar, const Vector<3, T> &v)
{
    return Vector<3, T>(scalar - v.x, scalar - v.y, scalar - v.z);
}

template <typename T>
Vector<3, T> operator-(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return Vector<3, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <typename T>
Vector<3, T> operator*(const Vector<3, T> &v, T scalar)
{
    return Vector<3, T>(v.x * scalar, v.y * scalar, v.z * scalar);
}

template <typename T>
Vector<3, T> operator*(T scalar, const Vector<3, T> &v)
{
    return Vector<3, T>(scalar * v.x, scalar * v.y, scalar * v.z);
}

template <typename T>
Vector<3, T> operator*(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return Vector<3, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
Vector<3, T> operator/(const Vector<3, T> &v, T scalar)
{
    return Vector<3, T>(v.x / scalar, v.y / scalar, v.z / scalar);
}

template <typename T>
Vector<3, T> operator/(T scalar, const Vector<3, T> &v)
{
    return Vector<3, T>(scalar / v.x, scalar / v.y, scalar / v.z);
}

template <typename T>
Vector<3, T> operator/(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return Vector<3, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template <typename T>
bool operator==(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
template <typename T>
bool operator!=(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return !(v1 == v2);
}
}  // namespace Nyx::Math
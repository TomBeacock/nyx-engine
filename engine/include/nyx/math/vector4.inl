#include "vector4.h"

#include <cassert>
#include <cmath>

namespace Nyx::Math {
template <typename T>
const Vector<4, T> Vector<4, T>::zero = Vector<4, T>(
    static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector<4, T> Vector<4, T>::one = Vector<4, T>(
    static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));

template <typename T>
template <typename TX, typename TY, typename TZ, typename TW>
Vector<4, T>::Vector(TX x, TY y, TZ z, TW w)
    : x(static_cast<T>(x)),
      y(static_cast<T>(y)),
      z(static_cast<T>(z)),
      w(static_cast<T>(w))
{}

template <typename T>
template <typename U>
Vector<4, T>::Vector(U scalar)
    : x(static_cast<T>(scalar)),
      y(static_cast<T>(scalar)),
      z(static_cast<T>(scalar)),
      w(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
Vector<4, T>::Vector(const Vector<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(), w()
{}

template <typename T>
template <typename U>
Vector<4, T>::Vector(const Vector<3, U> &v)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w()
{}

template <typename T>
template <typename U>
inline Vector<4, T>::Vector(const Vector<4, U> &v)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(v.w))
{}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    this->z = static_cast<T>(scalar);
    this->w = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator=(const Vector<4, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    this->z = static_cast<T>(v.z);
    this->w = static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    this->z += static_cast<T>(scalar);
    this->w += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator+=(const Vector<4, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    this->z += static_cast<T>(v.z);
    this->w += static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    this->z -= static_cast<T>(scalar);
    this->w -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator-=(const Vector<4, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    this->z -= static_cast<T>(v.z);
    this->w -= static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    this->z *= static_cast<T>(scalar);
    this->w *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator*=(const Vector<4, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    this->z *= static_cast<T>(v.z);
    this->w *= static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    this->z /= static_cast<T>(scalar);
    this->w /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<4, T> &Vector<4, T>::operator/=(const Vector<4, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    this->z /= static_cast<T>(v.z);
    this->w /= static_cast<T>(v.w);
    return *this;
}

template <typename T>
inline T &Vector<4, T>::operator[](size_t i)
{
    assert(i >= 0 && i < 4);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}
template <typename T>
inline const T &Vector<4, T>::operator[](size_t i) const
{
    assert(i >= 0 && i < 4);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}

template <typename T>
inline Vector<4, T> operator+(const Vector<4, T> &v)
{
    return v;
}

template <typename T>
inline Vector<4, T> operator-(const Vector<4, T> &v)
{
    return Vector<4, T>(-v.x, -v.y, -v.z, -v.w);
}
template <typename T>
Vector<4, T> operator+(const Vector<4, T> &v, T scalar)
{
    return Vector<4, T>(v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar);
}

template <typename T>
Vector<4, T> operator+(T scalar, const Vector<4, T> &v)
{
    return Vector<4, T>(scalar + v.x, scalar + v.y, scalar + v.z, scalar + v.w);
}

template <typename T>
Vector<4, T> operator+(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return Vector<4, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
Vector<4, T> operator-(const Vector<4, T> &v, T scalar)
{
    return Vector<4, T>(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
}

template <typename T>
Vector<4, T> operator-(T scalar, const Vector<4, T> &v)
{
    return Vector<4, T>(scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
}

template <typename T>
Vector<4, T> operator-(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return Vector<4, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
Vector<4, T> operator*(const Vector<4, T> &v, T scalar)
{
    return Vector<4, T>(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

template <typename T>
Vector<4, T> operator*(T scalar, const Vector<4, T> &v)
{
    return Vector<4, T>(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}

template <typename T>
Vector<4, T> operator*(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return Vector<4, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
Vector<4, T> operator/(const Vector<4, T> &v, T scalar)
{
    return Vector<4, T>(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

template <typename T>
Vector<4, T> operator/(T scalar, const Vector<4, T> &v)
{
    return Vector<4, T>(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
}

template <typename T>
Vector<4, T> operator/(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return Vector<4, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
bool operator==(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}
template <typename T>
bool operator!=(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return !(v1 == v2);
}
}  // namespace Nyx::Math
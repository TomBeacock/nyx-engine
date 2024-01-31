#include "vector2.h"

#include <cassert>
#include <cmath>

namespace Nyx::Math {
template <typename T>
const Vector<2, T> Vector<2, T>::zero =
    Vector<2, T>(static_cast<T>(0), static_cast<T>(0));
template <typename T>
const Vector<2, T> Vector<2, T>::one =
    Vector<2, T>(static_cast<T>(1), static_cast<T>(1));
template <typename T>
const Vector<2, T> Vector<2, T>::left =
    Vector<2, T>(static_cast<T>(-1), static_cast<T>(0));
template <typename T>
const Vector<2, T> Vector<2, T>::right =
    Vector<2, T>(static_cast<T>(1), static_cast<T>(0));
template <typename T>
const Vector<2, T> Vector<2, T>::up =
    Vector<2, T>(static_cast<T>(0), static_cast<T>(1));
template <typename T>
const Vector<2, T> Vector<2, T>::down =
    Vector<2, T>(static_cast<T>(0), static_cast<T>(-1));

template <typename T>
template <typename TX, typename TY>
Vector<2, T>::Vector(TX x, TY y) : x(static_cast<T>(x)), y(static_cast<T>(y))
{}

template <typename T>
template <typename U>
Vector<2, T>::Vector(U scalar)
    : x(static_cast<T>(scalar)), y(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
Vector<2, T>::Vector(const Vector<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
Vector<2, T>::Vector(const Vector<3, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
Vector<2, T>::Vector(const Vector<4, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator=(const Vector<2, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator+=(const Vector<2, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator-=(const Vector<2, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator*=(const Vector<2, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
inline Vector<2, T> &Vector<2, T>::operator/=(const Vector<2, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    return *this;
}

template <typename T>
inline T &Vector<2, T>::operator[](size_t i)
{
    assert(i >= 0 && i < 2);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
    }
}
template <typename T>
inline const T &Vector<2, T>::operator[](size_t i) const
{
    assert(i >= 0 && i < 2);
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
    }
}

template <typename T>
inline Vector<2, T> operator+(const Vector<2, T> &v)
{
    return v;
}

template <typename T>
inline Vector<2, T> operator-(const Vector<2, T> &v)
{
    return Vector<2, T>(-v.x, -v.y);
}
template <typename T>
Vector<2, T> operator+(const Vector<2, T> &v, T scalar)
{
    return Vector<2, T>(v.x + scalar, v.y + scalar);
}

template <typename T>
Vector<2, T> operator+(T scalar, const Vector<2, T> &v)
{
    return Vector<2, T>(scalar + v.x, scalar + v.y);
}

template <typename T>
Vector<2, T> operator+(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return Vector<2, T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
Vector<2, T> operator-(const Vector<2, T> &v, T scalar)
{
    return Vector<2, T>(v.x - scalar, v.y - scalar);
}

template <typename T>
Vector<2, T> operator-(T scalar, const Vector<2, T> &v)
{
    return Vector<2, T>(scalar - v.x, scalar - v.y);
}

template <typename T>
Vector<2, T> operator-(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return Vector<2, T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
Vector<2, T> operator*(const Vector<2, T> &v, T scalar)
{
    return Vector<2, T>(v.x * scalar, v.y * scalar);
}

template <typename T>
Vector<2, T> operator*(T scalar, const Vector<2, T> &v)
{
    return Vector<2, T>(scalar * v.x, scalar * v.y);
}

template <typename T>
Vector<2, T> operator*(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return Vector<2, T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
Vector<2, T> operator/(const Vector<2, T> &v, T scalar)
{
    return Vector<2, T>(v.x / scalar, v.y / scalar);
}

template <typename T>
Vector<2, T> operator/(T scalar, const Vector<2, T> &v)
{
    return Vector<2, T>(scalar / v.x, scalar / v.y);
}

template <typename T>
Vector<2, T> operator/(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return Vector<2, T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
bool operator==(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
template <typename T>
bool operator!=(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return !(v1 == v2);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<2, T> &v)
{
    return os << '[' << v.x << ',' << v.y << ']';
}
}  // namespace Nyx::Math

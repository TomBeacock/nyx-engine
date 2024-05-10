#include "nyx/assert.h"
#include "vector2.h"

namespace Nyx::Math {
template <typename T>
const VectorT<2, T> VectorT<2, T>::zero =
    VectorT<2, T>(static_cast<T>(0), static_cast<T>(0));
template <typename T>
const VectorT<2, T> VectorT<2, T>::one =
    VectorT<2, T>(static_cast<T>(1), static_cast<T>(1));
template <typename T>
const VectorT<2, T> VectorT<2, T>::left =
    VectorT<2, T>(static_cast<T>(-1), static_cast<T>(0));
template <typename T>
const VectorT<2, T> VectorT<2, T>::right =
    VectorT<2, T>(static_cast<T>(1), static_cast<T>(0));
template <typename T>
const VectorT<2, T> VectorT<2, T>::up =
    VectorT<2, T>(static_cast<T>(0), static_cast<T>(1));
template <typename T>
const VectorT<2, T> VectorT<2, T>::down =
    VectorT<2, T>(static_cast<T>(0), static_cast<T>(-1));

template <typename T>
template <typename TX, typename TY>
constexpr VectorT<2, T>::VectorT(TX x, TY y)
    : x(static_cast<T>(x)), y(static_cast<T>(y))
{}

template <typename T>
template <typename U>
constexpr VectorT<2, T>::VectorT(U scalar)
    : x(static_cast<T>(scalar)), y(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
constexpr VectorT<2, T>::VectorT(const VectorT<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
constexpr VectorT<2, T>::VectorT(const VectorT<3, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
constexpr VectorT<2, T>::VectorT(const VectorT<4, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator=(const VectorT<2, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator+=(const VectorT<2, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator-=(const VectorT<2, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator*=(const VectorT<2, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<2, T> &VectorT<2, T>::operator/=(const VectorT<2, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    return *this;
}

template <typename T>
constexpr T &VectorT<2, T>::operator[](size_t i)
{
    NYX_ASSERT(
        i >= 0 && i < 2, "Cannot access value, i should be in range [0-1]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
    }
}
template <typename T>
constexpr const T &VectorT<2, T>::operator[](size_t i) const
{
    NYX_ASSERT(
        i >= 0 && i < 2, "Cannot access value, i should be in range [0-1]");
    switch (i) {
        default:
        case 0: return x;
        case 1: return y;
    }
}

template <typename T>
constexpr VectorT<2, T> operator+(const VectorT<2, T> &v)
{
    return v;
}

template <typename T>
constexpr VectorT<2, T> operator-(const VectorT<2, T> &v)
{
    return VectorT<2, T>(-v.x, -v.y);
}

template <typename T>
constexpr VectorT<2, T> operator+(const VectorT<2, T> &v, T scalar)
{
    return VectorT<2, T>(v.x + scalar, v.y + scalar);
}

template <typename T>
constexpr VectorT<2, T> operator+(T scalar, const VectorT<2, T> &v)
{
    return VectorT<2, T>(scalar + v.x, scalar + v.y);
}

template <typename T>
constexpr VectorT<2, T> operator+(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return VectorT<2, T>(v1.x + v2.x, v1.y + v2.y);
}

template <typename T>
constexpr VectorT<2, T> operator-(const VectorT<2, T> &v, T scalar)
{
    return VectorT<2, T>(v.x - scalar, v.y - scalar);
}

template <typename T>
constexpr VectorT<2, T> operator-(T scalar, const VectorT<2, T> &v)
{
    return VectorT<2, T>(scalar - v.x, scalar - v.y);
}

template <typename T>
constexpr VectorT<2, T> operator-(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return VectorT<2, T>(v1.x - v2.x, v1.y - v2.y);
}

template <typename T>
constexpr VectorT<2, T> operator*(const VectorT<2, T> &v, T scalar)
{
    return VectorT<2, T>(v.x * scalar, v.y * scalar);
}

template <typename T>
constexpr VectorT<2, T> operator*(T scalar, const VectorT<2, T> &v)
{
    return VectorT<2, T>(scalar * v.x, scalar * v.y);
}

template <typename T>
constexpr VectorT<2, T> operator*(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return VectorT<2, T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
constexpr VectorT<2, T> operator/(const VectorT<2, T> &v, T scalar)
{
    return VectorT<2, T>(v.x / scalar, v.y / scalar);
}

template <typename T>
constexpr VectorT<2, T> operator/(T scalar, const VectorT<2, T> &v)
{
    return VectorT<2, T>(scalar / v.x, scalar / v.y);
}

template <typename T>
constexpr VectorT<2, T> operator/(
    const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return VectorT<2, T>(v1.x / v2.x, v1.y / v2.y);
}

template <typename T>
constexpr bool operator==(const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
template <typename T>
constexpr bool operator!=(const VectorT<2, T> &v1, const VectorT<2, T> &v2)
{
    return !(v1 == v2);
}
}  // namespace Nyx::Math

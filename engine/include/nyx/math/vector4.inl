#include "nyx/assert.h"
#include "vector4.h"

namespace Nyx::Math {
template <typename T>
const VectorT<4, T> VectorT<4, T>::zero = VectorT<4, T>(
    static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
template <typename T>
const VectorT<4, T> VectorT<4, T>::one = VectorT<4, T>(
    static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));

template <typename T>
template <typename TX, typename TY, typename TZ, typename TW>
constexpr VectorT<4, T>::VectorT(TX x, TY y, TZ z, TW w)
    : x(static_cast<T>(x)),
      y(static_cast<T>(y)),
      z(static_cast<T>(z)),
      w(static_cast<T>(w))
{}

template <typename T>
template <typename U>
constexpr VectorT<4, T>::VectorT(U scalar)
    : x(static_cast<T>(scalar)),
      y(static_cast<T>(scalar)),
      z(static_cast<T>(scalar)),
      w(static_cast<T>(scalar))
{}

template <typename T>
template <typename U>
constexpr VectorT<4, T>::VectorT(const VectorT<2, U> &v)
    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(), w()
{}

template <typename T>
template <typename U>
constexpr VectorT<4, T>::VectorT(const VectorT<3, U> &v)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w()
{}

template <typename T>
template <typename U>
constexpr VectorT<4, T>::VectorT(const VectorT<4, U> &v)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(v.w))
{}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator=(U scalar)
{
    this->x = static_cast<T>(scalar);
    this->y = static_cast<T>(scalar);
    this->z = static_cast<T>(scalar);
    this->w = static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator=(const VectorT<4, U> &v)
{
    this->x = static_cast<T>(v.x);
    this->y = static_cast<T>(v.y);
    this->z = static_cast<T>(v.z);
    this->w = static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator+=(U scalar)
{
    this->x += static_cast<T>(scalar);
    this->y += static_cast<T>(scalar);
    this->z += static_cast<T>(scalar);
    this->w += static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator+=(const VectorT<4, U> &v)
{
    this->x += static_cast<T>(v.x);
    this->y += static_cast<T>(v.y);
    this->z += static_cast<T>(v.z);
    this->w += static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator-=(U scalar)
{
    this->x -= static_cast<T>(scalar);
    this->y -= static_cast<T>(scalar);
    this->z -= static_cast<T>(scalar);
    this->w -= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator-=(const VectorT<4, U> &v)
{
    this->x -= static_cast<T>(v.x);
    this->y -= static_cast<T>(v.y);
    this->z -= static_cast<T>(v.z);
    this->w -= static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator*=(U scalar)
{
    this->x *= static_cast<T>(scalar);
    this->y *= static_cast<T>(scalar);
    this->z *= static_cast<T>(scalar);
    this->w *= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator*=(const VectorT<4, U> &v)
{
    this->x *= static_cast<T>(v.x);
    this->y *= static_cast<T>(v.y);
    this->z *= static_cast<T>(v.z);
    this->w *= static_cast<T>(v.w);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator/=(U scalar)
{
    this->x /= static_cast<T>(scalar);
    this->y /= static_cast<T>(scalar);
    this->z /= static_cast<T>(scalar);
    this->w /= static_cast<T>(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr VectorT<4, T> &VectorT<4, T>::operator/=(const VectorT<4, U> &v)
{
    this->x /= static_cast<T>(v.x);
    this->y /= static_cast<T>(v.y);
    this->z /= static_cast<T>(v.z);
    this->w /= static_cast<T>(v.w);
    return *this;
}

template <typename T>
constexpr T &VectorT<4, T>::operator[](size_t i)
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
constexpr const T &VectorT<4, T>::operator[](size_t i) const
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
constexpr VectorT<4, T> operator+(const VectorT<4, T> &v)
{
    return v;
}

template <typename T>
constexpr VectorT<4, T> operator-(const VectorT<4, T> &v)
{
    return VectorT<4, T>(-v.x, -v.y, -v.z, -v.w);
}
template <typename T>
constexpr VectorT<4, T> operator+(const VectorT<4, T> &v, T scalar)
{
    return VectorT<4, T>(
        v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar);
}

template <typename T>
constexpr VectorT<4, T> operator+(T scalar, const VectorT<4, T> &v)
{
    return VectorT<4, T>(
        scalar + v.x, scalar + v.y, scalar + v.z, scalar + v.w);
}

template <typename T>
constexpr VectorT<4, T> operator+(
    const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return VectorT<4, T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <typename T>
constexpr VectorT<4, T> operator-(const VectorT<4, T> &v, T scalar)
{
    return VectorT<4, T>(
        v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
}

template <typename T>
constexpr VectorT<4, T> operator-(T scalar, const VectorT<4, T> &v)
{
    return VectorT<4, T>(
        scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
}

template <typename T>
constexpr VectorT<4, T> operator-(
    const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return VectorT<4, T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <typename T>
constexpr VectorT<4, T> operator*(const VectorT<4, T> &v, T scalar)
{
    return VectorT<4, T>(
        v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

template <typename T>
constexpr VectorT<4, T> operator*(T scalar, const VectorT<4, T> &v)
{
    return VectorT<4, T>(
        scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}

template <typename T>
constexpr VectorT<4, T> operator*(
    const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return VectorT<4, T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template <typename T>
constexpr VectorT<4, T> operator/(const VectorT<4, T> &v, T scalar)
{
    return VectorT<4, T>(
        v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

template <typename T>
constexpr VectorT<4, T> operator/(T scalar, const VectorT<4, T> &v)
{
    return VectorT<4, T>(
        scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
}

template <typename T>
constexpr VectorT<4, T> operator/(
    const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return VectorT<4, T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template <typename T>
constexpr bool operator==(const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}
template <typename T>
constexpr bool operator!=(const VectorT<4, T> &v1, const VectorT<4, T> &v2)
{
    return !(v1 == v2);
}
}  // namespace Nyx::Math
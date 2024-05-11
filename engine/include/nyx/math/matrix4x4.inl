#include "matrix4x4.h"
#include "nyx/assert.h"
#include "nyx/math/vector_func.h"

namespace Nyx::Math {
template <typename T>
const MatrixT<4, 4, T> MatrixT<4, 4, T>::zero = MatrixT<4, 4, T>(0);
template <typename T>
const MatrixT<4, 4, T> MatrixT<4, 4, T>::one = MatrixT<4, 4, T>(1);
template <typename T>
const MatrixT<4, 4, T> MatrixT<4, 4, T>::identity =
    MatrixT<4, 4, T>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T>::MatrixT(U scalar)
    : cols{Col(scalar), Col(scalar), Col(scalar), Col(scalar)}
{}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T>::MatrixT(const MatrixT<4, 4, U> &m)
    : cols{m[0], m[1], m[2], m[3]}
{}

template <typename T>
template <typename X0, typename Y0, typename Z0, typename W0, typename X1,
    typename Y1, typename Z1, typename W1, typename X2, typename Y2,
    typename Z2, typename W2, typename X3, typename Y3, typename Z3,
    typename W3>
constexpr Nyx::Math::MatrixT<4, 4, T>::MatrixT(X0 x0, Y0 y0, Z0 z0, W0 w0,
    X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2, Z2 z2, W2 w2, X3 x3, Y3 y3, Z3 z3,
    W3 w3)
    : cols{
          Col(x0, y0, z0, w0),
          Col(x1, y1, z1, w1),
          Col(x2, y2, z2, w2),
          Col(x3, y3, z3, w3),
      }
{}

template <typename T>
template <typename V0, typename V1, typename V2, typename V3>
constexpr MatrixT<4, 4, T>::MatrixT(
    VectorT<4, V0> v0, VectorT<4, V1> v1, VectorT<4, V2> v2, VectorT<4, V3> v3)
    : cols{v0, v1, v2, v3}
{}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &Nyx::Math::MatrixT<4, 4, T>::operator=(U scalar)
{
    this->cols[0] = Col(scalar);
    this->cols[1] = Col(scalar);
    this->cols[2] = Col(scalar);
    this->cols[3] = Col(scalar);
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &Nyx::Math::MatrixT<4, 4, T>::operator=(
    const MatrixT<4, 4, U> &m)
{
    this->cols[0] = m[0];
    this->cols[1] = m[1];
    this->cols[2] = m[2];
    this->cols[3] = m[3];
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator+=(U scalar)
{
    this->cols[0] += scalar;
    this->cols[1] += scalar;
    this->cols[2] += scalar;
    this->cols[3] += scalar;
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator+=(
    const MatrixT<4, 4, U> &m)
{
    this->cols[0] += m[0];
    this->cols[1] += m[1];
    this->cols[2] += m[2];
    this->cols[3] += m[3];
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator-=(U scalar)
{
    this->cols[0] -= scalar;
    this->cols[1] -= scalar;
    this->cols[2] -= scalar;
    this->cols[3] -= scalar;
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator-=(
    const MatrixT<4, 4, U> &m)
{
    this->cols[0] -= m[0];
    this->cols[1] -= m[1];
    this->cols[2] -= m[2];
    this->cols[3] -= m[3];
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator*=(U scalar)
{
    this->cols[0] *= scalar;
    this->cols[1] *= scalar;
    this->cols[2] *= scalar;
    this->cols[3] *= scalar;
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator*=(
    const MatrixT<4, 4, U> &m)
{
    return (*this = *this * m);
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator/=(U scalar)
{
    this->cols[0] /= scalar;
    this->cols[1] /= scalar;
    this->cols[2] /= scalar;
    this->cols[3] /= scalar;
    return *this;
}

template <typename T>
template <typename U>
constexpr MatrixT<4, 4, T> &MatrixT<4, 4, T>::operator/=(
    const MatrixT<4, 4, U> &m)
{
    return *this *= inverse(m);
}

template <typename T>
constexpr MatrixT<4, 4, T>::Col &MatrixT<4, 4, T>::operator[](size_t i)
{
    NYX_ENGINE_ASSERT(
        i >= 0 && i < 4, "Cannot access column, i should be in range [0-3]");
    return cols[i];
}

template <typename T>
constexpr const MatrixT<4, 4, T>::Col &MatrixT<4, 4, T>::operator[](
    size_t i) const
{
    NYX_ENGINE_ASSERT(
        i >= 0 && i < 4, "Cannot access column, i should be in range [0-3]");
    return cols[i];
}

template <typename T>
constexpr MatrixT<4, 4, T> operator+(const MatrixT<4, 4, T> &m)
{
    return m;
}

template <typename T>
constexpr MatrixT<4, 4, T> operator-(const MatrixT<4, 4, T> &m)
{
    return MatrixT<4, 4, T>(-m[0], -m[1], -m[2], -m[3]);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator+(const MatrixT<4, 4, T> &m, T scalar)
{
    return MatrixT<4, 4, T>(
        m[0] + scalar, m[1] + scalar, m[2] + scalar, m[3] + scalar);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator+(T scalar, const MatrixT<4, 4, T> &m)
{
    return MatrixT<4, 4, T>(
        scalar + m[0], scalar + m[1], scalar + m[2], scalar + m[3]);
}
template <typename T>
constexpr MatrixT<4, 4, T> operator+(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    return MatrixT<4, 4, T>(
        m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
}
template <typename T>
constexpr MatrixT<4, 4, T> operator-(const MatrixT<4, 4, T> &m, T scalar)
{
    return MatrixT<4, 4, T>(
        m[0] - scalar, m[1] - scalar, m[2] - scalar, m[3] - scalar);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator-(T scalar, const MatrixT<4, 4, T> &m)
{
    return MatrixT<4, 4, T>(
        scalar - m[0], scalar - m[1], scalar - m[2], scalar - m[3]);
}
template <typename T>
constexpr MatrixT<4, 4, T> operator-(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    return MatrixT<4, 4, T>(
        m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
}
template <typename T>
constexpr MatrixT<4, 4, T> operator*(const MatrixT<4, 4, T> &m, T scalar)
{
    return MatrixT<4, 4, T>(
        m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator*(T scalar, const MatrixT<4, 4, T> &m)
{
    return MatrixT<4, 4, T>(
        scalar * m[0], scalar * m[1], scalar * m[2], scalar * m[3]);
}
template <typename T>
constexpr VectorT<4, T> operator*(
    const MatrixT<4, 4, T> &m, const VectorT<4, T> &v)
{
    return VectorT<4, T>(
        m[0].x * v.x + m[1].x * v.y + m[2].x * v.z + m[3].x * v.w,
        m[0].y * v.x + m[1].y * v.y + m[2].y * v.z + m[3].y * v.w,
        m[0].z * v.x + m[1].z * v.y + m[2].z * v.z + m[3].z * v.w,
        m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w * v.w);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator*(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    VectorT<4, T> r0 = {m1[0].x, m1[1].x, m1[2].x, m1[3].x};
    VectorT<4, T> r1 = {m1[0].y, m1[1].y, m1[2].y, m1[3].y};
    VectorT<4, T> r2 = {m1[0].z, m1[1].z, m1[2].z, m1[3].z};
    VectorT<4, T> r3 = {m1[0].w, m1[1].w, m1[2].w, m1[3].w};

    return MatrixT<4, 4, T>(dot(r0, m2[0]), dot(r1, m2[0]), dot(r2, m2[0]),
        dot(r3, m2[0]), dot(r0, m2[1]), dot(r1, m2[1]), dot(r2, m2[1]),
        dot(r3, m2[1]), dot(r0, m2[2]), dot(r1, m2[2]), dot(r2, m2[2]),
        dot(r3, m2[2]), dot(r0, m2[3]), dot(r1, m2[3]), dot(r2, m2[3]),
        dot(r3, m2[3]));
}

template <typename T>
constexpr MatrixT<4, 4, T> operator/(const MatrixT<4, 4, T> &m, T scalar)
{
    return MatrixT<4, 4, T>(
        m[0] / scalar, m[1] / scalar, m[2] / scalar, m[3] / scalar);
}

template <typename T>
constexpr MatrixT<4, 4, T> operator/(T scalar, const MatrixT<4, 4, T> &m)
{
    return MatrixT<4, 4, T>(
        scalar / m[0], scalar / m[1], scalar / m[2], scalar / m[3]);
}

template <typename T>
constexpr const VectorT<4, T> operator/(
    const MatrixT<4, 4, T> &m, const VectorT<4, T> &v)
{
    return inverse(m) * v;
}

template <typename T>
constexpr MatrixT<4, 4, T> operator/(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    return m1 * inverse(m2);
}

template <typename T>
constexpr bool operator==(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    return m1[0] == m2[0] && m1[1] == m2[1] && m1[2] == m2[2] && m1[3] == m2[3];
}

template <typename T>
constexpr bool operator!=(
    const MatrixT<4, 4, T> &m1, const MatrixT<4, 4, T> &m2)
{
    return m1[0] != m2[0] || m1[1] != m2[1] || m1[2] != m2[2] || m1[3] != m2[3];
}
}  // namespace Nyx::Math

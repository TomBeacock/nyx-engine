#pragma once

#include <format>
#include "vector4.h"

namespace Nyx::Math {
template <size_t R, size_t C, typename T>
struct Matrix;
}  // namespace Nyx::Math

namespace Nyx::Math {
using Float4x4 = Matrix<4, 4, float>;
using Double4x4 = Matrix<4, 4, double>;
using Int4x4 = Matrix<4, 4, int>;
using UInt4x4 = Matrix<4, 4, unsigned int>;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
struct Matrix<4, 4, T> {
    using Col = Vector<4, T>;

    const static Matrix<4, 4, T> zero;
    const static Matrix<4, 4, T> one;
    const static Matrix<4, 4, T> identity;

    Matrix() = default;
    template <typename U>
    explicit Matrix(U scalar);
    template <typename U>
    Matrix(const Matrix<4, 4, U> &m);
    template <typename X0, typename Y0, typename Z0, typename W0, typename X1,
        typename Y1, typename Z1, typename W1, typename X2, typename Y2,
        typename Z2, typename W2, typename X3, typename Y3, typename Z3,
        typename W3>
    Matrix(X0 x0, Y0 y0, Z0 z0, W0 w0, X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2,
        Z2 z2, W2 w2, X3 x3, Y3 y3, Z3 z3, W3 w3);
    template <typename V0, typename V1, typename V2, typename V3>
    Matrix(
        Vector<4, V0> v0, Vector<4, V1> v1, Vector<4, V2> v2, Vector<4, V3> v3);

    template <typename U>
    constexpr Matrix<4, 4, T> &operator=(U scalar);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator=(const Matrix<4, 4, U> &m);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator+=(U scalar);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator+=(const Matrix<4, 4, U> &m);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator-=(U scalar);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator-=(const Matrix<4, 4, U> &m);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator*=(U scalar);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator*=(const Matrix<4, 4, U> &m);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator/=(U scalar);
    template <typename U>
    constexpr Matrix<4, 4, T> &operator/=(const Matrix<4, 4, U> &m);

    constexpr Col &operator[](size_t i);
    constexpr const Col &operator[](size_t i) const;

  private:
    Col cols[4];
};

template <typename T>
constexpr Matrix<4, 4, T> operator+(const Matrix<4, 4, T> &m);
template <typename T>
constexpr Matrix<4, 4, T> operator-(const Matrix<4, 4, T> &m);

template <typename T>
constexpr Matrix<4, 4, T> operator+(const Matrix<4, 4, T> &m, T scalar);
template <typename T>
constexpr Matrix<4, 4, T> operator+(T scalar, const Matrix<4, 4, T> &m);
template <typename T>
constexpr Matrix<4, 4, T> operator+(
    const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);
template <typename T>
constexpr Matrix<4, 4, T> operator-(Matrix<4, 4, T> &m, T scalar);
template <typename T>
constexpr Matrix<4, 4, T> operator-(T scalar, const Matrix<4, 4, T> &m);
template <typename T>
constexpr Matrix<4, 4, T> operator-(
    const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);
template <typename T>
constexpr Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &m, T scalar);
template <typename T>
constexpr Matrix<4, 4, T> operator*(T scalar, const Matrix<4, 4, T> &m);
template <typename T>
constexpr Vector<4, T> operator*(
    const Matrix<4, 4, T> &m, const Vector<4, T> &v);
template <typename T>
constexpr Matrix<4, 4, T> operator*(
    const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);
template <typename T>
constexpr Matrix<4, 4, T> operator/(const Matrix<4, 4, T> &m, T scalar);
template <typename T>
constexpr Matrix<4, 4, T> operator/(T scalar, const Matrix<4, 4, T> &m);
template <typename T>
constexpr const Vector<4, T> operator/(
    const Matrix<4, 4, T> &m, const Vector<4, T> &v);
template <typename T>
constexpr Matrix<4, 4, T> operator/(
    const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);

template <typename T>
bool operator==(const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);
template <typename T>
bool operator!=(const Matrix<4, 4, T> &m1, const Matrix<4, 4, T> &m2);
}  // namespace Nyx::Math

#include "matrix4x4.inl"
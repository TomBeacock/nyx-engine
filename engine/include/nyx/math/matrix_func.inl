#include "matrix_func.h"

#include "nyx/math/matrix4x4.h"
#include "nyx/math/vector4.h"

namespace Nyx::Math {
template <typename T>
constexpr Matrix<4, 4, T> transpose(const Matrix<4, 4, T> &m)
{
    return Matrix<4, 4, T>(Vector<4, T>(m[0][0], m[1][0], m[2][0], m[3][0]),
        Vector<4, T>(m[0][1], m[1][1], m[2][1], m[3][1]),
        Vector<4, T>(m[0][2], m[1][2], m[2][2], m[3][2]),
        Vector<4, T>(m[0][3], m[1][3], m[2][3], m[3][3]));
}

template <typename T>
constexpr T determinant(const Matrix<4, 4, T> &m)
{
    T sub_factor0 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    T sub_factor1 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    T sub_factor2 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    T sub_factor3 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    T sub_factor4 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    T sub_factor5 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

    Vector<4, T> coef(+(m[1][1] * sub_factor0 - m[1][2] * sub_factor1 +
                          m[1][3] * sub_factor2),
        -(m[1][0] * sub_factor0 - m[1][2] * sub_factor3 +
            m[1][3] * sub_factor4),
        +(m[1][0] * sub_factor1 - m[1][1] * sub_factor3 +
            m[1][3] * sub_factor5),
        -(m[1][0] * sub_factor2 - m[1][1] * sub_factor4 +
            m[1][2] * sub_factor5));

    return m[0][0] * coef[0] + m[0][1] * coef[1] + m[0][2] * coef[2] +
           m[0][3] * coef[3];
}

template <size_t R, size_t C, typename T>
constexpr Matrix<R, C, T> inverse(const Matrix<R, C, T> &m)
{
    T coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    T coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    T coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

    T coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    T coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    T coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

    T coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    T coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    T coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

    T coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    T coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    T coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

    T coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    T coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    T coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

    T coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    T coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    T coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    Vector<4, T> fac0(coef00, coef00, coef02, coef03);
    Vector<4, T> fac1(coef04, coef04, coef06, coef07);
    Vector<4, T> fac2(coef08, coef08, coef10, coef11);
    Vector<4, T> fac3(coef12, coef12, coef14, coef15);
    Vector<4, T> fac4(coef16, coef16, coef18, coef19);
    Vector<4, T> fac5(coef20, coef20, coef22, coef23);

    Vector<4, T> vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
    Vector<4, T> vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
    Vector<4, T> vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
    Vector<4, T> vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

    Vector<4, T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
    Vector<4, T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
    Vector<4, T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
    Vector<4, T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

    Vector<4, T> signA(+1, -1, +1, -1);
    Vector<4, T> signB(-1, +1, -1, +1);
    Matrix<4, 4, T> inverse(
        inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

    Vector<4, T> row(
        inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

    Vector<4, T> dot0(m[0] * row);
    T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

    T one_over_det = static_cast<T>(1) / dot1;

    return inverse * one_over_det;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<4, 4, T> &m)
{
    return os << std::format("{}", m);
}
}  // namespace Nyx::Math

template <typename T>
constexpr auto std::formatter<Nyx::Math::Matrix<4, 4, T>>::parse(
    std::format_parse_context &ctx)
{
    return ctx.begin();
}

template <typename T>
auto std::formatter<Nyx::Math::Matrix<4, 4, T>>::format(
    const Nyx::Math::Matrix<4, 4, T> &m, std::format_context &ctx) const
{
    return std::format_to(ctx.out(),
        "|{},{},{},{}|\n|{},{},{},{}|\n|{},{},{},{}|\n|{},{},{},{}|", m[0][0],
        m[1][0], m[2][0], m[3][0], m[0][1], m[1][1], m[2][1], m[3][1], m[0][2],
        m[1][2], m[2][2], m[3][2], m[0][3], m[1][3], m[2][3], m[3][3]);
}
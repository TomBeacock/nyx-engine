#pragma once

#include <format>
#include <ostream>

namespace Nyx::Math {
template <size_t R, size_t C, typename T>
struct MatrixT;
}  // namespace Nyx::Math

namespace Nyx::Math {
/**
 * @brief Calculates the transposition of a matrix.
 * @tparam T Value type of the matrix.
 * @tparam R Number of rows in the matrix.
 * @tparam C Number of columns in the matrix.
 * @param m Input matrix.
 * @return The transposed matrix.
 */
template <size_t R, size_t C, typename T>
constexpr MatrixT<C, R, T> transpose(const MatrixT<R, C, T> &m);

/**
 * @brief Calculates the determinant of a matrix.
 * @tparam T Value type of the matrix.
 * @tparam R Number of rows in the matrix.
 * @tparam C Number of columns in the matrix.
 * @param m The matrix.
 * @return The determinant.
 */
template <size_t R, size_t C, typename T>
constexpr T determinant(const MatrixT<R, C, T> &m);

/**
 * @brief Calculates the inversion of a matrix.
 * @tparam T Value type of the matrix.
 * @tparam R Number of rows in the matrix.
 * @tparam C Number of columns in the matrix.
 * @param m The matrix.
 * @return The inverted matrix.
 */
template <size_t R, size_t C, typename T>
constexpr MatrixT<R, C, T> inverse(const MatrixT<R, C, T> &m);

template <size_t R, size_t C, typename T>
constexpr std::string to_string(const MatrixT<R, C, T> &m);

template <size_t R, size_t C, typename T>
inline std::ostream &operator<<(std::ostream &os, const MatrixT<R, C, T> &m);
}  // namespace Nyx::Math

template <typename T>
struct std::formatter<Nyx::Math::MatrixT<4, 4, T>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const Nyx::Math::MatrixT<4, 4, T> &m, std::format_context &ctx)
        const
    {
        return std::format_to(
            ctx.out(),
            "|{},{},{},{}|\n|{},{},{},{}|\n|{},{},{},{}|\n|{},{},{},{}|",
            m[0][0],
            m[1][0],
            m[2][0],
            m[3][0],
            m[0][1],
            m[1][1],
            m[2][1],
            m[3][1],
            m[0][2],
            m[1][2],
            m[2][2],
            m[3][2],
            m[0][3],
            m[1][3],
            m[2][3],
            m[3][3]);
    }
};

#include "matrix_func.inl"
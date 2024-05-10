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
inline std::ostream &operator<<(std::ostream &os, const MatrixT<R, C, T> &m);
}  // namespace Nyx::Math

template <typename T>
struct std::formatter<Nyx::Math::MatrixT<4, 4, T>> {
    constexpr auto parse(std::format_parse_context &ctx);

    auto format(
        const Nyx::Math::MatrixT<4, 4, T> &m, std::format_context &ctx) const;
};

#include "matrix_func.inl"
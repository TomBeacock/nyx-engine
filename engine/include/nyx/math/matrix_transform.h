#pragma once

namespace Nyx::Math {
template <size_t L, typename T>
struct VectorT;

template <typename T>
struct QuaternionT;

template <size_t R, size_t C, typename T>
struct MatrixT;
}  // namespace Nyx::Math

namespace Nyx::Math {
/**
 * @brief Create a translation matrix.
 * @tparam T The value type.
 * @tparam L The dimension of the translation vector.
 * @tparam M The dimension of the matrix.
 * @param t The translation vector.
 * @return The translation matrix.
 */
template <size_t M, size_t L, typename T>
constexpr MatrixT<M, M, T> translate(const VectorT<L, T> &t);

/**
 * @brief Create a rotation matrix.
 * @tparam T The value type.
 * @tparam M The dimension of the translation vector.
 * @tparam L The dimension of the matrix.
 * @param r The rotation quaternion
 * @return The rotation matrix.
 */
template <size_t M, size_t L, typename T>
constexpr MatrixT<M, M, T> rotate(const QuaternionT<T> &r);

/**
 * @brief Create a scale matrix.
 * @tparam T The value type.
 * @tparam L The dimension of the translation vector.
 * @tparam M The dimension of the matrix.
 * @param s The scale vector.
 * @return The scale matrix.
 */
template <size_t M, size_t L, typename T>
constexpr MatrixT<M, M, T> scale(const VectorT<L, T> &s);

/**
 * @brief Create a transformation matrix.
 *
 * Transformation is applied in the order: scale, rotate, translate.
 *
 * @tparam T The value type.
 * @param t The translation vector.
 * @param r The rotation quaternion
 * @param s The scale vector.
 * @return The transformation matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> transformation(
    const VectorT<3, T> &t, const QuaternionT<T> &r, const VectorT<3, T> &s);

/**
 * @brief Create a view matrix.
 * @tparam T The value type.
 * @param t The translation vector.
 * @param r The rotation quaternion.
 * @return The view matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> view(
    const VectorT<3, T> &t, const QuaternionT<T> &r);

/**
 * @brief Create an orthographic projection matrix.
 * @tparam T The value type.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 * @param front The front clipping plane.
 * @param back The back clipping plane.
 * @return The orthographic matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> orthographic(T width, T height, T front, T back);

/**
 * @brief Create an orthographic projection matrix.
 * @tparam T The value type.
 * @param left The left side of the viewport.
 * @param right The right side of the viewport.
 * @param top The top side of the viewport.
 * @param bottom The bottom side of the viewport.
 * @param front The front clipping plane.
 * @param back The back clipping plane.
 * @return The orthographic matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> orthographic(
    T left, T right, T top, T bottom, T front, T back);

/**
 * @brief Create a perspective projection matrix.
 * @tparam T The value type.
 * @param fov The vertical field-of-view (in radians).
 * @param aspect The aspect ratio (width / height)
 * @param front The front clipping plane.
 * @param back The back clipping plane.
 * @return The perspective matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> perspective(T fov, T aspect, T front, T back);

/**
 * @brief Create a perspective projection matrix.
 * @tparam T The value type.
 * @param left The left side of the viewport.
 * @param right The right side of the viewport.
 * @param top The top side of the viewport.
 * @param bottom The bottom side of the viewport.
 * @param front The front clipping plane.
 * @param back The back clipping plane.
 * @return The perspective matrix.
 */
template <typename T>
constexpr MatrixT<4, 4, T> perspective(
    T left, T right, T top, T bottom, T front, T back);
}  // namespace Nyx::Math

#include "matrix_transform.inl"
#pragma once

namespace Nyx::Math {
template <typename T>
struct QuaternionT;

template <size_t L, typename T>
struct VectorT;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <typename T>
T roll(const QuaternionT<T> &q);

template <typename T>
T pitch(const QuaternionT<T> &q);

template <typename T>
T yaw(const QuaternionT<T> &q);

template <typename T>
VectorT<3, T> to_euler_angles(const QuaternionT<T> &q);

template <typename T>
QuaternionT<T> rotate(
    const QuaternionT<T> &q,
    const T &angle,
    const VectorT<3, T> &axis);
}  // namespace Nyx::Math

#include "quaternion_func.inl"
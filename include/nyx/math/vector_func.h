#pragma once

#include <ostream>
#include <string>

namespace Nyx::Math {
template <size_t L, typename T>
struct Vector;
}  // namespace Nyx::Math

namespace Nyx::Math {
template <size_t L, typename T>
inline T angle(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
inline T distance(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
inline T dot(const Vector<L, T> &v1, const Vector<L, T> &v2);

template <size_t L, typename T>
inline Vector<L, T> lerp(
    const Vector<L, T> &v1, const Vector<L, T> &v2, float t);

template <size_t L, typename T>
inline T magnitude(const Vector<L, T> &v);

template <size_t L, typename T>
inline Vector<L, T> normalize(const Vector<L, T> &v);

template <size_t L, typename T>
Vector<L, T> reflect(const Vector<L, T> &v, const Vector<L, T> &normal);

template <size_t L, typename T>
inline T sqr_magnitude(const Vector<L, T> &v);

template <size_t L, typename T>
inline std::string to_string(const Vector<L, T> &v);

template <size_t L, typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector<L, T> &v);
}  // namespace Nyx::Math

#include "vector_func.inl"
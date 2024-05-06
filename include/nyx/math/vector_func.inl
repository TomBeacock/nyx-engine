#include "common.h"
#include "trigonometric.h"
#include "vector_func.h"

#include <format>

namespace Nyx::Math {
template <typename T>
inline T angle(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return acos(clamp(dot(v1, v2), static_cast<T>(-1), static_cast<T>(1)));
}

template <size_t L, typename T>
inline T distance(const Vector<L, T> &v1, const Vector<L, T> &v2)
{
    return magnitude(v2 - v1);
}

template <typename T>
inline T dot(const Vector<2, T> &v1, const Vector<2, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline T dot(const Vector<3, T> &v1, const Vector<3, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T dot(const Vector<4, T> &v1, const Vector<4, T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <size_t L, typename T>
inline Vector<L, T> lerp(
    const Vector<L, T> &v1, const Vector<L, T> &v2, float t)
{
    return v1 + (v2 - v1) * t;
}

template <size_t L, typename T>
inline T magnitude(const Vector<L, T> &v)
{
    return static_cast<T>(std::sqrt(sqr_magnitude(v)));
}

template <size_t L, typename T>
inline Vector<L, T> normalize(const Vector<L, T> &v)
{
    return v / magnitude(v);
}

template <size_t L, typename T>
inline Vector<L, T> reflect(const Vector<L, T> &v, const Vector<L, T> &normal)
{
    return v - normal * dot(v, normal) * static_cast<T>(2);
}

template <size_t L, typename T>
inline T sqr_magnitude(const Vector<L, T> &v)
{
    return dot(v, v);
}

template <size_t L, typename T>
inline std::string to_string(const Vector<L, T> &v)
{
    return std::format("{}", v);
}

template <size_t L, typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector<L, T> &v)
{
    return os << to_string(v);
}
}  // namespace Nyx::Math
#include "common.h"
#include "constants.h"
#include "quaternion_func.h"
#include "trigonometric.h"
#include "vector_func.h"

namespace Nyx::Math {
template <typename T>
T roll(const QuaternionT<T> &q)
{
    const T y = static_cast<T>(2) * (q.x * q.y + q.w * q.z);
    const T x = q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z;

    if (Math::abs(x) < Math::epsilon && Math::abs(y) < Math::epsilon) {
        return static_cast<T>(0);
    }
    return static_cast<T>(Math::atan(y, x));
}

template <typename T>
T pitch(const QuaternionT<T> &q)
{
    const T y = static_cast<T>(2) * (q.y * q.z + q.w * q.x);
    const T x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;

    if (Math::abs(x) < Math::epsilon && Math::abs(y) < Math::epsilon) {
        return static_cast<T>(0);
    }
    return static_cast<T>(Math::atan(y, x));
}

template <typename T>
T yaw(const QuaternionT<T> &q)
{
    T x = static_cast<T>(-2) * (q.x * q.z - q.w * q.y);
    x = Math::clamp(x, static_cast<T>(-1), static_cast<T>(1));
    return static_cast<T>(Math::asin(x));
}

template <typename T>
VectorT<3, T> to_euler_angles(const QuaternionT<T> &q)
{
    return VectorT<3, T>(pitch(q), yaw(q), roll(q));
}
template <typename T>
QuaternionT<T> rotate(
    const QuaternionT<T> &q,
    const T &angle,
    const VectorT<3, T> &axis)
{
    // Ensure axis is normalized
    VectorT<3, T> tmp_axis(axis);
    T m = Math::magnitude(tmp_axis);
    if (Math::abs(m - static_cast<T>(1)) > Math::epsilon) {
        T one_over_m = static_cast<T>(1) / m;
        tmp_axis *= one_over_m;
    }

    const T s = Math::sin(angle * static_cast<T>(0.5));
    const T c = Math::cos(angle * static_cast<T>(0.5));
    const QuaternionT<T> q2(tmp_axis.x * s, tmp_axis.y * s, tmp_axis.z * s, c);
    return q * q2;
}
}  // namespace Nyx::Math
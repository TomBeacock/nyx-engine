#include "matrix_func.h"
#include "matrix_transform.h"
#include "nyx/math/matrix4x4.h"
#include "nyx/math/vector3.h"

#if defined(NYX_GRAPHICS_D3D12)
    #define NYX_CLIP_SPACE_ZERO_ONE
    #define NYX_COORDINATE_SYSTEM_LEFT_HANDED
#endif

#ifdef NYX_COORDINATE_SYSTEM_LEFT_HANDED
    #define NYX_COORDINATE_SYSTEM_Z_SIGN
#else
    #define NYX_COORDINATE_SYSTEM_Z_SIGN -
#endif

namespace Nyx::Math {
template <typename T>
constexpr MatrixT<4, 4, T> translate(const VectorT<3, T> &t)
{
    return MatrixT<4, 4, T>(
        VectorT<4, T>(1, 0, 0, 0),
        VectorT<4, T>(0, 1, 0, 0),
        VectorT<4, T>(0, 0, 1, 0),
        VectorT<4, T>(t.x, t.y, t.z, 1));
}

template <typename T>
constexpr MatrixT<4, 4, T> rotate(const QuaternionT<T> &r)
{
    MatrixT<4, 4, T> result = MatrixT<4, 4, T>::identity;

    T qxx = r.x * r.x;
    T qyy = r.y * r.y;
    T qzz = r.z * r.z;
    T qxz = r.x * r.z;
    T qxy = r.x * r.y;
    T qyz = r.y * r.z;
    T qwx = r.w * r.x;
    T qwy = r.w * r.y;
    T qwz = r.w * r.z;

    result[0][0] = static_cast<T>(1) - static_cast<T>(2) * (qyy + qzz);
    result[0][1] = static_cast<T>(2) * (qxy + qwz);
    result[0][2] = static_cast<T>(2) * (qxz - qwy);
    result[1][0] = static_cast<T>(2) * (qxy - qwz);
    result[1][1] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qzz);
    result[1][2] = static_cast<T>(2) * (qyz + qwx);
    result[2][0] = static_cast<T>(2) * (qxz + qwy);
    result[2][1] = static_cast<T>(2) * (qyz - qwx);
    result[2][2] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qyy);

    return result;
}

template <typename T>
constexpr MatrixT<4, 4, T> scale(const VectorT<3, T> &s)
{
    return MatrixT<4, 4, T>(
        VectorT<4, T>(s.x, 0, 0, 0),
        VectorT<4, T>(0, s.y, 0, 0),
        VectorT<4, T>(0, 0, s.z, 0),
        VectorT<4, T>(0, 0, 0, 1));
}

template <typename T>
constexpr MatrixT<4, 4, T> transformation(
    const VectorT<3, T> &t,
    const QuaternionT<T> &r,
    const VectorT<3, T> &s)
{
    return translate(t) * rotate(r) * scale(s);
}

template <typename T>
constexpr MatrixT<4, 4, T> view(const VectorT<3, T> &t, const QuaternionT<T> &r)
{
    return inverse(translate(t) * rotate(r));
}

template <typename T>
constexpr MatrixT<4, 4, T> orthographic(T width, T height, T front, T back)
{
    T half_width = width / 2;
    T half_height = height / 2;

    MatrixT<4, 4, T> result{};
    result[0][0] = static_cast<T>(1) / half_width;
    result[1][1] = static_cast<T>(1) / half_height;
    result[3][3] = 1;
#ifdef NYX_CLIP_SPACE_ZERO_ONE
    result[2][2] =
        NYX_COORDINATE_SYSTEM_Z_SIGN static_cast<T>(1) / (back - front);
    result[3][2] = -front / (back - front);
#else
    result[2][2] =
        NYX_COORDINATE_SYSTEM_Z_SIGN static_cast<T>(2) / (back - front);
    result[3][2] = -(back + front) / (back - front);
#endif
    return result;
}

template <typename T>
constexpr MatrixT<4, 4, T> orthographic(
    T left,
    T right,
    T top,
    T bottom,
    T front,
    T back)
{
    MatrixT<4, 4, T> result{};
    result[0][0] = static_cast<T>(2) / (right - left);
    result[1][1] = static_cast<T>(2) / (top - bottom);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][3] = 1;
#ifdef NYX_CLIP_SPACE_ZERO_ONE
    result[2][2] =
        NYX_COORDINATE_SYSTEM_Z_SIGN static_cast<T>(2) / (back - front);
    result[3][2] = -front / (back - front);
#else
    result[2][2] =
        NYX_COORDINATE_SYSTEM_Z_SIGN static_cast<T>(1) / (back - front);
    result[3][2] = -(back + front) / (back - front);
#endif
    return result;
}

template <typename T>
constexpr MatrixT<4, 4, T> perspective(T fov, T aspect, T front, T back)
{
    T tangent = tan(fov / static_cast<T>(2));

    MatrixT<4, 4, T> result{};
    result[0][0] = static_cast<T>(1) / (tangent * aspect);
    result[1][1] = static_cast<T>(1) / tangent;
    result[2][3] = NYX_COORDINATE_SYSTEM_Z_SIGN 1;
#ifdef NYX_CLIP_SPACE_ZERO_ONE
    result[2][2] = back / (back - front);
    result[3][2] = -(back * front) / (back - front);
#else
    result[2][2] = (back + front) / (back - front);
    result[3][2] = -(static_cast<T>(2) * back * front) / (back - front);
#endif
    return result;
}

template <typename T>
constexpr MatrixT<4, 4, T> perspective(
    T left,
    T right,
    T top,
    T bottom,
    T front,
    T back)
{
    MatrixT<4, 4, T> result{};
    result[0][0] = (static_cast<T>(2) * front) / (right - left);
    result[1][1] = (static_cast<T>(2) * front) / (top - bottom);
    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][3] = NYX_COORDINATE_SYSTEM_Z_SIGN 1;
#ifdef NYX_CLIP_SPACE_ZERO_ONE
    result[2][2] = back / (back - front);
    result[3][2] = -(back * front) / (back - front);
#else
    result[2][2] = (back + front) / (back - front);
    result[3][2] = -(static_cast<T>(2) * back * front) / (back - front);
#endif
    return result;
}
}  // namespace Nyx::Math
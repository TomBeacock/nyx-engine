#include "matrix_func.h"
#include "matrix_transform.h"
#include "nyx/math/matrix4x4.h"
#include "nyx/math/vector3.h"

namespace Nyx::Math {
template <typename T>
constexpr MatrixT<4, 4, T> translate(const VectorT<3, T> &t)
{
    return MatrixT<4, 4, T>(VectorT<4, T>(1, 0, 0, 0),
        VectorT<4, T>(0, 1, 0, 0), VectorT<4, T>(0, 0, 1, 0),
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
    return MatrixT<4, 4, T>(VectorT<4, T>(s.x, 0, 0, 0),
        VectorT<4, T>(0, s.y, 0, 0), VectorT<4, T>(0, 0, s.z, 0),
        VectorT<4, T>(0, 0, 0, 1));
}

template <typename T>
constexpr MatrixT<4, 4, T> transformation(
    const VectorT<3, T> &t, const QuaternionT<T> &r, const VectorT<3, T> &s)
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
    return MatrixT<4, 4, T>(
        VectorT<4, T>(static_cast<T>(1) / half_width, 0, 0, 0),
        VectorT<4, T>(0, static_cast<T>(1) / half_height, 0, 0),
        VectorT<4, T>(0, 0, static_cast<T>(2) / (back - front), 0),
        VectorT<4, T>(0, 0, -(back + front) / (back - front), 1));
}

template <typename T>
constexpr MatrixT<4, 4, T> orthographic(
    T left, T right, T top, T bottom, T front, T back)
{
    return MatrixT<4, 4, T>(
        VectorT<4, T>(static_cast<T>(2) / (right - left), 0, 0, 0),
        VectorT<4, T>(0, static_cast<T>(2) / (top - bottom), 0, 0),
        VectorT<4, T>(0, 0, static_cast<T>(2) / (back - front), 0),
        VectorT<4, T>(-(right + left) / (right - left),
            -(top + bottom) / (top - bottom), -(back + front) / (back - front),
            1));
}

template <typename T>
constexpr MatrixT<4, 4, T> perspective(T fov, T aspect, T front, T back)
{
    T tangent = tan(fov / static_cast<T>(2));

    return MatrixT<4, 4, T>(
        VectorT<4, T>(static_cast<T>(1) / (tangent * aspect), 0, 0, 0),
        VectorT<4, T>(0, static_cast<T>(1) / tangent, 0, 0),
        VectorT<4, T>(0, 0, (back + front) / (back - front), 1),
        VectorT<4, T>(
            0, 0, -(static_cast<T>(2) * back * front) / (back - front), 0));
}

template <typename T>
constexpr MatrixT<4, 4, T> perspective(
    T left, T right, T top, T bottom, T front, T back)
{
    return MatrixT<4, 4, T>(
        VectorT<4, T>((static_cast<T>(2) * front) / (right - left), 0, 0, 0),
        VectorT<4, T>(0, (static_cast<T>(2) * front) / (top - bottom), 0, 0),
        VectorT<4, T>((right + left) / (right - left),
            (top + bottom) / (top - bottom), (back + front) / (back - front),
            1),
        VectorT<4, T>(
            0, 0, -(static_cast<T>(2) * back * front) / (back - front), 0));
}
}  // namespace Nyx::Math
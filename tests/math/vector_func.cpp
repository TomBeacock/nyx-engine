#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(vector_func, angle)
{
    EXPECT_FLOAT_EQ(pi / 2.0f, angle(Float2(0, 1), Float2(1, 0)));
    EXPECT_FLOAT_EQ(pi, angle(Float2(-1, 0), Float2(1, 0)));
    EXPECT_DOUBLE_EQ(pi / 4.0, angle(Double2(0, 1), normalize(Double2(1, 1))));
}

TEST(vector_func, distance)
{
    EXPECT_FLOAT_EQ(2.0f, distance(Float2(0, 1), Float2(0, 3)));
}

TEST(vector_func, dot)
{
    EXPECT_EQ(11, dot(Int2(1, 2), Int2(3, 4)));
    EXPECT_EQ(32, dot(Int3(1, 2, 3), Int3(4, 5, 6)));
    EXPECT_EQ(70, dot(Int4(1, 2, 3, 4), Int4(5, 6, 7, 8)));
}

TEST(vector_func, lerp)
{
    EXPECT_FLOAT_EQ(
        7.5f, lerp(Float2(5.0f, 0.0f), Float2(10.0f, 0.0f), 0.5f).x);
}

TEST(vector_func, magnitude)
{
    EXPECT_FLOAT_EQ(5, magnitude(Float2(3, 4)));
}

TEST(vector_func, normalization)
{
    EXPECT_EQ(Int2(1, 0), normalize(Int2(10, 0)));
    EXPECT_FLOAT_EQ(0.7071067812f, normalize(Float2(1.0f, 1.0f)).x);
}

TEST(vector_func, reflection)
{
    EXPECT_DOUBLE_EQ(
        -1.0, reflect(Double2(1.0, 0.0), normalize(Double2(1.0, 1.0))).y);
    EXPECT_DOUBLE_EQ(
        1.0, reflect(Double2(0.0, -1.0), normalize(Double2(1.0, 1.0))).x);
}

TEST(vector_func, sqr_magnitude)
{
    EXPECT_FLOAT_EQ(25, sqr_magnitude(Float2(3, 4)));
}
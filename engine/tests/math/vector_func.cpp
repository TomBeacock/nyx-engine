#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(vector_func, angle)
{
    EXPECT_FLOAT_EQ(
        static_cast<float>(pi) / 2.0f, angle(Real2(0, 1), Real2(1, 0)));
    EXPECT_FLOAT_EQ(static_cast<float>(pi), angle(Real2(-1, 0), Real2(1, 0)));
    EXPECT_FLOAT_EQ(static_cast<float>(pi / 4.0),
        angle(Real2(0, 1), normalize(Real2(1, 1))));
}

TEST(vector_func, distance)
{
    EXPECT_FLOAT_EQ(2.0f, distance(Real2(0, 1), Real2(0, 3)));
}

TEST(vector_func, dot)
{
    EXPECT_EQ(11, dot(Int2(1, 2), Int2(3, 4)));
    EXPECT_EQ(32, dot(Int3(1, 2, 3), Int3(4, 5, 6)));
    EXPECT_EQ(70, dot(Int4(1, 2, 3, 4), Int4(5, 6, 7, 8)));
}

TEST(vector_func, lerp)
{
    EXPECT_FLOAT_EQ(7.5f, lerp(Real2(5.0f, 0.0f), Real2(10.0f, 0.0f), 0.5f).x);
}

TEST(vector_func, magnitude)
{
    EXPECT_FLOAT_EQ(5, magnitude(Real2(3, 4)));
}

TEST(vector_func, normalization)
{
    EXPECT_EQ(Int2(1, 0), normalize(Int2(10, 0)));
    EXPECT_FLOAT_EQ(0.7071067812f, normalize(Real2(1.0f, 1.0f)).x);
}

TEST(vector_func, reflection)
{
    EXPECT_FLOAT_EQ(
        -1.0f, reflect(Real2(1.0f, 0.0f), normalize(Real2(1.0f, 1.0f))).y);
    EXPECT_FLOAT_EQ(
        1.0f, reflect(Real2(0.0f, -1.0f), normalize(Real2(1.0f, 1.0f))).x);
}

TEST(vector_func, sqr_magnitude)
{
    EXPECT_FLOAT_EQ(25, sqr_magnitude(Real2(3, 4)));
}
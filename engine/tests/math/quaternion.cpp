#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(quaternion, construction)
{
    EXPECT_EQ(Quaternion(1.0f, 2.0f, 3.0f, 4.0f), Quaternion(1, 2, 3, 4));
}

TEST(quaternion, indexing)
{
    EXPECT_FLOAT_EQ(0.0f, Quaternion::identity[0]);
    EXPECT_FLOAT_EQ(1.0f, Quaternion::identity[3]);
}

TEST(quaternion, unary_operators)
{
    EXPECT_EQ(Quaternion::identity, +Quaternion::identity);
    EXPECT_EQ(Quaternion(0, 0, 0, -1), -Quaternion::identity);
}

TEST(quaternion, binary_operators)
{
    EXPECT_EQ(Quaternion(6, 8, 10, 12),
        Quaternion(1, 2, 3, 4) + Quaternion(5, 6, 7, 8));
    EXPECT_EQ(Quaternion(-4, -4, -4, -4),
        Quaternion(1, 2, 3, 4) - Quaternion(5, 6, 7, 8));
    EXPECT_EQ(Quaternion(2, 4, 6, 8), Quaternion(1, 2, 3, 4) * 2.0f);
    EXPECT_EQ(Quaternion(1, 2, 3, 4), Quaternion(2, 4, 6, 8) / 2.0f);
}
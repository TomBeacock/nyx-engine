#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(vector4, construction)
{
    EXPECT_EQ(Int4(5, 5, 5, 5), Int4(5));
}

TEST(vector4, indexing)
{
    EXPECT_EQ(1, Int4(1, 2, 3, 4)[0]);
    EXPECT_EQ(2, Int4(1, 2, 3, 4)[1]);
    EXPECT_EQ(3, Int4(1, 2, 3, 4)[2]);
    EXPECT_EQ(4, Int4(1, 2, 3, 4)[3]);
}

TEST(vector4, unary_operators)
{
    EXPECT_EQ(Int4(1, 2, 3, 4), +Int4(1, 2, 3, 4));
    EXPECT_EQ(Int4(-1, -2, -3, -4), -Int4(1, 2, 3, 4));
}

TEST(vector4, binary_operators)
{
    EXPECT_EQ(Int4(2, 3, 4, 5), Int4(1, 2, 3, 4) + 1);
    EXPECT_EQ(Int4(6, 8, 10, 12), Int4(1, 2, 3, 4) + Int4(5, 6, 7, 8));
    EXPECT_EQ(Int4(0, 1, 2, 3), Int4(1, 2, 3, 4) - 1);
    EXPECT_EQ(Int4(-4, -4, -4, -4), Int4(1, 2, 3, 4) - Int4(5, 6, 7, 8));
    EXPECT_EQ(Int4(2, 4, 6, 8), Int4(1, 2, 3, 4) * 2);
    EXPECT_EQ(Int4(5, 12, 21, 32), Int4(1, 2, 3, 4) * Int4(5, 6, 7, 8));
    EXPECT_EQ(Int4(1, 2, 3, 4), Int4(2, 4, 6, 8) / 2);
    EXPECT_EQ(Int4(2, 3, 4, 5), Int4(4, 9, 16, 25) / Int4(2, 3, 4, 5));
}
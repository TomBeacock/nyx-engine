#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(vector2, construction)
{
    EXPECT_EQ(Int2(5, 5), Int2(5));
}

TEST(vector2, indexing)
{
    EXPECT_EQ(1, Int2(1, 2)[0]);
    EXPECT_EQ(2, Int2(1, 2)[1]);
}

TEST(vector2, unary_operators)
{
    EXPECT_EQ(Int2(1, 2), +Int2(1, 2));
    EXPECT_EQ(Int2(-1, -2), -Int2(1, 2));
}

TEST(vector2, binary_operators)
{
    EXPECT_EQ(Int2(2, 3), Int2(1, 2) + 1);
    EXPECT_EQ(Int2(4, 6), Int2(1, 2) + Int2(3, 4));
    EXPECT_EQ(Int2(0, 1), Int2(1, 2) - 1);
    EXPECT_EQ(Int2(-2, -2), Int2(1, 2) - Int2(3, 4));
    EXPECT_EQ(Int2(2, 4), Int2(1, 2) * 2);
    EXPECT_EQ(Int2(3, 8), Int2(1, 2) * Int2(3, 4));
    EXPECT_EQ(Int2(1, 2), Int2(2, 4) / 2);
    EXPECT_EQ(Int2(2, 4), Int2(4, 12) / Int2(2, 3));
}
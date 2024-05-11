#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(vector3, construction)
{
    EXPECT_EQ(Int3(5, 5, 5), Int3(5));
}

TEST(vector3, indexing)
{
    EXPECT_EQ(1, Int3(1, 2, 3)[0]);
    EXPECT_EQ(2, Int3(1, 2, 3)[1]);
    EXPECT_EQ(3, Int3(1, 2, 3)[2]);
}

TEST(vector3, unary_operators)
{
    EXPECT_EQ(Int3(1, 2, 3), +Int3(1, 2, 3));
    EXPECT_EQ(Int3(-1, -2, -3), -Int3(1, 2, 3));
}

TEST(vector3, binary_operators)
{
    EXPECT_EQ(Int3(2, 3, 4), Int3(1, 2, 3) + 1);
    EXPECT_EQ(Int3(5, 7, 9), Int3(1, 2, 3) + Int3(4, 5, 6));
    EXPECT_EQ(Int3(0, 1, 2), Int3(1, 2, 3) - 1);
    EXPECT_EQ(Int3(-3, -3, -3), Int3(1, 2, 3) - Int3(4, 5, 6));
    EXPECT_EQ(Int3(2, 4, 6), Int3(1, 2, 3) * 2);
    EXPECT_EQ(Int3(4, 10, 18), Int3(1, 2, 3) * Int3(4, 5, 6));
    EXPECT_EQ(Int3(1, 2, 3), Int3(2, 4, 6) / 2);
    EXPECT_EQ(Int3(2, 4, 5), Int3(4, 12, 20) / Int3(2, 3, 4));
}
#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(matrix4x4, construction)
{
    EXPECT_EQ(Int4x4(Int4(5, 5, 5, 5), Int4(5, 5, 5, 5), Int4(5, 5, 5, 5),
                  Int4(5, 5, 5, 5)),
        Int4x4(5));
}

TEST(vecmatrix4x4tor2, indexing)
{
    EXPECT_EQ(0, Int4x4::identity[0][1]);
    EXPECT_EQ(1, Int4x4::identity[1][1]);
}

TEST(matrix4x4, unary_operators)
{
    EXPECT_EQ(Int4x4::identity, +Int4x4::identity);
    EXPECT_EQ(Int4x4(Int4(-1, 0, 0, 0), Int4(0, -1, 0, 0), Int4(0, 0, -1, 0),
                  Int4(0, 0, 0, -1)),
        -Int4x4::identity);
}

TEST(matrix4x4, binary_operators)
{
    EXPECT_EQ(Int4x4(Int4(2, 1, 1, 1), Int4(1, 2, 1, 1), Int4(1, 1, 2, 1),
                  Int4(1, 1, 1, 2)),
        Int4x4::identity + 1);
    EXPECT_EQ(Int4x4(Int4(2, 1, 1, 1), Int4(1, 2, 1, 1), Int4(1, 1, 2, 1),
                  Int4(1, 1, 1, 2)),
        Int4x4::identity + Int4x4::one);
    EXPECT_EQ(Int4x4(Int4(0, 1, 1, 1), Int4(1, 0, 1, 1), Int4(1, 1, 0, 1),
                  Int4(1, 1, 1, 0)),
        Int4x4::one - Int4x4::identity);
    EXPECT_EQ(Int4x4(Int4(2, 0, 0, 0), Int4(0, 2, 0, 0), Int4(0, 0, 2, 0),
                  Int4(0, 0, 0, 2)),
        Int4x4::identity * 2);
    EXPECT_EQ(Int4x4(Int4(96, 24, 58, 90), Int4(68, 56, 95, 107),
                  Int4(69, 18, 71, 81), Int4(69, 52, 92, 142)),
        Int4x4(Int4(5, 0, 3, 1), Int4(2, 6, 8, 8), Int4(6, 2, 1, 5),
            Int4(1, 0, 4, 6)) *
            Int4x4(Int4(7, 1, 9, 5), Int4(5, 8, 4, 3), Int4(8, 2, 3, 7),
                Int4(0, 6, 8, 9)));
    EXPECT_EQ(Int4x4::identity, Int4x4(Int4(2, 0, 0, 0), Int4(0, 2, 0, 0),
                                    Int4(0, 0, 2, 0), Int4(0, 0, 0, 2)) /
                                    2);
}
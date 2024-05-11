#include <gtest/gtest.h>
#include <nyx/math.h>

using namespace Nyx::Math;

TEST(matrix_func, transpose)
{
    EXPECT_EQ(Int4x4(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16),
        transpose(
            Int4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));
}

TEST(matrix_func, determinant)
{
    EXPECT_EQ(0, determinant(Int4x4(
                     1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)));
    EXPECT_EQ(-4,
        determinant(Int4x4(2, 0, 0, 0, 1, -1, 0, 0, 0, 0, 2, 0, -3, 1, -5, 1)));
}

TEST(matrix_func, inverse)
{
    EXPECT_EQ(Float4x4(0.5f, 0, 0, 0, 0.5f, -1, 0, 0, 0, 0, 0.5f, 0, 1.0f, 1.0f,
                  2.5f, 1.0f),
        inverse(Float4x4(2, 0, 0, 0, 1, -1, 0, 0, 0, 0, 2, 0, -3, 1, -5, 1)));
}
#include "nyx/math.h"

#include <gtest/gtest.h>

using namespace Nyx::Math;

TEST(matrix_transform, translate)
{
    EXPECT_EQ(Int4x4(Int4{1, 0, 0, 0}, Int4{0, 1, 0, 0}, Int4{0, 0, 1, 0},
                  Int4{3, -5, 7, 1}),
        translate(Int3(3, -5, 7)));
}

TEST(matrix_transform, scale)
{
    EXPECT_EQ(Int4x4(Int4{3, 0, 0, 0}, Int4{0, -5, 0, 0}, Int4{0, 0, 7, 0},
                  Int4{0, 0, 0, 1}),
        scale(Int3(3, -5, 7)));
}
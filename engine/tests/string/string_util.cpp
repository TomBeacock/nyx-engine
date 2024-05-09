#include "nyx/string/string_util.h"

#include <gtest/gtest.h>

TEST(string_util, utf8_to_wstring)
{
    ASSERT_EQ(L"Hello world", Nyx::utf8_to_wstring(u8"Hello world"));
    ASSERT_EQ(L"£", Nyx::utf8_to_wstring(u8"£"));
}
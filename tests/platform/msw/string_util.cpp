#include "platform/msw/string_util.cpp"

#include <gtest/gtest.h>

TEST(string_util, utf8_to_wstring)
{
    ASSERT_EQ(L"Hello world", Nyx::MSW::utf8_to_wstring(u8"Hello world"));
    ASSERT_EQ(L"£", Nyx::MSW::utf8_to_wstring(u8"£"));
}
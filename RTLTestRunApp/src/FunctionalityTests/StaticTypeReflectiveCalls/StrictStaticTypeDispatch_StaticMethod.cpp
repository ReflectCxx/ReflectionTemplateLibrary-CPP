
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StrictStaticTypeRtl_static_method, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringS, std::string(const char)> reverse_string = reverseString->targetT<StringS>()
                                                                                         .argsT<const char>()
                                                                                         .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StringS, std::string(char*)> reverse_string = reverseString->targetT<StringS>()
                                                                                    .argsT<char*>()
                                                                                    .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StringS, std::string(const char*)> reverse_string = reverseString->targetT<const StringS>()
                                                                                                .argsT<const char*>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StringS, std::string(std::string)> reverse_string = reverseString->targetT<const StringS>()
                                                                                                .argsT<std::string>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::function<std::string(const char*)> reverse_string = reverseString->argsT<const char*>()
                                                                                   .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(std::string)> reverse_string = reverseString->argsT<std::string>()
                                                                                   .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRB);
            auto exp_str = std::string(STRB_REVERSE) + SUFFIX_std_string + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string()> reverse_string = reverseString->argsT<>()
                                                                        .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string();
            auto exp_str = std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}
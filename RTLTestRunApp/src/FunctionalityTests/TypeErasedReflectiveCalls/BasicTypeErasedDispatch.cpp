
#include <complex>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(BasicTypeErasedDispatch, default_resolutions_to_call_by_value_overloads)
	{
		auto reverseStringOpt = cxx::mirror().getFunction(str_reverseString);
		ASSERT_TRUE(reverseStringOpt);

		rtl::Function reverseString = *reverseStringOpt;
		{
			auto [err, robj] = reverseString(const_cast<char*>(STRA));
			EXPECT_TRUE(err == rtl::error::SignatureMismatch);
		} {
			auto [err, robj] = reverseString(STRA);
			
			EXPECT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_cptr;
			EXPECT_EQ(retStr, expStr);
		} {
			auto [err, robj] = reverseString(std::string(STRA));

			EXPECT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string;
			EXPECT_EQ(retStr, expStr);
		} {
			std::string str = STRA;
			auto [err, robj] = reverseString(&str);

			EXPECT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_ptr;
			EXPECT_EQ(retStr, expStr);
		} {
			const std::string str = STRA;
			auto [err, robj] = reverseString(&str);

			EXPECT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_cptr;
			EXPECT_EQ(retStr, expStr);
		}
	}
}
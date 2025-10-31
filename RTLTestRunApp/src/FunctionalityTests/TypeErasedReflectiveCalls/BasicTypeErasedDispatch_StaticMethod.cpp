#include <gtest/gtest.h>
#include <string_view>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(BasicTypeErasedRtl_static_method, implicit_resolutions_to_call_by_value_overloads)
	{
		std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
		ASSERT_TRUE(optStringUtil);

		std::optional<rtl::Method> reverseStrOpt = optStringUtil->getMethod(str_reverseString);
		ASSERT_TRUE(reverseStrOpt);
		EXPECT_FALSE(reverseStrOpt->hasSignature<char*>());
		{
			rtl::method<StringS, rtl::Return(char*)> reverseString = reverseStrOpt.value()
																				  .targetT<StringS>()
																				  .argsT<char*>()
																				  .returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(StringS())(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::InvalidCaller);
				EXPECT_TRUE(robj.isEmpty());
			} {
				auto [err, robj] = reverseString.bind<char*>(StringS())(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::InvalidCaller);
				EXPECT_TRUE(robj.isEmpty());
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<const char*>());
		{
			rtl::method<StringS, rtl::Return(const char*)> reverseString = reverseStrOpt.value().targetT<StringS>()
																						.argsT<const char*>()
																						.returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(StringS())(STRA);
				EXPECT_EQ(err, rtl::error::InvalidStaticMethodCaller);
			} 
		}
			//{
		//		auto [err, robj] = reverseString.bind<const char*>(StringS())(STRA);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr;
		//		EXPECT_EQ(retStr, expStr);
		//	}
		//}
		//EXPECT_TRUE(reverseStrOpt->hasSignature<std::string>());
		//{
		//	rtl::method<StringS, rtl::Return(std::string)> reverseString = reverseStrOpt.value().targetT<StringS>()
		//		.argsT<std::string>()
		//		.returnT<>();
		//	EXPECT_TRUE(reverseString);
		//	{
		//		auto [err, robj] = reverseString(StringS())(STRA);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string;
		//		EXPECT_EQ(retStr, expStr);
		//	} {
		//		auto [err, robj] = reverseString.bind<std::string>(StringS())(STRA);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string;
		//		EXPECT_EQ(retStr, expStr);
		//	}
		//}
		//EXPECT_TRUE(reverseStrOpt->hasSignature<std::string*>());
		//{
		//	rtl::method<StringS, rtl::Return(std::string*)> reverseString = reverseStrOpt.value().targetT<StringS>()
		//		.argsT<std::string*>()
		//		.returnT<>();
		//	EXPECT_TRUE(reverseString);
		//	{
		//		std::string str = STRA;
		//		auto [err, robj] = reverseString(StringS())(&str);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr;
		//		EXPECT_EQ(retStr, expStr);
		//	} {
		//		std::string str = STRA;
		//		auto [err, robj] = reverseString.bind<std::string*>(StringS())(&str);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr;
		//		EXPECT_EQ(retStr, expStr);
		//	}
		//}
		//EXPECT_TRUE(reverseStrOpt->hasSignature<const std::string*>());
		//{
		//	rtl::method<StringS, rtl::Return(const std::string*)> reverseString = reverseStrOpt.value().targetT<StringS>()
		//		.argsT<const std::string*>()
		//		.returnT<>();
		//	EXPECT_TRUE(reverseString);
		//	{
		//		const std::string str = STRA;
		//		auto [err, robj] = reverseString(StringS())(&str);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr;
		//		EXPECT_EQ(retStr, expStr);
		//	} {
		//		const std::string str = STRA;
		//		auto [err, robj] = reverseString.bind<const std::string*>(StringS())(&str);

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr;
		//		EXPECT_EQ(retStr, expStr);
		//	}
		//}
		//EXPECT_TRUE(reverseStrOpt->hasSignature<>());
		//{
		//	rtl::method<StringS, rtl::Return()> reverseString = reverseStrOpt.value().targetT<StringS>()
		//		.argsT<>()
		//		.returnT<>();
		//	EXPECT_TRUE(reverseString);
		//	{
		//		auto [err, robj] = reverseString(StringS())();

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void;
		//		EXPECT_EQ(retStr, expStr);
		//	} {
		//		auto [err, robj] = reverseString.bind(StringS())();

		//		EXPECT_EQ(err, rtl::error::None);
		//		ASSERT_FALSE(robj.isEmpty());
		//		ASSERT_TRUE(robj.canViewAs<std::string>());

		//		const std::string& retStr = robj.view<std::string>()->get();
		//		std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void;
		//		EXPECT_EQ(retStr, expStr);
		//	}
		//}
	}
}
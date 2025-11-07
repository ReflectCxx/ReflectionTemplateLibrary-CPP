
#include <rtl/rtl.h>
#include <gtest/gtest.h>
#include <string_view>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(ReturnTypeErased_rtl_static_method, using_wrong_class_n_callable_apis_for_static_method)
    {
        {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);   // has only static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::method<StringS, rtl::Return(std::string)> reverse_string = reverseString.value()
                                                                                             .targetT<StringS>()
                                                                                             .argsT<std::string>()
                                                                                             .returnT<>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidStaticMethodCaller);

				auto [err, robj] = reverse_string(StringS())(std::string());
				EXPECT_EQ(err, rtl::error::InvalidStaticMethodCaller);
				EXPECT_TRUE(robj.isEmpty());
            } {
                rtl::function<rtl::Return(std::string)> reverse_string = static_cast<rtl::Function>(reverseString.value())
                                                                                                                 .argsT<std::string>()
                                                                                                                 .returnT<>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidStaticMethodCaller);
			
				auto [err, robj] = reverse_string(std::string());
				EXPECT_EQ(err, rtl::error::InvalidStaticMethodCaller);
				EXPECT_TRUE(robj.isEmpty());
			}
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringC::struct_);   // doesn't have any static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);

            rtl::static_method<rtl::Return(std::string)> reverse_string = reverseString.value()
                                                                                       .argsT<std::string>()
                                                                                       .returnT<>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidNonStaticMethodCaller);

			auto [err, robj] = reverse_string(std::string());
			EXPECT_EQ(err, rtl::error::InvalidNonStaticMethodCaller);
			EXPECT_TRUE(robj.isEmpty());
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);   // doesn't have any static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::static_method<rtl::Return(std::string)> reverse_string = reverseString.value()
                                                                                           .argsT<std::string>()
                                                                                           .returnT<>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidNonStaticMethodCaller);

				auto [err, robj] = reverse_string(std::string());
				EXPECT_EQ(err, rtl::error::InvalidNonStaticMethodCaller);
				EXPECT_TRUE(robj.isEmpty());
            }
        }
    }


	TEST(ReturnTypeErased_rtl_static_method, implicit_resolutions_to_call_by_value_overloads)
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
			rtl::method<StringS, rtl::Return(const char*)> reverseString = reverseStrOpt.value()
																						.targetT<StringS>()
																						.argsT<const char*>()
																						.returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(StringS())(STRA);
				EXPECT_EQ(err, rtl::error::InvalidStaticMethodCaller);
			} 
		} {
			rtl::static_method<rtl::Return(const char*)> reverseString = reverseStrOpt.value()
																					  .argsT<const char*>()
																					  .returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString(STRA);
				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<std::string>());
		{
			rtl::static_method<rtl::Return(std::string)> reverseString = reverseStrOpt.value()
																					  .argsT<std::string>()
																				      .returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind<std::string>()(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<std::string*>());
		{
			rtl::static_method<rtl::Return(std::string*)> reverseString = reverseStrOpt.value()
																					   .argsT<std::string*>()
																					   .returnT<>();
			EXPECT_TRUE(reverseString);
			{
				std::string str = STRA;
				auto [err, robj] = reverseString(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				std::string str = STRA;
				auto [err, robj] = reverseString.bind<std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<const std::string*>());
		{
			rtl::static_method<rtl::Return(const std::string*)> reverseString = reverseStrOpt.value()
																							 .argsT<const std::string*>()
																							 .returnT<>();
			EXPECT_TRUE(reverseString);
			{
				const std::string str = STRA;
				auto [err, robj] = reverseString(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				const std::string str = STRA;
				auto [err, robj] = reverseString.bind<const std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<>());
		{
			rtl::static_method<rtl::Return()> reverseString = reverseStrOpt.value()
																		   .argsT<>()
																		   .returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString();

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind()();

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
	}
}
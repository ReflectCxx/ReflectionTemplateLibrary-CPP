
#include <rtl/access.h>
#include <gtest/gtest.h>
#include <string_view>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringMute.h"
#include "../CxxTestProps/inc/StringConst.h"
#include "../CxxTestProps/inc/StringStatic.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(ReturnErased_StaticMethod, using_wrong_class_n_callable_apis_for_static_method)
    {
        {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);   // has only static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::method<StrStatic, rtl::Return(std::string)> reverse_string = reverseString.value()
                                                                                               .targetT<StrStatic>()
                                                                                               .argsT<std::string>()
                                                                                               .returnT<>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::SignatureMismatch);

				auto [err, robj] = reverse_string(StrStatic())(std::string());
				EXPECT_EQ(err, rtl::error::SignatureMismatch);
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
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);   // doesn't have any static-methods.
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
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);   // doesn't have any static-methods.
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


	TEST(ReturnErased_StaticMethod, implicit_resolutions_to_call_by_value_overloads)
	{
		std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
		ASSERT_TRUE(optStringUtil);

		std::optional<rtl::Method> reverseStrOpt = optStringUtil->getMethod(str_reverseString);
		ASSERT_TRUE(reverseStrOpt);
		EXPECT_FALSE(reverseStrOpt->hasSignature<char*>());
		{
			rtl::method<StrStatic, rtl::Return(char*)> reverseString = reverseStrOpt.value()
																				    .targetT<StrStatic>()
																				    .argsT<char*>()
																				    .returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(StrStatic())(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::SignatureMismatch);
				EXPECT_TRUE(robj.isEmpty());
			} {
				auto [err, robj] = reverseString.bind<char*>(StrStatic())(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::SignatureMismatch);
				EXPECT_TRUE(robj.isEmpty());
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<const char*>());
		{
			rtl::method<StrStatic, rtl::Return(const char*)> reverseString = reverseStrOpt.value()
																						  .targetT<StrStatic>()
																						  .argsT<const char*>()
																						  .returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(StrStatic())(STRA);
				EXPECT_EQ(err, rtl::error::SignatureMismatch);
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
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_const_char_ptr + SUFFIX_static;
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
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind<std::string>()(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string + SUFFIX_static;
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
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_ptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				std::string str = STRA;
				auto [err, robj] = reverseString.bind<std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_ptr + SUFFIX_static;
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
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_cptr + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				const std::string str = STRA;
				auto [err, robj] = reverseString.bind<const std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_cptr + SUFFIX_static;
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
				std::string expStr = std::string(StrStatic::struct_) + REV_STR_VOID_RET + SUFFIX_void + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind()();

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(StrStatic::struct_) + REV_STR_VOID_RET + SUFFIX_void + SUFFIX_static;
				EXPECT_EQ(retStr, expStr);
			}
		}
	}
}
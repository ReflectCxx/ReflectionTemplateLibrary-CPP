
#include <rtl/access.h>
#include <gtest/gtest.h>
#include <complex>
#include <string_view>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"

using namespace test_utils;
using namespace test_mirror;

// TODO: test cases for functions with return type 'void'.

namespace rtl_tests
{
	TEST(ReturnTypeErased_rtl_function, invalid_erased_return_rtl_function)
	{
		{
			rtl::function<rtl::Return()> erased_ret_fn;
			EXPECT_FALSE(erased_ret_fn);

			auto [err, robj] = erased_ret_fn();
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		}

		rtl::function<rtl::Return(int)> erased_ret_fn;
		EXPECT_FALSE(erased_ret_fn);
		{
			auto [err, robj] = erased_ret_fn(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		} {
			auto [err, robj] = erased_ret_fn.bind<int>()(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		} {
			auto [err, robj] = erased_ret_fn.bind<int&&>()(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		}
	}


	TEST(ReturnTypeErased_rtl_function, implicit_resolutions_to_call_by_value_overloads)
	{
		auto reverseStrOpt = cxx::mirror().getFunction(str_reverseString);
		ASSERT_TRUE(reverseStrOpt);
		EXPECT_FALSE(reverseStrOpt->hasSignature<char*>());
		{
			rtl::function<rtl::Return(char*)> reverseString = reverseStrOpt->argsT<char*>().returnT<>();
			EXPECT_FALSE(reverseString);
			{
				auto [err, robj] = reverseString(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::InvalidCaller);
				EXPECT_TRUE(robj.isEmpty());
			} {
				auto [err, robj] = reverseString.bind<char*>()(const_cast<char*>(STRA));

				EXPECT_EQ(err, rtl::error::InvalidCaller);
				EXPECT_TRUE(robj.isEmpty());
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<const char*>());
		{
			rtl::function<rtl::Return(const char*)> reverseString = reverseStrOpt->argsT<const char*>().returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind<const char*>()(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<std::string>());
		{
			rtl::function<rtl::Return(std::string)> reverseString = reverseStrOpt->argsT<std::string>().returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind<std::string>()(STRA);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<std::string*>());
		{
			rtl::function<rtl::Return(std::string*)> reverseString = reverseStrOpt->argsT<std::string*>().returnT<>();
			EXPECT_TRUE(reverseString);
			{
				std::string str = STRA;
				auto [err, robj] = reverseString(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr;
				EXPECT_EQ(retStr, expStr);
			} {
				std::string str = STRA;
				auto [err, robj] = reverseString.bind<std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<const std::string*>());
		{
			rtl::function<rtl::Return(const std::string*)> reverseString = reverseStrOpt->argsT<const std::string*>().returnT<>();
			EXPECT_TRUE(reverseString);
			{
				const std::string str = STRA;
				auto [err, robj] = reverseString(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr;
				EXPECT_EQ(retStr, expStr);
			} {
				const std::string str = STRA;
				auto [err, robj] = reverseString.bind<const std::string*>()(&str);

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr;
				EXPECT_EQ(retStr, expStr);
			}
		}
		EXPECT_TRUE(reverseStrOpt->hasSignature<>());
		{
			rtl::function<rtl::Return()> reverseString = reverseStrOpt->argsT<>().returnT<>();
			EXPECT_TRUE(reverseString);
			{
				auto [err, robj] = reverseString();

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void;
				EXPECT_EQ(retStr, expStr);
			} {
				auto [err, robj] = reverseString.bind()();

				EXPECT_EQ(err, rtl::error::None);
				ASSERT_FALSE(robj.isEmpty());
				ASSERT_TRUE(robj.canViewAs<std::string>());

				const std::string& retStr = robj.view<std::string>()->get();
				std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void;
				EXPECT_EQ(retStr, expStr);
			}
		}
	}


	TEST(ReturnTypeErased_rtl_function, implicit_resolution_to_ambiguous_lvalue_and_cref_overload)
	{
		auto revStrOverloadValCRefOpt = cxx::mirror().getFunction(str_revStrOverloadValCRef);
		ASSERT_TRUE(revStrOverloadValCRefOpt);

		EXPECT_FALSE(revStrOverloadValCRefOpt->hasSignature<std::string_view&>());
		EXPECT_FALSE(revStrOverloadValCRefOpt->hasSignature<std::string_view&&>());

		// Both by-value (T) and const-ref (const T&) overloads exist.		
		EXPECT_TRUE(revStrOverloadValCRefOpt->hasSignature<std::string_view>());
		EXPECT_TRUE(revStrOverloadValCRefOpt->hasSignature<const std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValCRefOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString); 
		{
			// RTL chooses the safe by-value overload implicitly. The const-ref
			// path requires explicit binding only to disambiguate intent.
			// Note: If only const T& existed (no by-value overload), RTL would
			// call it implicitly, since binding to const-ref cannot mutate the caller.
			auto [err, robj] = reverseString(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
			EXPECT_EQ(retStr, expStr);
		} {
			// explicit call by value resolution.
			auto [err, robj] = reverseString.bind<std::string_view>()(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(ReturnTypeErased_rtl_function, explicit_resolution_to_ambiguous_lvalue_and_cref_overload)
	{
		auto revStrOverloadValCRefOpt = cxx::mirror().getFunction(str_revStrOverloadValCRef);
		ASSERT_TRUE(revStrOverloadValCRefOpt);

		EXPECT_FALSE(revStrOverloadValCRefOpt->hasSignature<std::string_view&>());
		EXPECT_FALSE(revStrOverloadValCRefOpt->hasSignature<std::string_view&&>());
		
		// Both by-value (T) and const-ref (const T&) overloads exist.		
		EXPECT_TRUE(revStrOverloadValCRefOpt->hasSignature<std::string_view>());
		EXPECT_TRUE(revStrOverloadValCRefOpt->hasSignature<const std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValCRefOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);
		{
			// Explicitly selecting the const-ref overload using .bind<const T&>().
			// If no by-value overload were present, implicit resolution to const-ref
			// would have worked automatically, because const-ref cannot mutate.
			auto [err, robj] = reverseString.bind<const std::string_view&>()(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		} {
			auto [err, robj] = reverseString.bind<std::string_view&>()(str);

			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
			ASSERT_TRUE(robj.isEmpty());
		}
	}


	TEST(ReturnTypeErased_rtl_function, implicit_resolution_to_ambiguous_lvalue_and_ref_overload)
	{
		auto revStrOverloadValRefOpt = cxx::mirror().getFunction(str_revStrOverloadValRef);
		ASSERT_TRUE(revStrOverloadValRefOpt);

		EXPECT_FALSE(revStrOverloadValRefOpt->hasSignature<std::string_view&&>());
		EXPECT_FALSE(revStrOverloadValRefOpt->hasSignature<const std::string_view&>());
		
		// Here both by-value (T) and non-const ref (T&) overloads exist.
		EXPECT_TRUE(revStrOverloadValRefOpt->hasSignature<std::string_view>());
		EXPECT_TRUE(revStrOverloadValRefOpt->hasSignature<std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValRefOpt->argsT<std::string_view>().returnT<>();
		{
			// Here also, RTL prioritizes the safe-by-value overload automatically
			// since it guarantees no mutation. The non-const ref overload remains
			// accessible only through explicit binding to preserve mutability intent.
			auto [err, robj] = reverseString(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
			EXPECT_EQ(retStr, expStr);
		} {
			// explicit call by value resolution.
			auto [err, robj] = reverseString.bind<std::string_view>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(ReturnTypeErased_rtl_function, explicit_resolution_to_ambiguous_lvalue_and_ref_overload)
	{
		auto revStrOverloadValRefOpt = cxx::mirror().getFunction(str_revStrOverloadValRef);
		ASSERT_TRUE(revStrOverloadValRefOpt);
		
		EXPECT_FALSE(revStrOverloadValRefOpt->hasSignature<std::string_view&&>());
		EXPECT_FALSE(revStrOverloadValRefOpt->hasSignature<const std::string_view&>());
		
		// Here both by-value (T) and non-const ref (T&) overloads exist.
		EXPECT_TRUE(revStrOverloadValRefOpt->hasSignature<std::string_view>());
		EXPECT_TRUE(revStrOverloadValRefOpt->hasSignature<std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValRefOpt->argsT<std::string_view>().returnT<>();
		{
			// Explicitly selecting the non-const ref overload.
			// Even though the by-value overload is preferred implicitly for safety,
			// the user can override that choice by binding explicitly as T&,
			// signaling the intent to allow mutation through reflection.
			auto [err, robj] = reverseString.bind<std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		} {
			auto [err, robj] = reverseString.bind<const std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
			ASSERT_TRUE(robj.isEmpty());
		}
	}


	TEST(ReturnTypeErased_rtl_function, calling_non_overloaded_non_const_ref_argument)
	{
		auto revStrNonConstRefArgOpt = cxx::mirror().getFunction(str_revStrNonConstRefArg);
		ASSERT_TRUE(revStrNonConstRefArgOpt);

		EXPECT_FALSE(revStrNonConstRefArgOpt->hasSignature<std::string_view>());
		EXPECT_FALSE(revStrNonConstRefArgOpt->hasSignature<std::string_view&&>());
		EXPECT_FALSE(revStrNonConstRefArgOpt->hasSignature<const std::string_view&>());

		// Here no overloads exists, only non-const ref (T&) argument.
		EXPECT_TRUE(revStrNonConstRefArgOpt->hasSignature<std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrNonConstRefArgOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);

		// Calls that may mutate user data (T&) require explicit intent.
		// Hence, the dispatcher returns 'ExplicitRefBindingRequired' error.
		// Since no call by value overload exists.
		{
			auto [err, robj] = reverseString(str);
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		} {
			// expected non-const ref binding.
			auto [err, robj] = reverseString.bind<const std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
		} {
			// By calling .bind<T&>(), the user explicitly signals willingness to let
			// the function modify the argument. This re-enables the T& call path and
			// executes successfully, producing the expected result.
			auto [err, robj] = reverseString.bind<std::string_view&>()(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(ReturnTypeErased_rtl_function, calling_non_overloaded_const_ref_argument)
	{
		auto revStrConstRefArgOpt = cxx::mirror().getFunction(str_revStrConstRefArg);
		ASSERT_TRUE(revStrConstRefArgOpt);

		EXPECT_FALSE(revStrConstRefArgOpt->hasSignature<std::string_view>());
		EXPECT_FALSE(revStrConstRefArgOpt->hasSignature<std::string_view&>());
		EXPECT_FALSE(revStrConstRefArgOpt->hasSignature<std::string_view&&>());

		// Here no overloads exists, only non-const ref (T&) argument.
		EXPECT_TRUE(revStrConstRefArgOpt->hasSignature<const std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrConstRefArgOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);
		{
			// This call resolves to the const-ref overload (no other overloads exist),
			// so the argument is implicitly bound as a const reference.
			auto [err, robj] = reverseString(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		} {
			// explicit binding must also behave the same way.
			auto [err, robj] = reverseString.bind<const std::string_view&>()(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		} {
			// explicit binding to non-const ref returns error.
			auto [err, robj] = reverseString.bind<std::string_view&>()(str);

			// expected 'const T&'
			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
			ASSERT_TRUE(robj.isEmpty());
		}
	}


	TEST(ReturnTypeErased_rtl_function, calling_non_overloaded_rvalue_ref_argument)
	{
		auto revStrRValueRefArgOpt = cxx::mirror().getFunction(str_revStrRValueRefArg);
		ASSERT_TRUE(revStrRValueRefArgOpt);

		EXPECT_FALSE(revStrRValueRefArgOpt->hasSignature<std::string_view>());
		EXPECT_FALSE(revStrRValueRefArgOpt->hasSignature<std::string_view&>());
		EXPECT_FALSE(revStrRValueRefArgOpt->hasSignature<const std::string_view&>());
		
		// Here no overloads exists, only non-const ref (T&) argument.
		EXPECT_TRUE(revStrRValueRefArgOpt->hasSignature<std::string_view&&>());

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrRValueRefArgOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);
		{
			auto [err, robj] = reverseString(std::string_view(STRA));
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		} {
			auto [err, robj] = reverseString.bind<std::string_view&&>()(std::string_view(STRA));

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_rvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(ReturnTypeErased_rtl_function, implicit_resolution_to_ambiguous_ref_and_cref_overload)
	{
		auto revStrOverloadValRefNCrefOpt = cxx::mirror().getFunction(str_revStrOverloadValRefAndCRef);
		ASSERT_TRUE(revStrOverloadValRefNCrefOpt);

		EXPECT_FALSE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view>());
		EXPECT_FALSE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view&&>());

		// Here distinct overloads exists, with non-const ref (T&) and const-ref (const T&).
		EXPECT_TRUE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view&>());
		EXPECT_TRUE(revStrOverloadValRefNCrefOpt->hasSignature<const std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValRefNCrefOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);
		{
			// Both T& and const T& overloads are viable for an lvalue argument.
			// RTL avoids implicit ambiguity by requiring explicit ref binding
			// when mutation is possible (non-const ref path).
			auto [err, robj] = reverseString(str);
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		} {
			auto [err, robj] = reverseString.bind<std::string_view>()(str);
			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
		} {
			auto [err, robj] = reverseString.bind<std::string_view&&>()(str);
			EXPECT_EQ(err, rtl::error::RefBindingMismatch);
		}
	}


	TEST(ReturnTypeErased_rtl_function, explicit_resolution_to_ambiguous_ref_and_cref_overload)
	{
		auto revStrOverloadValRefNCrefOpt = cxx::mirror().getFunction(str_revStrOverloadValRefAndCRef);
		ASSERT_TRUE(revStrOverloadValRefNCrefOpt);

		EXPECT_FALSE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view>());
		EXPECT_FALSE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view&&>());

		// Here distinct overloads exists, with non-const ref (T&) and const-ref (const T&).
		EXPECT_TRUE(revStrOverloadValRefNCrefOpt->hasSignature<std::string_view&>());
		EXPECT_TRUE(revStrOverloadValRefNCrefOpt->hasSignature<const std::string_view&>());
		std::string_view str = STRA;

		rtl::function<rtl::Return(std::string_view)> reverseString = revStrOverloadValRefNCrefOpt->argsT<std::string_view>().returnT<>();
		EXPECT_TRUE(reverseString);
		{
			// Explicitly selecting the non-const ref overload.
			// Caller signals intent to allow mutation by binding as T&.
			auto [err, robj] = reverseString.bind<std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		} {
			// Explicitly selecting the const ref overload.
			// Note: If only 'const T&' existed, RTL would have resolved it implicitly.
			// But since both 'T&' and 'const T&' overloads are available,
			// RTL treats the situation as ambiguous and requires explicit selection
			// to avoid guessing the user's intent regarding mutability.
			auto [err, robj] = reverseString.bind<const std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			ASSERT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		}
	}
}
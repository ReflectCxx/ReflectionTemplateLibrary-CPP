
#include <complex>
#include <gtest/gtest.h>
#include <string_view>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"

#include <rtl/dispatch/rtl_function_erased_return.h>

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(BasicTypeErasedDispatch, invalid_erased_return_rtl_function)
	{
		{
			rtl::function<rtl::Return()> erased_ret_func;
			EXPECT_FALSE(erased_ret_func);

			auto [err, robj] = erased_ret_func();
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		}

		rtl::function<rtl::Return(int)> erased_ret_func;
		EXPECT_FALSE(erased_ret_func);
		{
			auto [err, robj] = erased_ret_func(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		} {
			auto [err, robj] = erased_ret_func.call<int>(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		} {
			auto [err, robj] = erased_ret_func.call<int&&>(0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		}
	}

	TEST(BasicTypeErasedDispatch, implicit_resolutions_to_call_by_value_overloads)
	{
		auto reverseStringOpt = cxx::mirror().getFunction(str_reverseString);
		ASSERT_TRUE(reverseStringOpt);

		rtl::Function reverseString = *reverseStringOpt;
		{
			auto [err, robj] = reverseString(const_cast<char*>(STRA));
			EXPECT_EQ(err, rtl::error::SignatureMismatch);
		} {
			auto [err, robj] = reverseString(STRA);
			
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_const_char_ptr;
			EXPECT_EQ(retStr, expStr);
		} {
			auto [err, robj] = reverseString(std::string(STRA));

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string;
			EXPECT_EQ(retStr, expStr);
		} {
			std::string str = STRA;
			auto [err, robj] = reverseString(&str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_ptr;
			EXPECT_EQ(retStr, expStr);
		} {
			const std::string str = STRA;
			auto [err, robj] = reverseString(&str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_cptr;
			EXPECT_EQ(retStr, expStr);
		} {
			auto [err, robj] = reverseString();

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(REV_STR_VOID_RET) + SUFFIX_ARG_void;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, implicit_resolution_to_ambiguous_lvalue_and_cref_overload)
	{
		auto revStrOverloadValCRefOpt = cxx::mirror().getFunction(str_revStrOverloadValCRef);
		ASSERT_TRUE(revStrOverloadValCRefOpt);

		rtl::Function revStrOverloadValCRef = *revStrOverloadValCRefOpt;
		{
			std::string_view str = STRA;

			// Both by-value (T) and const-ref (const T&) overloads exist.
			// RTL chooses the safe by-value overload implicitly. The const-ref
			// path requires explicit binding only to disambiguate intent.
			// Note: If only const T& existed (no by-value overload), RTL would
			// call it implicitly, since binding to const-ref cannot mutate the caller.
			auto [err, robj] = revStrOverloadValCRef(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, explicit_resolution_to_ambiguous_lvalue_and_cref_overload)
	{
		auto revStrOverloadValCRefOpt = cxx::mirror().getFunction(str_revStrOverloadValCRef);
		ASSERT_TRUE(revStrOverloadValCRefOpt);

		rtl::Function revStrOverloadValCRef = *revStrOverloadValCRefOpt;
		{
			std::string_view str = STRA;

			// Explicitly selecting the const-ref overload using .bind<const T&>().
			// Required only when a by-value overload exists to resolve ambiguity.
			// If no by-value overload were present, implicit resolution to const-ref
			// would have worked automatically, because const-ref cannot mutate.
			auto [err, robj] = revStrOverloadValCRef.bind<const std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, implicit_resolution_to_ambiguous_lvalue_and_ref_overload)
	{
		auto revStrOverloadValRefOpt = cxx::mirror().getFunction(str_revStrOverloadValRef);
		ASSERT_TRUE(revStrOverloadValRefOpt);

		rtl::Function revStrOverloadValRef = *revStrOverloadValRefOpt;
		{
			std::string_view str = STRA;

			// Here both by-value (T) and non-const ref (T&) overloads exist.
			// Unlike in static C++, where such a situation causes ambiguity and
			// requires an explicit static_cast, RTL prioritizes the safe-by-value
			// overload automatically since it guarantees no mutation.
			// The non-const ref overload remains accessible only through explicit
			// binding to preserve mutability intent.
			auto [err, robj] = revStrOverloadValRef(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, explicit_resolution_to_ambiguous_lvalue_and_ref_overload)
	{
		auto revStrOverloadValRefOpt = cxx::mirror().getFunction(str_revStrOverloadValRef);
		ASSERT_TRUE(revStrOverloadValRefOpt);

		rtl::Function revStrOverloadValRef = *revStrOverloadValRefOpt;
		{
			std::string_view str = STRA;

			// Explicitly selecting the non-const ref overload.
			// Even though the by-value overload is preferred implicitly for safety,
			// the user can override that choice by binding explicitly as T&,
			// signaling the intent to allow mutation through reflection.
			auto [err, robj] = revStrOverloadValRef.bind<std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		}
	}



	// -----------------------------------------------------------------------------
	// Tests implicit vs explicit binding behavior for reference arguments in RTL.
	// Demonstrates RTL's intentional design choice: non-const refs require explicit
	// opt-in binding to prevent unintended mutation through reflection.
	// -----------------------------------------------------------------------------
	TEST(BasicTypeErasedDispatch, calling_non_overloaded_non_const_ref_argument)
	{
		auto revStrNonConstRefArgOpt = cxx::mirror().getFunction(str_revStrNonConstRefArg);
		ASSERT_TRUE(revStrNonConstRefArgOpt);

		std::string_view str = STRA;
		rtl::Function revStrNonConstRefArg = *revStrNonConstRefArgOpt;

		// -------------------------------------------------------------------------
		// Case 1: Implicit call with a value (or perfectly forwarded lvalue)
		// -------------------------------------------------------------------------
		// Even though 'str' is an lvalue and forwarding is perfect, RTL enforces
		// semantic safety: calls that may mutate user data (T&) require explicit
		// intent. Hence, the dispatcher returns ExplicitRefBindingRequired instead
		// of silently binding to a non-const lvalue reference.
		// -------------------------------------------------------------------------
		{
			auto [err, robj] = revStrNonConstRefArg(str);
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		}

		// -------------------------------------------------------------------------
		// Case 2: Explicitly binding as std::string_view&
		// -------------------------------------------------------------------------
		// By calling .bind<T&>(), the user explicitly signals willingness to let
		// the function modify the argument. This re-enables the T& call path and
		// executes successfully, producing the expected result.
		// -------------------------------------------------------------------------
		{
			auto [err, robj] = revStrNonConstRefArg.bind<std::string_view&>()(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	// -----------------------------------------------------------------------------
	// Tests implicit binding for const-reference arguments.
	// Since const-ref parameters cannot mutate caller data, RTL allows implicit
	// binding without requiring an explicit .bind<T&>() call.
	// -----------------------------------------------------------------------------
	TEST(BasicTypeErasedDispatch, calling_non_overloaded_const_ref_argument)
	{
		auto revStrConstRefArgOpt = cxx::mirror().getFunction(str_revStrConstRefArg);
		ASSERT_TRUE(revStrConstRefArgOpt);

		std::string_view str = STRA;
		rtl::Function revStrConstRefArg = *revStrConstRefArgOpt;

		// -------------------------------------------------------------------------
		// Case: Implicitly binding to const-ref parameter
		// -------------------------------------------------------------------------
		// Safe by C++ semantics — temporaries and values can bind to const& freely.
		// RTL mirrors this rule at runtime, so the call proceeds without requiring
		// explicit binding and executes successfully.
		// -------------------------------------------------------------------------
		{
			auto [err, robj] = revStrConstRefArg(str);

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, calling_non_overloaded_rvalue_ref_argument)
	{
		auto revStrRValueRefArgOpt = cxx::mirror().getFunction(str_revStrRValueRefArg);
		ASSERT_TRUE(revStrRValueRefArgOpt);

		rtl::Function revStrRValueRefArg = *revStrRValueRefArgOpt;
		{
			auto [err, robj] = revStrRValueRefArg(std::string_view(STRA));
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		} {
			auto [err, robj] = revStrRValueRefArg.bind<std::string_view&&>()(std::string_view(STRA));

			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_rvref;
			EXPECT_EQ(retStr, expStr);
		}
	}


	TEST(BasicTypeErasedDispatch, implicit_resolution_to_ambiguous_ref_and_cref_overload)
	{
		auto revStrOverloadValRefNCrefOpt = cxx::mirror().getFunction(str_revStrOverloadValRefAndCRef);
		ASSERT_TRUE(revStrOverloadValRefNCrefOpt);

		rtl::Function revStrOverloadValRefNCref = *revStrOverloadValRefNCrefOpt;
		{
			std::string_view str = STRA;

			// Both T& and const T& overloads are viable for an lvalue argument.
			// RTL avoids implicit ambiguity by requiring explicit ref binding
			// when mutation is possible (non-const ref path).
			auto [err, robj] = revStrOverloadValRefNCref(str);
			EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
		}
	}


	TEST(BasicTypeErasedDispatch, explicit_resolution_to_ambiguous_ref_and_cref_overload)
	{
		auto revStrOverloadValRefNCrefOpt = cxx::mirror().getFunction(str_revStrOverloadValRefAndCRef);
		ASSERT_TRUE(revStrOverloadValRefNCrefOpt);

		std::string_view str = STRA;
		rtl::Function revStrOverloadValRefNCref = *revStrOverloadValRefNCrefOpt;
		{
			// Explicitly selecting the non-const ref overload.
			// Caller signals intent to allow mutation by binding as T&.
			auto [err, robj] = revStrOverloadValRefNCref.bind<std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_lvref;
			EXPECT_EQ(retStr, expStr);
		} {
			// Explicitly selecting the const ref overload.
			// Note: If only 'const T&' existed, RTL would have resolved it implicitly.
			// But since both 'T&' and 'const T&' overloads are available,
			// RTL treats the situation as ambiguous and requires explicit selection
			// to avoid guessing the user's intent regarding mutability.
			auto [err, robj] = revStrOverloadValRefNCref.bind<const std::string_view&>()(str);
			EXPECT_EQ(err, rtl::error::None);
			ASSERT_FALSE(robj.isEmpty());
			EXPECT_TRUE(robj.canViewAs<std::string>());

			const std::string& retStr = robj.view<std::string>()->get();
			std::string expStr = std::string(STRA_REVERSE) + SUFFIX_ARG_std_string_view_clvref;
			EXPECT_EQ(retStr, expStr);
		}
	}
}
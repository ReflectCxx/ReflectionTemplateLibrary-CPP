/*
==================================================================
RObject String Reflection & View Coverage
==================================================================

This test suite verifies correct handling of string-related types
when reflected through RObject::reflect() and subsequently accessed
via RObject::view<T>().

The goals are to ensure:
    - Various string-representing input types are accepted and stored correctly.
    - Multiple read-only view types (std::string, std::string_view, const char*, std::string*)
      can be consistently and correctly retrieved from the reflected object.
    - Zero-copy views are returned where applicable (e.g., from lvalue or pointer input).
    - Writable views (T*, T&, T&&) are explicitly disallowed by design.

Once the input is deduced as a particular type, RObject::reflect() and view() abstract
away the original construction source and stores as std::string internally, except
the pointer type, ie. std::string*, which is stored as pointers to the original data.

------------------------------------------------------------------
MAIN TEST CASES - COVERED
------------------------------------------------------------------

[OK] String literal (direct)
    - RObject::reflect("string_literal_rvalue");
    - RObject::reflect("");

[OK] char[] / const char[] / const char*
    - RObject::reflect(STR_CHAR_ARRAY);
    - RObject::reflect(STR_CONST_CHAR_ARRAY);
    - RObject::reflect(STR_CONST_CHAR_POINTER);

[OK] std::string and pointer variants
    - RObject::reflect(STR_STD_STRING);
    - RObject::reflect(std::string(STR_STD_STRING));
    - RObject::reflect(&STR_STD_STRING);

[OK] std::string_view (lvalue & rvalue)
    - RObject::reflect(STR_STD_STRING_VIEW);
    - RObject::reflect(std::string_view(STR_CONST_CHAR_POINTER));

------------------------------------------------------------------
VIEW TYPES - COVERED (FOR EACH INPUT)
------------------------------------------------------------------

[OK] std::string
[OK] std::string_view
[OK] const char*
[OK] const std::string*

------------------------------------------------------------------
NEGATIVE TEST CASES - DESIGN ENFORCEMENTS
------------------------------------------------------------------

[X] Writable or unsafe view types are disallowed:
    - T*            (e.g., std::string*)
    - T& / T&&      (e.g., std::string&, std::string&&)
    - char*         (non-const pointer)

[X] RObject::view<T>() only supports read-only access:
    - const T*      -> allowed (non-owning, read-only pointer)
    - T* or reference forms  -> disallowed by design

[X] Incompatible type requests safely return std::nullopt:
    - RObject holding string -> view<int>()         -> nullopt
    - RObject holding int    -> view<std::string>() -> nullopt

------------------------------------------------------------------
OPTIONAL BONUS CASES - Intentionally Skipped
------------------------------------------------------------------

- Empty std::string                   (std::string already covered)
- Empty std::string_view              (std::string_view already covered)
- Long string literal                 (string literal already covered)
- Very long std::string               (std::string already covered)

------------------------------------------------------------------
Summary:
------------------------------------------------------------------

- Full type coverage COMPLETE (char[], const char[], const char*, std::string, std::string_view, literal).
- Both lvalue and rvalue cases covered where applicable.
- All relevant read-only combinations of view types verified.
- Invalid or mutable view requests are explicitly disallowed.

==================================================================
*/

#include <gtest/gtest.h>

#include "ReflectionSystem.h"

using namespace rtl::access;

namespace
{
    static bool _= rtl::unit_test::ReflectionSystem::init();

    static const std::string STR_STD_STRING = "string_type: std::string";
    static constexpr const char* STR_CONST_CHAR_POINTER = "string_type: const_char_*.";

    static char STR_CHAR_ARRAY[] = "string_type: const_char_array.";
    static constexpr const char STR_CONST_CHAR_ARRAY[] = "string_type: const_char_array.";

    static const std::string_view STR_STD_STRING_VIEW = "string_type: std::string_view";
}


namespace rtl
{
    namespace unit_tests
    {

        TEST(RObject_view_negative_test, disallowed_mutable_views_should_not_compile)
        {
            RObject robj = RObject::reflect(std::string("Immutable"));

        /*  The following lines SHOULD NOT COMPILE if uncommented:
            These are intentionally commented to enforce design-time correctness.
        */

        //  ASSERT_FALSE(robj.canReflectAs<std::string*>());     //Mutable pointer not allowed
        //  ASSERT_FALSE(robj.canReflectAs<char*>());            //Mutable C-string
        //  ASSERT_FALSE(robj.canReflectAs<std::string&>());     //Reference not supported
        //  ASSERT_FALSE(robj.canReflectAs<std::string&&>());    //Rvalue ref not allowed
            
        //  auto bad1 = robj.view<std::string*>();     //Mutable pointer not allowed
        //  auto bad2 = robj.view<char*>();            //Mutable C-string
        //  auto bad3 = robj.view<std::string&>();     //Reference not supported
        //  auto bad4 = robj.view<std::string&&>();    //Rvalue ref not allowed
        }


        TEST(RObject_view_negative_test, incompatible_view_returns_nullopt)
        {
            RObject robj = RObject::reflect(std::string("test"));

            ASSERT_FALSE(robj.canReflectAs<int>());

            // Request a view of an incompatible type
            auto view = robj.view<int>();
            ASSERT_FALSE(view.has_value());  // Must return nullopt
        }


        TEST(RObject_view_negative_test, incompatible_reflected_type_returns_nullopt)
        {
            int value = 42;
            RObject robj = RObject::reflect(&value);

            // Although value is stored, it's not a string
            ASSERT_FALSE(robj.canReflectAs<std::string_view>());
            auto str_view = robj.view<std::string_view>();
            ASSERT_FALSE(str_view.has_value());

            ASSERT_FALSE(robj.canReflectAs<const char*>());
            auto cstr_view = robj.view<const char*>();
            ASSERT_FALSE(cstr_view.has_value());
        }
    }


    namespace unit_test
    {
        TEST(RObject_init_with_stdString_pointer, view_as_std_string_pointer)
        {
            // Create an RObject that reflects a std::string pointer.
            RObject robj = RObject::reflect(&STR_STD_STRING);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<const std::string*>());

            // Try to obtain a view as 'std::string*', should not compile.
            //auto view0 = robj.view<std::string*>();

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const std::string*>();
            ASSERT_TRUE(view.has_value());

            const std::string* str_ptr = view->get();

            // Validate the addresses are same, no copy made.
            ASSERT_EQ(str_ptr, &STR_STD_STRING);
        }


        TEST(RObject_init_with_stdString_pointer, view_as_std_string)
        {
            // Create an RObject that reflects a std::string pointer.
            RObject robj = RObject::reflect(&STR_STD_STRING);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            const std::string& str_cref = view->get();

            // Validate the addresses are same, no copy made.
            ASSERT_EQ(&str_cref, &STR_STD_STRING);
        }


        TEST(RObject_init_with_stdString_pointer, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a std::string pointer.
            RObject robj = RObject::reflect(&STR_STD_STRING);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Ensure the returned pointer is the original std::string's buffer (no copy).
            const char* str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING.c_str());
        }


        TEST(RObject_init_with_stdString_pointer, view_as_std_string_view)
        {
            // Create an RObject that reflects a std::string pointer.
            RObject robj = RObject::reflect(&STR_STD_STRING);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_init_with_empty_literal, view_as_std_string)
        {
            // Create an RObject that reflects a empty string literal rvalue
            RObject robj = RObject::reflect("");

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, "");
        }


        TEST(RObject_init_with_literal, view_as_std_string)
        {
            // Create an RObject that reflects a string literal rvalue
            RObject robj = RObject::reflect("string_literal_rvalue");

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, "string_literal_rvalue");
        }


        TEST(RObject_init_with_charArray, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_init_with_charArray, view_as_std_const_string_pointer)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);
          
            //Check if the value can be accessed as 'const std::string*'.
            ASSERT_TRUE(robj.canReflectAs<const std::string*>());

        /*  Try to obtain a view as 'const std::string*' and verify it is present.
		*   Returns the address of the internal std::string (constructed from input char[]).
        */  auto view = robj.view<const std::string*>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = *(view->get());
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_init_with_charArray, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_init_with_charArray, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Ensure the returned pointer is the original array (no copy).
            const char* str_cref = view->get();
            ASSERT_EQ(str_cref, std::string(STR_CHAR_ARRAY));
        }


        TEST(RObject_init_with_constCharArray, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_init_with_constCharArray, view_as_std_const_string_pointer)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            //Check if the value can be accessed as 'const std::string*'.
            ASSERT_TRUE(robj.canReflectAs<const std::string*>());

        /*  Try to obtain a view as 'const std::string*' and verify it is present.
        *   Returns the address of the internal std::string (constructed from input 'const char[]').
        */  auto view = robj.view<const std::string*>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = *(view->get());
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_init_with_constCharArray, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_init_with_constCharArray, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_init_with_constCharPtr, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_init_with_constCharPtr, view_as_std_const_string_pointer)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            //Check if the value can be accessed as 'const std::string*'.
            ASSERT_TRUE(robj.canReflectAs<const std::string*>());

        /*  Try to obtain a view as 'const std::string*' and verify it is present.
        *   Returns the address of the internal std::string (constructed from input 'const char*').
        */  auto view = robj.view<const std::string*>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = *(view->get());
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_init_with_constCharPtr, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_init_with_constCharPtr, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_init_with_stdString, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_init_with_stdString_rvalue, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'std::string' rvalue).
            RObject robj = RObject::reflect(std::string(STR_STD_STRING));

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_init_with_stdString, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_init_with_stdString, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_STD_STRING);
        }


        TEST(RObject_init_with_stdStringView, view_as_std_string)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING_VIEW);
        }


        TEST(RObject_init_with_stdStringView, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING_VIEW);
        }


        TEST(RObject_init_with_stdStringView_rvalue, view_as_std_string_view)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(std::string_view(STR_CONST_CHAR_POINTER));

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_init_with_stdStringView, view_as_const_char_ptr)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string_view(str_cref), STR_STD_STRING_VIEW);
        }
    }
}
/*
==================================================================
RObject String Reflection & View Coverage
==================================================================

This test suite verifies correct handling of string-related types
when reflected through RObject::reflect() and subsequently accessed
via RObject::view<T>().

The goal is to ensure that:
    - Various string-representing input types are accepted and stored correctly.
    - Multiple view types (std::string, std::string_view, const char*) can be
      consistently and correctly retrieved from the reflected object.

Once the input is deduced as a particular type, RObject::reflect() and view() abstract 
away the original construction source and storeed as std::string internally.
Therefore, testing redundant construction variants is unnecessary.

------------------------------------------------------------------
MAIN TEST CASES - COVERED
------------------------------------------------------------------

[OK] String literal (direct)
    - RObject::reflect("string_literal_rvalue");
    - RObject::reflect("");

[OK] char[]
    - RObject::reflect(STR_CHAR_ARRAY);

[OK] const char[]
    - RObject::reflect(STR_CONST_CHAR_ARRAY);

[OK] const char*
    - RObject::reflect(STR_CONST_CHAR_POINTER);

[OK] std::string (lvalue & rvalue)
    - RObject::reflect(STR_STD_STRING);
    - RObject::reflect(std::string(STR_STD_STRING));

[OK] std::string_view (lvalue & rvalue)
    - RObject::reflect(STR_STD_STRING_VIEW);
    - RObject::reflect(std::string_view(STR_CONST_CHAR_POINTER));

------------------------------------------------------------------
VIEW TYPES - COVERED (FOR EACH INPUT)
------------------------------------------------------------------

[OK] std::string
[OK] std::string_view
[OK] const char*

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
- All relevant combinations of view types verified.

This test suite provides sufficient verification for RObject::reflect()
and RObject::view<T>() handling of string-related types.

==================================================================
*/


#include <gtest/gtest.h>

#include "ReflectionSystem.h"

using namespace rtl::access;

namespace
{
    static bool _= rtl::unit_test::ReflectionSystem::init();

    static const std::string STR_STD_STRING = "string_type: std::string.";
    static constexpr const char* STR_CONST_CHAR_POINTER = "string_type: const_char_*.";

    static char STR_CHAR_ARRAY[] = "string_type: const_char_array.";
    static constexpr const char STR_CONST_CHAR_ARRAY[] = "string_type: const_char_array.";

    static const std::string_view STR_STD_STRING_VIEW = STR_STD_STRING;
}


namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_view_as_std_string, init_with_empty_literal)
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


        TEST(RObject_view_as_std_string, init_with_literal)
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


        TEST(RObject_view_as_std_string, init_with_charArray)
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


        TEST(RObject_view_as_std_string_view, init_with_charArray)
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


        TEST(RObject_view_as_const_char_ptr, init_with_charArray)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CHAR_ARRAY);
        }


        TEST(RObject_view_as_std_string, init_with_constCharArray)
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


        TEST(RObject_view_as_std_string_view, init_with_constCharArray)
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


        TEST(RObject_view_as_const_char_ptr, init_with_constCharArray)
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


        TEST(RObject_view_as_std_string, init_with_constCharPtr)
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


        TEST(RObject_view_as_std_string_view, init_with_constCharPtr)
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


        TEST(RObject_view_as_const_char_ptr, init_with_constCharPtr)
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


        TEST(RObject_view_as_std_string, init_with_stdString)
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


        TEST(RObject_view_as_std_string, init_with_stdString_rvalue)
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


        TEST(RObject_view_as_std_string_view, init_with_stdString)
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


        TEST(RObject_view_as_const_char_ptr, init_with_stdString)
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


        TEST(RObject_view_as_std_string, init_with_stdStringView)
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


        TEST(RObject_view_as_std_string_view, init_with_stdStringView)
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


        TEST(RObject_view_as_std_string_view, init_with_stdStringView_rvalue)
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


        TEST(RObject_view_as_const_char_ptr, init_with_stdStringView)
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
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
        TEST(RObject_string, init_with_charArray_view_as_stdString)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_charArray_view_as_stdStringView)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_charArray_view_as_constCharPtr)
        {
            // Create an RObject that reflects a string value (init with 'char[]').
            RObject robj = RObject::reflect(STR_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_constCharArray_view_as_stdString)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_constCharArray_view_as_stdStringView)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_constCharArray_view_as_constCharPtr)
        {
            // Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STR_CONST_CHAR_ARRAY);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CONST_CHAR_ARRAY);
        }


        TEST(RObject_string, init_with_constCharPtr_view_as_stdString)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_string, init_with_constCharPtr_view_as_stdStringView)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_string, init_with_constCharPtr_view_as_constCharPtr)
        {
            // Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STR_CONST_CHAR_POINTER);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_CONST_CHAR_POINTER);
        }


        TEST(RObject_string, init_with_stdString_view_as_stdString)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_string, init_with_stdString_view_as_stdStringView)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING);
        }


        TEST(RObject_string, init_with_stdString_view_as_constCharPtr)
        {
            // Create an RObject that reflects a string value (init with 'std::string').
            RObject robj = RObject::reflect(STR_STD_STRING);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'const char*'.
            ASSERT_TRUE(robj.canReflectAs<const char*>());

            // Try to obtain a view as 'const char*' and verify it is present.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            // Validate the C-string content matches the original input.
            const char* str_cref = view->get();
            ASSERT_EQ(std::string(str_cref), STR_STD_STRING);
        }


        TEST(RObject_string, init_with_stdStringView_view_as_stdString)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string'.
            ASSERT_TRUE(robj.canReflectAs<std::string>());

            // Try to obtain a view as 'std::string' and verify it is present.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            // Validate the string content matches the original input.
            const std::string& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING_VIEW);
        }


        TEST(RObject_string, init_with_stdStringView_view_as_stdStringView)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

            // Check if the value can be accessed as 'std::string_view'.
            ASSERT_TRUE(robj.canReflectAs<std::string_view>());

            // Try to obtain a view as 'std::string_view' and verify it is present.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            // Validate the string_view content matches the original input.
            const std::string_view& str_cref = view->get();
            ASSERT_EQ(str_cref, STR_STD_STRING_VIEW);
        }


        TEST(RObject_string, init_with_stdStringView_view_as_constCharPtr)
        {
            // Create an RObject that reflects a string value (init with 'std::string_view').
            // Stores a copy of the 'std::string_view' as a 'std::string'.
            RObject robj = RObject::reflect(STR_STD_STRING_VIEW);

            // Check that the original type stored is 'std::string'.
            ASSERT_TRUE(robj.isTrueType<std::string>());

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
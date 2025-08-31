
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "GlobalTestUtils.h"

using namespace rtl;

namespace
{
    static const std::string STR_STD_STRING = "string_type: std::string";
    static constexpr const char* STR_CONST_CHAR_POINTER = "string_type: const_char_*.";

    static char STR_CHAR_ARRAY[] = "string_type: const_char_array.";
    static constexpr const char STR_CONST_CHAR_ARRAY[] = "string_type: const_char_array.";

    static const std::string_view STR_STD_STRING_VIEW = "string_type: std::string_view";

    //initialize RTL, necessary for RObject conversions to work.
    static auto _= rtl::CxxMirror({/*..empty..*/});
}


namespace rtl_tests
{

    TEST(RObject_view_negative_test, disallowed_mutable_views_should_not_compile)
    {
        RObject robj = rtl::reflect(std::string("Immutable"));

    /*  The following lines SHOULD NOT COMPILE if uncommented:
        These are intentionally commented to enforce design-time correctness.
    */

    /*  ASSERT_FALSE(robj.canViewAs<std::string*>());     //Mutable pointer not allowed
        ASSERT_FALSE(robj.canViewAs<char*>());            //Mutable C-string
        ASSERT_FALSE(robj.canViewAs<std::string&>());     //Reference not supported
        ASSERT_FALSE(robj.canViewAs<std::string&&>());    //Rvalue ref not allowed
            
        auto bad1 = robj.view<std::string*>();     //Mutable pointer not allowed
        auto bad2 = robj.view<char*>();            //Mutable C-string
        auto bad3 = robj.view<std::string&>();     //Reference not supported
        auto bad4 = robj.view<std::string&&>();    //Rvalue ref not allowed
    */
    }


    TEST(RObject_view_negative_test, incompatible_view_returns_nullopt)
    {
        RObject robj = rtl::reflect(std::string("test"));

        ASSERT_FALSE(robj.canViewAs<int>());

        // Request a view of an incompatible type
        auto view = robj.view<int>();
        ASSERT_FALSE(view.has_value());  // Must return nullopt
    }


    TEST(RObject_view_negative_test, incompatible_reflected_type_returns_nullopt)
    {
        int value = 42;
        RObject robj = rtl::reflect(&value);

        // Although value is stored, it's not a string
        ASSERT_FALSE(robj.canViewAs<std::string_view>());
        auto view0 = robj.view<std::string_view>();
        ASSERT_FALSE(view0.has_value());

        ASSERT_FALSE(robj.canViewAs<std::nullptr_t>());
        auto view1 = robj.view<std::nullptr_t>();
        ASSERT_FALSE(view1.has_value());
    }
}


namespace unit_test
{
    TEST(RObject_init_with_stdString_pointer, view_as_std_string)
    {
        // Create an RObject that reflects a std::string pointer.
        RObject robj = rtl::reflect(&STR_STD_STRING);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

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
        RObject robj = rtl::reflect(&STR_STD_STRING);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view = robj.view<char>();
        ASSERT_TRUE(view.has_value());
        
        // Ensure the returned pointer is the original std::string's buffer (no copy).
        const char& str_cref = view->get();
        ASSERT_EQ(&str_cref, STR_STD_STRING.c_str());
    }


    TEST(RObject_init_with_stdString_pointer, view_as_std_string_view)
    {
        // Create an RObject that reflects a std::string pointer.
        RObject robj = rtl::reflect(&STR_STD_STRING);

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

        // Try to obtain a view as 'std::string_view' and verify it is present.
        auto view = robj.view<std::string_view>();
        ASSERT_TRUE(view.has_value());

        // Validate the string_view content matches the original input.
        const std::string_view& str_cref = view->get();
        ASSERT_EQ(str_cref, STR_STD_STRING);
    }


    TEST(RObject_view_as_std_string_and_string_view, init_with_empty_literal)
    {
        // Create an RObject that reflects a empty string literal rvalue
        RObject robj = rtl::reflect("");

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

        // Try to obtain a view as 'std::string_view' and verify it is present.
        auto view0 = robj.view<std::string_view>();
        ASSERT_TRUE(view0.has_value());

        // Validate the 'string_view' content matches the original input.
        const std::string_view& str_view = view0->get();
        ASSERT_EQ(str_view, "");

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

        // Try to obtain a view as 'std::string' and verify it is present.
        auto view1 = robj.view<std::string>();
        ASSERT_TRUE(view1.has_value());

        // Validate the string content matches the original input.
        const std::string& str_cref = view1->get();
        ASSERT_EQ(str_cref, "");
    }


    TEST(RObject_view_as_std_string_and_string_view, init_with_charArray)
    {
        // Create an RObject that reflects a string value (init with 'char[]').
        RObject robj = rtl::reflect(STR_CHAR_ARRAY);

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

        // Try to obtain a view as 'std::string_view' and verify it is present.
        auto view0 = robj.view<std::string_view>();
        ASSERT_TRUE(view0.has_value());

        // Validate the string content matches the original input.
        const std::string_view& str_view = view0->get();
        ASSERT_EQ(str_view, STR_CHAR_ARRAY);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

        // Try to obtain a view as 'std::string' and verify it is present.
        auto view1 = robj.view<std::string>();
        ASSERT_TRUE(view1.has_value());

        // Validate the string content matches the original input.
        const std::string& str_cref = view1->get();
        ASSERT_EQ(str_cref, STR_CHAR_ARRAY);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view2 = robj.view<char>();
        ASSERT_TRUE(view2.has_value());

        //since the char[] is wrapped in string_view, base address is stored, data not copied.
        const char& str_addr = view2->get();
        ASSERT_EQ(&str_addr, STR_CHAR_ARRAY);
    }


    TEST(RObject_init_with_charArray, view_as_const_char_ptr)
    {
        // Create an RObject that reflects a string value (init with 'char[]').
        RObject robj = rtl::reflect(STR_CHAR_ARRAY);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view = robj.view<char>();
        ASSERT_TRUE(view.has_value());

        const char& str_cref = view->get();
        // Ensure the returned pointer is the original array (no copy).
        ASSERT_EQ(&str_cref, STR_CHAR_ARRAY);
        // Validate the string content.
        ASSERT_EQ(std::string_view(&str_cref), std::string_view(STR_CHAR_ARRAY));
    }


    TEST(RObject_view_as_std_string_and_string_view, init_with_constCharArray)
    {
        // Create an RObject that reflects a string value (init with 'const char[]').
        RObject robj = rtl::reflect(STR_CONST_CHAR_ARRAY);

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

        // Try to obtain a view as 'std::string_view' and verify it is present.
        auto view0 = robj.view<std::string_view>();
        ASSERT_TRUE(view0.has_value());

        // Validate the string content matches the original input.
        const std::string_view& str_view = view0->get();
        ASSERT_EQ(str_view, STR_CONST_CHAR_ARRAY);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

        // Try to obtain a view as 'std::string' and verify it is present.
        auto view1 = robj.view<std::string>();
        ASSERT_TRUE(view1.has_value());

        //since the char[] is wrapped in string_view, but will return std::string copy.
        const std::string& str_cref = view1->get();
        ASSERT_EQ(str_cref, STR_CONST_CHAR_ARRAY);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view2 = robj.view<char>();
        ASSERT_TRUE(view2.has_value());

        //since the char[] is wrapped in string_view, base address is stored, data not copied.
        const char& str_addr = view2->get();
        ASSERT_EQ(&str_addr, STR_CONST_CHAR_ARRAY);
    }


    TEST(RObject_view_as_const_char_ptr, init_with_constCharArray)
    {
        // Create an RObject that reflects a string value (init with 'const char[]').
        RObject robj = rtl::reflect(STR_CONST_CHAR_ARRAY);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view = robj.view<char>();
        ASSERT_TRUE(view.has_value());

        const char& str_cref = view->get();

        //the addresses are same
        ASSERT_EQ(&str_cref, STR_CONST_CHAR_ARRAY);

        // Validate the C-string content matches the original input.
        ASSERT_EQ(std::string_view(&str_cref), STR_CONST_CHAR_ARRAY);
    }


    TEST(RObject_view_as_std_string_and_string_view, init_with_constCharPtr)
    {
        // Create an RObject that reflects a string value (init with 'const char*').
        RObject robj = rtl::reflect(STR_CONST_CHAR_POINTER);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_FALSE(robj.canViewAs<std::string>());

        // Check if the value can be accessed as 'std::string'.
        ASSERT_FALSE(robj.canViewAs<std::string_view>());

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'std::string' and verify it is present.
        auto view = robj.view<char>();
        ASSERT_TRUE(view.has_value());

        // Validate the string content matches the original input.
        const char& str_addr = view->get();
        ASSERT_EQ(&str_addr, STR_CONST_CHAR_POINTER);
    }


    TEST(RObject_init_with_stdString, view_as_std_string)
    {
        // Create an RObject that reflects a string value (init with 'std::string').
        RObject robj = rtl::reflect(STR_STD_STRING);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

        // Try to obtain a view as 'std::string' and verify it is present.
        auto view0 = robj.view<std::string>();
        ASSERT_TRUE(view0.has_value());

        // Validate the string content matches the original input.
        const std::string& str_cref = view0->get();
        ASSERT_EQ(str_cref, STR_STD_STRING);

        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view1 = robj.view<char>();
        ASSERT_TRUE(view1.has_value());

        // Validate the base address are different, since RObject is reflecting a copy.
        const char& str_addr = view1->get();
        ASSERT_NE(&str_addr, STR_STD_STRING.c_str());
    }


    TEST(RObject_init_with_stdString_rvalue, view_as_std_string)
    {
        // Create an RObject that reflects a string value (init with 'std::string' rvalue).
        RObject robj = rtl::reflect(std::string(STR_STD_STRING));

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

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
        RObject robj = rtl::reflect(STR_STD_STRING);

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

        // Try to obtain a view as 'std::string_view' and verify it is present.
        auto view = robj.view<std::string_view>();
        ASSERT_TRUE(view.has_value());

        // Validate the string_view content matches the original input.
        const std::string_view& str_cref = view->get();
        ASSERT_EQ(str_cref, STR_STD_STRING);
    }


    TEST(RObject_init_with_stdStringView, view_as_std_string)
    {
        // Create an RObject that reflects a string value (init with 'std::string_view').
        // Stores a copy of the 'std::string_view' as a 'std::string'.
        RObject robj = rtl::reflect(STR_STD_STRING_VIEW);

        // Check if the value can be accessed as 'std::string'.
        ASSERT_TRUE(robj.canViewAs<std::string>());

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
        RObject robj = rtl::reflect(STR_STD_STRING_VIEW);

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

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
        RObject robj = rtl::reflect(std::string_view(STR_CONST_CHAR_POINTER));

        // Check if the value can be accessed as 'std::string_view'.
        ASSERT_TRUE(robj.canViewAs<std::string_view>());

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
        RObject robj = rtl::reflect(STR_STD_STRING_VIEW);

        // Check if the value can be accessed as 'const char*'.
        ASSERT_TRUE(robj.canViewAs<char>());

        // Try to obtain a view as 'const char*' and verify it is present.
        auto view = robj.view<char>();
        ASSERT_TRUE(view.has_value());

        // Validate the C-string content matches the original input.
        const char& str_cref = view->get();
        ASSERT_EQ(std::string_view(&str_cref), STR_STD_STRING_VIEW);
    }
}


#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl;


namespace rtl_tests
{
    // Test reflecting a char and viewing it as signed char
    TEST(RObject_char_value, reflect_char_view_as_signed_char)
    {
        // Reflect the value 'A' (ASCII 65) into RObject
        RObject robj = rtl::reflect('A');

        // Check if RObject can reflect as `signed char`
        ASSERT_TRUE(robj.canViewAs<signed char>());

        // Get a view of the value as `signed char`
        auto view = robj.view<signed char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted signed char value
        const signed char& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<signed char>('A'));
    }


    // Test reflecting a char and viewing it as unsigned char
    TEST(RObject_char_value, reflect_char_view_as_unsigned_char)
    {
        // Reflect the value 'A' (ASCII 65) into RObject
        RObject robj = rtl::reflect('A');

        // Check if RObject can reflect as `unsigned char`
        ASSERT_TRUE(robj.canViewAs<unsigned char>());

        // Get a view of the value as `unsigned char`
        auto view = robj.view<unsigned char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned char value
        const unsigned char& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<unsigned char>('A'));
    }


    // Test reflecting a char and viewing it as short
    TEST(RObject_char_value, reflect_char_view_as_short)
    {
        // Reflect the value 'A' (ASCII 65) into RObject
        RObject robj = rtl::reflect('A');

        // Check if RObject can reflect as `short`
        ASSERT_TRUE(robj.canViewAs<short>());

        // Get a view of the value as `short`
        auto view = robj.view<short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted short value
        const short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<short>('A'));
    }


    // Test reflecting a char and viewing it as unsigned short
    TEST(RObject_char_value, reflect_char_view_as_unsigned_short)
    {
        // Reflect the value 'A' (ASCII 65) into RObject
        RObject robj = rtl::reflect('A');

        // Check if RObject can reflect as `unsigned short`
        ASSERT_TRUE(robj.canViewAs<unsigned short>());

        // Get a view of the value as `unsigned short`
        auto view = robj.view<unsigned short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned short value
        const unsigned short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<unsigned short>('A'));
    }


    // Test reflecting a char and viewing it as int
    TEST(RObject_char_value, reflect_char_view_as_int)
    {
        // Reflect the value 'A' (ASCII 65) into RObject
        RObject robj = rtl::reflect('A');

        // Check if RObject can reflect as `int`
        ASSERT_TRUE(robj.canViewAs<int>());

        // Get a view of the value as `int`
        auto view = robj.view<int>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted int value
        const int& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<int>('A'));
    }
}
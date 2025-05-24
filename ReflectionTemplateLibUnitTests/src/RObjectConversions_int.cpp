
#include <gtest/gtest.h>

#include "ReflectionSystem.h"

using namespace rtl::access;

namespace {
    static bool _ = rtl::unit_test::ReflectionSystem::init();
}

namespace rtl
{
    namespace unit_test
    {
        // Test reflecting an int and viewing it as bool
        TEST(RObject_int, reflect_int_view_as_bool)
        {
            // Reflect an int value (e.g., 5) into RObject
            RObject robj = RObject::reflect(5);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `bool`
            ASSERT_TRUE(robj.canReflectAs<bool>());

            // Get a view of the value as `bool`
            auto view = robj.view<bool>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted bool value
            const bool& cref = view->get();

            // Verify the conversion result (non-zero → true)
            ASSERT_EQ(cref, true);
        }


        // Test reflecting an int and viewing it as char
        TEST(RObject_int, reflect_int_view_as_char)
        {
            // Reflect an int value (e.g., 65) into RObject
            RObject robj = RObject::reflect(65);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `char`
            ASSERT_TRUE(robj.canReflectAs<char>());

            // Get a view of the value as `char`
            auto view = robj.view<char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted char value
            const char& cref = view->get();

            // Verify the conversion result (65 → 'A')
            ASSERT_EQ(cref, static_cast<char>(65));
        }


        // Test reflecting an int and viewing it as signed char
        TEST(RObject_int, reflect_int_view_as_signed_char)
        {
            // Reflect an int value (e.g., 97) into RObject
            RObject robj = RObject::reflect(97);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `signed char`
            ASSERT_TRUE(robj.canReflectAs<signed char>());

            // Get a view of the value as `signed char`
            auto view = robj.view<signed char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted signed char value
            const signed char& cref = view->get();

            // Verify the conversion result (97 → 'a')
            ASSERT_EQ(cref, static_cast<signed char>(97));
        }


        // Test reflecting an int and viewing it as unsigned char
        TEST(RObject_int, reflect_int_view_as_unsigned_char)
        {
            // Reflect an int value (e.g., 255) into RObject
            RObject robj = RObject::reflect(255);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `unsigned char`
            ASSERT_TRUE(robj.canReflectAs<unsigned char>());

            // Get a view of the value as `unsigned char`
            auto view = robj.view<unsigned char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned char value
            const unsigned char& cref = view->get();

            // Verify the conversion result (255 → '\xff')
            ASSERT_EQ(cref, static_cast<unsigned char>(255));
        }


        // Test reflecting an int and viewing it as short
        TEST(RObject_int, reflect_int_view_as_short)
        {
            // Reflect an int value (e.g., 32767) into RObject
            RObject robj = RObject::reflect(32767);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `short`
            ASSERT_TRUE(robj.canReflectAs<short>());

            // Get a view of the value as `short`
            auto view = robj.view<short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted short value
            const short& cref = view->get();

            // Verify the conversion result
            ASSERT_EQ(cref, static_cast<short>(32767));
        }


        // Test reflecting an int and viewing it as unsigned short
        TEST(RObject_int, reflect_int_view_as_unsigned_short)
        {
            // Reflect an int value (e.g., 65535) into RObject
            RObject robj = RObject::reflect(65535);

            // Verify the true type stored is `int`
            ASSERT_TRUE(robj.isTrueType<int>());

            // Check if RObject can reflect as `unsigned short`
            ASSERT_TRUE(robj.canReflectAs<unsigned short>());

            // Get a view of the value as `unsigned short`
            auto view = robj.view<unsigned short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned short value
            const unsigned short& cref = view->get();

            // Verify the conversion result
            ASSERT_EQ(cref, static_cast<unsigned short>(65535));
        }
    }
}
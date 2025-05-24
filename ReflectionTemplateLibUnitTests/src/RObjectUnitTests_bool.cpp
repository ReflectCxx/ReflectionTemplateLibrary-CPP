
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests_strings.h"

using namespace rtl::access;

static CxxMirror reflectionSystem({});

namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_podTest, reflect_bool_view_as_bool)
        {
            // Reflect a bool value into RObject
            RObject robj = RObject::reflect(true);

            // Check if the original stored type is bool
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if RObject can be viewed as bool (true type or convertible)
            ASSERT_TRUE(robj.canReflectAs<bool>());

            // Get a view of the value as bool
            auto view = robj.view<bool>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the underlying value
            const bool& cref = view->get();

            // Confirm the value is equal to the original
            ASSERT_EQ(cref, true);
        }


        TEST(RObject_podTest, reflect_bool_view_as_int)
        {
            // Reflect a bool value (false) into RObject
            RObject robj = RObject::reflect(false);

            // Confirm the true type held is bool
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if RObject can be viewed as int (via conversion)
            ASSERT_TRUE(robj.canReflectAs<int>());

            // Get a view of the value as int
            auto view = robj.view<int>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted int value
            const int& cref = view->get();

            // Confirm the value matches expected result of bool(false) → int(0)
            ASSERT_EQ(cref, 0);
        }


        // Test reflecting a bool and viewing it as char
        TEST(RObject_podTest, reflect_bool_view_as_char)
        {
            // Reflect the value `true` into RObject
            RObject robj = RObject::reflect(true);

            // Ensure the stored type is actually `bool`
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if the RObject can reflect as `char`
            ASSERT_TRUE(robj.canReflectAs<char>());

            // Get the reflected value as `char`
            auto view = robj.view<char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted char value
            const char& cref = view->get();

            // Verify the reflected `char` value is correct
            ASSERT_EQ(cref, static_cast<char>(true));
        }


        // Test reflecting a bool and viewing it as signed char
        TEST(RObject_podTest, reflect_bool_view_as_signed_char)
        {
            // Reflect the value `false` into RObject
            RObject robj = RObject::reflect(false);

            // Check if the original type is `bool`
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if the value can be reflected as `signed char`
            ASSERT_TRUE(robj.canReflectAs<signed char>());

            // Get the reflected value as `signed char`
            auto view = robj.view<signed char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted signed char value
            const signed char& cref = view->get();

            // Verify the converted value matches the original bool value
            ASSERT_EQ(cref, static_cast<signed char>(false));
        }


        // Test reflecting a bool and viewing it as unsigned char
        TEST(RObject_podTest, reflect_bool_view_as_unsigned_char)
        {
            // Reflect the value `true` into RObject
            RObject robj = RObject::reflect(true);

            // Confirm the stored type is `bool`
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if RObject can reflect as `unsigned char`
            ASSERT_TRUE(robj.canReflectAs<unsigned char>());

            // Get the reflected value as `unsigned char`
            auto view = robj.view<unsigned char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned char value
            const unsigned char& cref = view->get();

            // Confirm the converted value matches the original bool value
            ASSERT_EQ(cref, static_cast<unsigned char>(true));
        }


        // Test reflecting a bool and viewing it as short
        TEST(RObject_podTest, reflect_bool_view_as_short)
        {
            // Reflect the value `false` into RObject
            RObject robj = RObject::reflect(false);

            // Verify the stored true type is `bool`
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if the value can be reflected as `short`
            ASSERT_TRUE(robj.canReflectAs<short>());

            // Get the reflected value as `short`
            auto view = robj.view<short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted short value
            const short& cref = view->get();

            // Confirm the converted value matches original bool value
            ASSERT_EQ(cref, static_cast<short>(false));
        }


        // Test reflecting a bool and viewing it as unsigned short
        TEST(RObject_podTest, reflect_bool_view_as_unsigned_short)
        {
            // Reflect the value `true` into RObject
            RObject robj = RObject::reflect(true);

            // Confirm the stored true type is `bool`
            ASSERT_TRUE(robj.isTrueType<bool>());

            // Check if the value can be reflected as `unsigned short`
            ASSERT_TRUE(robj.canReflectAs<unsigned short>());

            // Get the reflected value as `unsigned short`
            auto view = robj.view<unsigned short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned short value
            const unsigned short& cref = view->get();

            // Confirm the converted value matches original bool value
            ASSERT_EQ(cref, static_cast<unsigned short>(true));
        }
    }
}
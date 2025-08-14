
#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl::access;

namespace rtl_tests
{
    // Test reflecting an int and viewing it as bool
    TEST(RObject_int_rvalue, reflect_int_view_as_bool)
    {
        // Reflect an int value (e.g., 5) into RObject
        RObject robj = rtl::reflect(5);

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());

        // Get a view of the value as `bool`
        auto view = robj.view<bool>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted bool value
        const bool& cref = view->get();

        // Verify the conversion result (non-zero -> true)
        ASSERT_EQ(cref, true);
    }


    // Test reflecting an int and viewing it as char
    TEST(RObject_int_rvalue, reflect_int_view_as_char)
    {
        // Reflect an int value (e.g., 65) into RObject
        RObject robj = rtl::reflect(65);

        // Check if RObject can reflect as `char`
        ASSERT_TRUE(robj.canViewAs<char>());

        // Get a view of the value as `char`
        auto view = robj.view<char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted char value
        const char& cref = view->get();

        // Verify the conversion result (65 -> 'A')
        ASSERT_EQ(cref, static_cast<char>(65));
    }


    // Test reflecting an int and viewing it as signed char
    TEST(RObject_int_rvalue, reflect_int_view_as_signed_char)
    {
        // Reflect an int value (e.g., 97) into RObject
        RObject robj = rtl::reflect(97);

        // Check if RObject can reflect as `signed char`
        ASSERT_TRUE(robj.canViewAs<signed char>());

        // Get a view of the value as `signed char`
        auto view = robj.view<signed char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted signed char value
        const signed char& cref = view->get();

        // Verify the conversion result (97 -> 'a')
        ASSERT_EQ(cref, static_cast<signed char>(97));
    }


    // Test reflecting an int and viewing it as unsigned char
    TEST(RObject_int_rvalue, reflect_int_view_as_unsigned_char)
    {
        // Reflect an int value (e.g., 255) into RObject
        RObject robj = rtl::reflect(255);

        // Check if RObject can reflect as `unsigned char`
        ASSERT_TRUE(robj.canViewAs<unsigned char>());

        // Get a view of the value as `unsigned char`
        auto view = robj.view<unsigned char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned char value
        const unsigned char& cref = view->get();

        // Verify the conversion result (255 -> '\xff')
        ASSERT_EQ(cref, static_cast<unsigned char>(255));
    }


    // Test reflecting an int and viewing it as short
    TEST(RObject_int_rvalue, reflect_int_view_as_short)
    {
        // Reflect an int value (e.g., 32767) into RObject
        RObject robj = rtl::reflect(32767);

        // Check if RObject can reflect as `short`
        ASSERT_TRUE(robj.canViewAs<short>());

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
    TEST(RObject_int_rvalue, reflect_int_view_as_unsigned_short)
    {
        // Reflect an int value (e.g., 65535) into RObject
        RObject robj = rtl::reflect(65535);

        // Check if RObject can reflect as `unsigned short`
        ASSERT_TRUE(robj.canViewAs<unsigned short>());

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


namespace rtl_tests
{
    // Test reflecting an int and viewing it as bool
    TEST(RObject_int_lvalue, reflect_int_ptr_view_as_int_ptr)
    {
        int value = 5; // Example int value

        // Reflect an int value pointer into RObject
        RObject robj = rtl::reflect(&value);

        // Check if RObject can reflect as `const int *`
        ASSERT_TRUE(robj.canViewAs<int>());

        // Get a view of the value as `const int *`
        auto view = robj.view<int>();

        // Ensure the view is valid
        ASSERT_TRUE(view.has_value());

		// Access the pointer returned by the view
        const int& cref = view->get();

        // Verify the addresses are same, no copy made.
        ASSERT_EQ(&cref, &value);
    }


    // Test reflecting an int and viewing it as bool
    TEST(RObject_int_lvalue, reflect_int_ptr_view_as_int_value)
    {
        int value = 5; // Example int value

        // Reflect an int value pointer into RObject
        RObject robj = rtl::reflect(&value);

        // Check if RObject can reflect as `int`
        ASSERT_TRUE(robj.canViewAs<int>());

        // Get a view of the value as `int`
        auto view = robj.view<int>();

        // Ensure the view is valid
        ASSERT_TRUE(view.has_value());

        // Access the pointer returned by the view
        int cref = view->get();

        // Verify the addresses are same, no copy made.
        ASSERT_EQ(cref, value);
    }


    // Test reflecting an int and viewing it as bool
    TEST(RObject_int_lvalue, reflect_int_view_as_bool)
    {
		int value = 5; // Example int value

        // Reflect an int value (e.g., 5) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());

        // Get a view of the value as `bool`
        auto view = robj.view<bool>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted bool value
        const bool& cref = view->get();

        // Verify the conversion result (non-zero -> true)
        ASSERT_EQ(cref, true);
    }


    // Test reflecting an int and viewing it as char
    TEST(RObject_int_lvalue, reflect_int_view_as_char)
    {
		int value = 65; // Example int value

        // Reflect an int value (e.g., 65) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `char`
        ASSERT_TRUE(robj.canViewAs<char>());

        // Get a view of the value as `char`
        auto view = robj.view<char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted char value
        const char& cref = view->get();

        // Verify the conversion result (65 -> 'A')
        ASSERT_EQ(cref, static_cast<char>(value));
    }


    // Test reflecting an int and viewing it as signed char
    TEST(RObject_int_lvalue, reflect_int_view_as_signed_char)
    {
		int value = 97; // Example int value

        // Reflect an int value (e.g., 97) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `signed char`
        ASSERT_TRUE(robj.canViewAs<signed char>());

        // Get a view of the value as `signed char`
        auto view = robj.view<signed char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted signed char value
        const signed char& cref = view->get();

        // Verify the conversion result (97 -> 'a')
        ASSERT_EQ(cref, static_cast<signed char>(value));
    }


    // Test reflecting an int and viewing it as unsigned char
    TEST(RObject_int_lvalue, reflect_int_view_as_unsigned_char)
    {
		int value = 255; // Example int value

        // Reflect an int value (e.g., 255) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `unsigned char`
        ASSERT_TRUE(robj.canViewAs<unsigned char>());

        // Get a view of the value as `unsigned char`
        auto view = robj.view<unsigned char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned char value
        const unsigned char& cref = view->get();

        // Verify the conversion result (255 -> '\xff')
        ASSERT_EQ(cref, static_cast<unsigned char>(value));
    }


    // Test reflecting an int and viewing it as short
    TEST(RObject_int_lvalue, reflect_int_view_as_short)
    {
		int value = 32767; // Example int value

        // Reflect an int value (e.g., 32767) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `short`
        ASSERT_TRUE(robj.canViewAs<short>());

        // Get a view of the value as `short`
        auto view = robj.view<short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted short value
        const short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<short>(value));
    }


    // Test reflecting an int and viewing it as unsigned short
    TEST(RObject_int_lvalue, reflect_int_view_as_unsigned_short)
    {
		int value = 65535; // Example int value

        // Reflect an int value (e.g., 65535) into RObject
        RObject robj = rtl::reflect(value);

        // Check if RObject can reflect as `unsigned short`
        ASSERT_TRUE(robj.canViewAs<unsigned short>());

        // Get a view of the value as `unsigned short`
        auto view = robj.view<unsigned short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned short value
        const unsigned short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<unsigned short>(value));
    }
}




namespace rtl_tests
{
    // Test reflecting an int* and viewing it as bool
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_bool_true)
    {
        int *ptr = new int(5);

        // Reflect an int value (e.g., 5) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());

        // Get a view of the value as `bool`
        auto view = robj.view<bool>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted bool value
        const bool& cref = view->get();

        // Verify the conversion result (non-zero -> true)
        ASSERT_EQ(cref, true);

		delete ptr; // Clean up the dynamically allocated memory
    }


    // Test reflecting an int* and viewing it as bool
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_bool_false)
    {
		int* ptr = new int(0);

        // Reflect an int value (e.g., 5) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());

        // Get a view of the value as `bool`
        auto view = robj.view<bool>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted bool value
        const bool& cref = view->get();

        // Verify the conversion result (non-zero -> true)
        ASSERT_EQ(cref, false);
    }


    // Test reflecting an int* and viewing it as char
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_char)
    {
		int* ptr = new int(65);

        // Reflect an int value (e.g., 65) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `char`
        ASSERT_TRUE(robj.canViewAs<char>());

        // Get a view of the value as `char`
        auto view = robj.view<char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted char value
        const char& cref = view->get();

        // Verify the conversion result (65 -> 'A')
        ASSERT_EQ(cref, static_cast<char>(65));

		delete ptr; // Clean up the dynamically allocated memory
    }


    // Test reflecting an int* and viewing it as signed char
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_signed_char)
    {
		int* ptr = new int(97);

        // Reflect an int value (e.g., 97) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `signed char`
        ASSERT_TRUE(robj.canViewAs<signed char>());

        // Get a view of the value as `signed char`
        auto view = robj.view<signed char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted signed char value
        const signed char& cref = view->get();

        // Verify the conversion result (97 -> 'a')
        ASSERT_EQ(cref, static_cast<signed char>(97));

        delete ptr; // Clean up the dynamically allocated memory
    }


    // Test reflecting an int and viewing it as unsigned char
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_unsigned_char)
    {
		int* ptr = new int(255);

        // Reflect an int value (e.g., 255) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `unsigned char`
        ASSERT_TRUE(robj.canViewAs<unsigned char>());

        // Get a view of the value as `unsigned char`
        auto view = robj.view<unsigned char>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned char value
        const unsigned char& cref = view->get();

        // Verify the conversion result (255 -> '\xff')
        ASSERT_EQ(cref, static_cast<unsigned char>(255));

        delete ptr; // Clean up the dynamically allocated memory
    }


    // Test reflecting an int and viewing it as short
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_short)
    {
		int* ptr = new int(32767);

        // Reflect an int value (e.g., 32767) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `short`
        ASSERT_TRUE(robj.canViewAs<short>());

        // Get a view of the value as `short`
        auto view = robj.view<short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted short value
        const short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<short>(32767));

        delete ptr; // Clean up the dynamically allocated memory
    }


    // Test reflecting an int and viewing it as unsigned short
    TEST(RObject_int_pointer_lvalue, reflect_int_view_as_unsigned_short)
    {
		int* ptr = new int(65535);

        // Reflect an int value (e.g., 65535) into RObject
        RObject robj = rtl::reflect(ptr);

        // Check if RObject can reflect as `unsigned short`
        ASSERT_TRUE(robj.canViewAs<unsigned short>());

        // Get a view of the value as `unsigned short`
        auto view = robj.view<unsigned short>();

        // Ensure the view is valid (conversion succeeded)
        ASSERT_TRUE(view.has_value());

        // Access the converted unsigned short value
        const unsigned short& cref = view->get();

        // Verify the conversion result
        ASSERT_EQ(cref, static_cast<unsigned short>(65535));

        delete ptr; // Clean up the dynamically allocated memory
    }
}


namespace rtl_tests
{
    // Test reflecting an int* and viewing it as bool
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_bool_true)
    {
    /*  Reflect an int value(e.g., 5) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(5));

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());
        {
            // Get a view of the value as `bool`
            auto view = robj.view<bool>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted bool value
            const bool& cref = view->get();

            // Verify the conversion result (non-zero -> true)
            ASSERT_EQ(cref, true);
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }


    // Test reflecting an int* and viewing it as bool
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_bool_false)
    {
    /*  Reflect an int value (e.g., 0) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(0));

        // Check if RObject can reflect as `bool`
        ASSERT_TRUE(robj.canViewAs<bool>());
        {
            // Get a view of the value as `bool`
            auto view = robj.view<bool>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted bool value
            const bool& cref = view->get();

            // Verify the conversion result (non-zero -> true)
            ASSERT_EQ(cref, false);
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }

        //Caution: The dynamically allocated memory (new int) is not deleted here.
    }


    // Test reflecting an int* and viewing it as char
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_char)
    {
    /*  Reflect an int value(e.g., 65) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(65));

        // Check if RObject can reflect as `char`
        ASSERT_TRUE(robj.canViewAs<char>());
        {
            // Get a view of the value as `char`
            auto view = robj.view<char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted char value
            const char& cref = view->get();

            // Verify the conversion result (65 -> 'A')
            ASSERT_EQ(cref, static_cast<char>(65));
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }


    // Test reflecting an int* and viewing it as signed char
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_signed_char)
    {
    /*  Reflect an int value(e.g., 97) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(97));

        // Check if RObject can reflect as `signed char`
        ASSERT_TRUE(robj.canViewAs<signed char>());
        {
            // Get a view of the value as `signed char`
            auto view = robj.view<signed char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted signed char value
            const signed char& cref = view->get();

            // Verify the conversion result (97 -> 'a')
            ASSERT_EQ(cref, static_cast<signed char>(97));
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }


    // Test reflecting an int and viewing it as unsigned char
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_unsigned_char)
    {
    /*  Reflect an int value(e.g., 255) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(255));

        // Check if RObject can reflect as `unsigned char`
        ASSERT_TRUE(robj.canViewAs<unsigned char>());
        {
            // Get a view of the value as `unsigned char`
            auto view = robj.view<unsigned char>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned char value
            const unsigned char& cref = view->get();

            // Verify the conversion result (255 -> '\xff')
            ASSERT_EQ(cref, static_cast<unsigned char>(255));
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }


    // Test reflecting an int and viewing it as short
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_short)
    {
    /*  Reflect an int value(e.g., 32767) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(32767));

        // Check if RObject can reflect as `short`
        ASSERT_TRUE(robj.canViewAs<short>());
        {
            // Get a view of the value as `short`
            auto view = robj.view<short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted short value
            const short& cref = view->get();

            // Verify the conversion result
            ASSERT_EQ(cref, static_cast<short>(32767));
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }


    // Test reflecting an int and viewing it as unsigned short
    TEST(RObject_int_pointer_rvalue, reflect_int_view_as_unsigned_short)
    {
    /*  Reflect an int value(e.g., 65535) into RObject
    *   Intentionally relinquishing ownership of dynamically allocated memory
    *   to test RObject creation with an rvalue pointer.
    */  RObject robj = rtl::reflect(new int(65535));

        // Check if RObject can reflect as `unsigned short`
        ASSERT_TRUE(robj.canViewAs<unsigned short>());
        {
            // Get a view of the value as `unsigned short`
            auto view = robj.view<unsigned short>();

            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());

            // Access the converted unsigned short value
            const unsigned short& cref = view->get();

            // Verify the conversion result
            ASSERT_EQ(cref, static_cast<unsigned short>(65535));
        } {
            ASSERT_TRUE(robj.canViewAs<int>());

            auto view = robj.view<int>();

            ASSERT_TRUE(view.has_value());

            // rtl::view<> holds ref to the entity in RObject;
            // delete the dynamically allocated memory (new int)
            const int& cref = view->get();
            delete& cref;
        }
    }
}

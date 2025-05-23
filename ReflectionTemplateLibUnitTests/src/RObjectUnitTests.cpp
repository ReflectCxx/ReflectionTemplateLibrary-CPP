
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests.h"

using namespace rtl::access;

namespace rtl
{
    namespace unit_test
    {
        TEST(RObjectStringTests, init_with_constCharPtr_view_as_stdString)
        {
            //Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_POINTER);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string'.
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string'.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            const std::string& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CONST_CHAR_POINTER);
        }


        TEST(RObjectStringTests, init_with_constCharPtr_view_as_stdStringView)
        {
            //Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_POINTER);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string_view'.
            ASSERT_TRUE(robj.isReflecting<std::string_view>());

            //get the view as type 'std::string_view'.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            const std::string_view& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CONST_CHAR_POINTER);
        }


        TEST(RObjectStringTests, init_with_constCharPtr_view_as_constCharPtr)
        {
            //Create an RObject that reflects a string value (init with 'const char*').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_POINTER);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'const char*'.
            ASSERT_TRUE(robj.isReflecting<const char*>());

            //get the view as type 'const char*'.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            const char* str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(std::string(str_cref), STRING_CONST_CHAR_POINTER);
        }


        TEST(RObjectStringTests, init_with_constCharArray_view_as_stdString)
        {
            //Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_ARRAY);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string'.
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string'.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            const std::string& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CONST_CHAR_ARRAY);
        }


        TEST(RObjectStringTests, init_with_constCharArray_view_as_stdStringView)
        {
            //Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_ARRAY);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string_view'.
            ASSERT_TRUE(robj.isReflecting<std::string_view>());

            //get the view as type 'std::string_view'.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            const std::string_view& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CONST_CHAR_ARRAY);
        }


        TEST(RObjectStringTests, init_with_constCharArray_view_as_constCharPtr)
        {
            //Create an RObject that reflects a string value (init with 'const char[]').
            RObject robj = RObject::reflect(STRING_CONST_CHAR_ARRAY);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'const char*'.
            ASSERT_TRUE(robj.isReflecting<const char*>());

            //get the view as type 'const char*'.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            const char* str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(std::string(str_cref), STRING_CONST_CHAR_ARRAY);
        }


        TEST(RObjectStringTests, init_with_stdString_view_as_stdString)
        {
            //Create an RObject that reflects a string value (init with std::string).
            RObject robj = RObject::reflect(STRING_STD_STRING);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string'.
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string'.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            const std::string& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_STD_STRING);
        }


        TEST(RObjectStringTests, init_with_stdString_view_as_stdStringView)
        {
            //Create an RObject that reflects a string value (init with std::string).
            RObject robj = RObject::reflect(STRING_STD_STRING);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string_view'.
            ASSERT_TRUE(robj.isReflecting<std::string_view>());

            //get the view as type 'std::string_view'.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            const std::string_view& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_STD_STRING);
        }


        TEST(RObjectStringTests, init_with_stdString_view_as_constCharPtr)
        {
            //Create an RObject that reflects a string value (init with std::string).
            RObject robj = RObject::reflect(STRING_STD_STRING);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'const char*'.
            ASSERT_TRUE(robj.isReflecting<const char*>());

            //get the view as type 'const char*'.
            auto view = robj.view<const char*>();
            ASSERT_TRUE(view.has_value());

            const char* str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(std::string(str_cref), STRING_STD_STRING);
        }

    /*  this won't compile since 'char[]' is not const. treated as unvalid string.
        TEST(RObjectStringTests, init_with_charArray_view_as_stdString)
        {
            //Create an RObject that reflects a string value (init with  char[]).
            RObject robj = RObject::reflect(STRING_CHAR_ARRAY);
        }
    */
    }
}

#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests.h"

using namespace rtl::access;

namespace rtl
{
    namespace unit_test
    {
        TEST(RObjectStringTests, init_with_ConstCharPtr_view_as_StdString)
        {
            //Create an RObject that reflects a string value (init with const char*).
            RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string'.
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string'.
            auto view = robj.view<std::string>();
            ASSERT_TRUE(view.has_value());

            const std::string& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CHAR_POINTER);
        }


        TEST(RObjectStringTests, init_with_ConstCharPtr_view_as_StdStringView)
        {
            //Create an RObject that reflects a string value (init with const char*).
            RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

            //check if the RObject is reflecting anything?
            ASSERT_TRUE(robj.isReflecting());

            //check if the RObject is reflecting value type 'std::string_view'.
            ASSERT_TRUE(robj.isReflecting<std::string_view>());

            //get the view as type 'std::string_view'.
            auto view = robj.view<std::string_view>();
            ASSERT_TRUE(view.has_value());

            const std::string_view& str_cref = view->get();
            //Check if the value contained is same as given initially.
            ASSERT_EQ(str_cref, STRING_CHAR_POINTER);
        }
    }
}
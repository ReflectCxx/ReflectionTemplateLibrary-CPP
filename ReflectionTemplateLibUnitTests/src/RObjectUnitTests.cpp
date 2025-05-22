
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests.h"

using namespace rtl::access;

namespace rtl
{
    namespace unit_test
    {
        //TEST(RObjectStringTests, init_with_ConstCharPtr_view_as_ConstCharPtr)
        //{
        //    //Create an RObject that reflects a string value (init with const char*).
        //    RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

        //    //check if the RObject reflects(or contains) value type 'const char *'.
        //    ASSERT_TRUE(robj.isReflecting<const char *>());            
        //    
        //    //get the view as type 'const char*'.
        //    const char* str = robj.view<const char*>();

        //    //robj.view<char>() returns nullptr, if underlying data is not convertible to 'const char*'.
        //    ASSERT_TRUE(str != nullptr);

        //    //Check if the value contained is same as given initially.
        //    ASSERT_EQ(std::string(str), STRING_CHAR_POINTER);
        //}


        //TEST(RObjectStringTests, init_with_ConstCharPtr_view_as_StdString)
        //{
        //    //Create an RObject that reflects a string value (init with const char*).
        //    RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

        //    //check if the RObject reflects(or contains) value type 'std::string'.
        //    //ASSERT_TRUE(robj.isReflecting<std::string>());

        //    //get the view as type 'std::string'.
        //    auto str = robj.view<std::string*>();

        //    //robj.view<std::string>() returns nullptr, if underlying data is not convertible to 'std::string'.
        //    ASSERT_TRUE(str != nullptr);

        //    //Check if the value contained is same as given initially.
        //    ASSERT_EQ(*str, STRING_CHAR_POINTER);
        //}


        //TEST(RObjectStringTests, init_with_ConstCharPtr_view_as_StdStringView)
        //{
        //    //Create an RObject that reflects a string value (init with const char*).
        //    RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

        //    //check if the RObject reflects(or contains) value type 'std::string'.
        //    ASSERT_TRUE(robj.isReflecting<std::string_view>());

        //    //get the view as type 'std::string'.
        //    auto str = robj.view<std::string_view>();

        //    //robj.view<std::string>() returns nullptr, if underlying data is not convertible to 'std::string_view'.
        //    ASSERT_TRUE(str != nullptr);

        //    //Check if the value contained is same as given initially.
        //    ASSERT_EQ(*str, STRING_CHAR_POINTER);
        //}
    }
}
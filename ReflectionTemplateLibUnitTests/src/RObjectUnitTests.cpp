
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests.h"

using namespace rtl::access;

//Initialize the reflection-system to initialize the RObject's converter-system.
static rtl::access::CxxMirror reflectionSystem({});

namespace rtl
{
    namespace unit_test
    {
        TEST(RObjectTest, reflect_a_string_and_view_as_const_char_pointer)
        {
            //Create an RObject that reflects a string value (accepts const char[], const char*, std::string, or std::string_view).
            RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

            //check if the RObject reflects(or contains) value type 'const char *'.
            ASSERT_TRUE(robj.isReflecting<const char *>());            
            
            //get the view as type 'const char*'.
            const char* str = robj.view<char>();

            //robj.view<char>() returns nullptr, if underlying data is convertible to 'const char*'.
            ASSERT_TRUE(str != nullptr);

            //Check if the value contained is same as given initially.
            ASSERT_EQ(std::string(str), STRING_CHAR_POINTER);
        }


        TEST(RObjectTest, reflect_a_string_and_view_as_std_string)
        {
            //Create an RObject that reflects a string value (accepts const char[], const char*, std::string, or std::string_view).
            RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

            //check if the RObject reflects(or contains) value type 'std::string'.
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string'.
            auto str = robj.view<std::string>();

            //robj.view<std::string>() returns nullptr, if underlying data is not convertible to 'std::string'.
            ASSERT_TRUE(str != nullptr);

            //Check if the value contained is same as given initially.
            ASSERT_EQ(*str, STRING_CHAR_POINTER);
        }
    }
}
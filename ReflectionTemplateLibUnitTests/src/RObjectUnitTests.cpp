
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RObjectUnitTests.h"

using namespace rtl::access;

//Initialize the reflection system to initialize the RObject's converters.
static rtl::access::CxxMirror reflectionSystem({});

namespace rtl
{
    namespace unit_test
    {
        TEST(RObjectTest, reflect_as_string_containing_c_style_char_litral)
        {
            //create an RObject reflecting value with type 'const char *'.
            RObject robj = RObject::reflect<alloc::Stack>(STRING_CHAR_POINTER);

            //check if the RObject reflects(contains) value with type 'const char *'.
            ASSERT_TRUE(robj.isReflecting<const char *>());            
            
            //get the view as type 'const char*', which is the original type of the value assigned.
            auto constCharPtrView = robj.view<const char*>();

            //returns std::optional, containing reference to contained value, may be empty if types not true or not convertible.
            ASSERT_TRUE(constCharPtrView.has_value());
            
            //Returns 'const char* const', assigned to std::string.
            std::string str0 = constCharPtrView->get();

            //Check if the value contained is same as given initially.
            ASSERT_EQ(str0, STRING_CHAR_POINTER);

            //check if the RObject reflects(contains) value with type 'std::string'
            ASSERT_TRUE(robj.isReflecting<std::string>());

            //get the view as type 'std::string', which is not the original but 'const char*' can be converted to 'std::string' implicitly.
            auto stdStringView = robj.view<std::string>();

            //returns std::optional, containing reference to contained value, may be empty if 'const char*' cannot be converted to 'std::string'.
            ASSERT_TRUE(stdStringView.has_value());
            
            //Returns 'const std::string', assigned to std::string.
            std::string str1 = stdStringView->get();

            //Check if the value contained is same as given initially.
            ASSERT_EQ(str1, STRING_CHAR_POINTER);
        }
    }
}
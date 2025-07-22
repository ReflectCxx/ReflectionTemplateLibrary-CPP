
#include <memory>
#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl::access;

namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_smart_ptr, reflect_unique_ptr)
        {
            std::unique_ptr<int> uptr = std::make_unique<int>(329);

            //RObject robj = reflect(uptr);

            // Check if RObject can reflect as `unique_ptr<int>`
            //ASSERT_TRUE(robj.canViewAs<std::unique_ptr<int>>());

            // Get a view of the value as `bool`
            //auto view = robj.view<std::unique_ptr<int>>();

            // Ensure the view is valid (conversion succeeded)
            //ASSERT_TRUE(view.has_value());

            // Access the converted bool value
            //const int cref = *view->get();

            // Verify the conversion result (non-zero -> true)
            //ASSERT_EQ(cref, 329);
        }
    }
}
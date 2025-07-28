
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
            std::shared_ptr<int> uptr = std::make_shared<int>(329);

            RObject robj = reflect(std::move(uptr));

            // Check if RObject can reflect as `int`
            EXPECT_TRUE(robj.canViewAs<int>());
            {
                auto view = robj.view<int>();
                ASSERT_TRUE(view);

                int value = view->get();
                EXPECT_EQ(value, 329);
            }
            // Check if RObject can reflect as `int`
            EXPECT_TRUE(robj.canViewAs<const int*>());
            {
                auto view = robj.view<const int*>();
                ASSERT_TRUE(view);

                int value = *view->get();
                EXPECT_EQ(value, 329);
            }
            // Check if RObject can reflect as `shared_ptr<int>`
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
            {
                // Get a view of the value as `bool`
                auto view = robj.view<std::shared_ptr<int>>();

                // Ensure the view is valid (conversion succeeded)
                ASSERT_TRUE(view.has_value());

                // Access the converted bool value
                const int cref = *view->get();

                // Verify the conversion result (non-zero -> true)
                EXPECT_EQ(cref, 329);
            }
            //These should not compile.
            //robj.canViewAs<const std::shared_ptr<int>*>();
            //robj.view<const std::shared_ptr<int>*>();
        }
    }
}
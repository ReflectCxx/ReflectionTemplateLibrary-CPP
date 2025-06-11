
#include <gtest/gtest.h>
#include <span>

#include "ReflectionSystem.h"

using namespace rtl::access;

namespace
{
    static bool _ = rtl::unit_test::ReflectionSystem::init();
}


namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_view_vector, init_with_stdVector_int)
        {
            std::vector<int> input = { 1, 2, 3, 4, 5 };

            RObject robj = RObject::reflect(input);

            ASSERT_TRUE(robj.canReflectAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());
            
			const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(vec_view->get(), input);
        }


        TEST(RObject_view_vector, init_with_stdVector_int_rvalue)
        {
            RObject robj = RObject::reflect(std::vector<int>({ 1, 2, 3, 4, 5 }));

            ASSERT_TRUE(robj.canReflectAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(vec_view->get(), std::vector<int>({ 1, 2, 3, 4, 5 }));
        }
    }
}
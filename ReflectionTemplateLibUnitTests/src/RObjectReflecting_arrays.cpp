
#include <gtest/gtest.h>
#include <span>

#include "ReflectionSystem.h"

using namespace rtl::access;

namespace
{
    static bool _= rtl::unit_test::ReflectionSystem::init();
}


namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_view_vector, init_with_stdVector_int_lvalue)
        {
            std::vector<int> input = { 1, 2, 3, 4, 5 };

            RObject robj = rtl::reflect(input);

            ASSERT_TRUE(robj.canReflectAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());
            
			const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(inputView, input);
        }


        TEST(RObject_view_vector, init_with_stdVector_int_lvalue_ptr)
        {
            std::vector<int> input = { 1, 2, 3, 4, 5 };

            RObject robj = rtl::reflect(&input);

            ASSERT_TRUE(robj.canReflectAs<const std::vector<int>*>());

            const auto& vec_view = robj.view<const std::vector<int>*>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>* inputView = vec_view->get();

			//no copy made since RObjct::reflect was initialized with a pointer
            ASSERT_EQ(inputView, &input);
        }


        TEST(RObject_view_vector, init_with_stdVector_int_rvalue)
        {
            RObject robj = rtl::reflect(std::vector<int>({ 1, 2, 3, 4, 5 }));

            ASSERT_TRUE(robj.canReflectAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(vec_view->get(), std::vector<int>({ 1, 2, 3, 4, 5 }));
        }


        TEST(RObject_array_reflection, reflect_int_array)
        {
            int data[3] = { 10, 20, 30 };

            RObject robj = rtl::reflect(data);

            using ExpectedArray = std::array<int, 3>;

            ASSERT_TRUE(robj.canReflectAs<ExpectedArray>());

            auto view = robj.view<ExpectedArray>();
            ASSERT_TRUE(view.has_value());

            const ExpectedArray& arr = view->get();
            EXPECT_EQ(arr[0], 10);
            EXPECT_EQ(arr[1], 20);
            EXPECT_EQ(arr[2], 30);
        }
    }
}
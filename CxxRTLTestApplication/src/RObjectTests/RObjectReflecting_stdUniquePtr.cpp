
#include <memory>
#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl::access;

namespace {

    static std::size_t g_nodeInstanceCount = 0;
    struct Node
    {
        std::size_t data;

        ~Node() {
            g_nodeInstanceCount--;
        }
        //Node(const Node& pOther) :data(pOther.data) { 
        //    g_nodeInstanceCount++; 
        //}
        Node(Node&& pOther) noexcept :data(pOther.data) {
            pOther.data = rtl::index_none;
            g_nodeInstanceCount++;
        }
        Node() :data(g_nodeInstanceCount++) {}

        Node(const Node& pOther) = delete;  //Ensure's no copy. only move.
        Node& operator=(Node&&) = delete;
        Node& operator=(const Node&) = delete;
    };
}


namespace rtl::unit_test
{
    TEST(RObject_std_wrapper_unique_ptr, reflect_init_with_lvalue)
    {
        constexpr const int NUM = 963;
        std::unique_ptr<int> uptr = std::make_unique<int>(NUM);
        {
            RObject robj = reflect(std::move(uptr));
            ASSERT_FALSE(robj.isEmpty());

            //Check if RObject can reflect as `int`
            EXPECT_TRUE(robj.canViewAs<int>());
            {
                auto view = robj.view<int>();
                ASSERT_TRUE(view);

                int value = view->get();
                EXPECT_EQ(value, NUM);
            }
            // Check if RObject can reflect as `int`
            EXPECT_TRUE(robj.canViewAs<const int*>());
            {
                auto view = robj.view<const int*>();
                ASSERT_TRUE(view);

                int value = *view->get();
                EXPECT_EQ(value, NUM);
            }
            // Check if RObject can reflect as `unique_ptr<int>`
            //EXPECT_TRUE(robj.canViewAs<std::unique_ptr<int>>());
            //{
            //    // Get a view of the value as `unique_ptr<int>`, ie. Original type.
            //    auto view = robj.view<std::unique_ptr<int>>();
            //    ASSERT_TRUE(view.has_value());

            //    const std::unique_ptr<int>& sptrVal = view->get();
            //    EXPECT_EQ(*sptrVal, NUM);
            //}
            //robj.canViewAs<const std::unique_ptr<int>*>();  //should not compile.
            //robj.view<const std::unique_ptr<int>*>();       //should not compile.
        }
    }
}
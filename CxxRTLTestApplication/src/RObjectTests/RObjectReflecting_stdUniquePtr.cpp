
#include <memory>
#include <gtest/gtest.h>

#include "Node.h"
#include "MyReflection.h"

using namespace test_utils;
using namespace rtl::access;

namespace rtl::unit_test
{
    TEST(RObject_reflecting_unique_ptr, reflect_pod_init_with_lvalue)
    {
        constexpr const int NUM = 963;
        std::unique_ptr<int> uptr = std::make_unique<int>(NUM);
        {
            // Reflect a move-only type directly into RObject
            RObject robj = reflect(std::move(uptr));
            ASSERT_FALSE(robj.isEmpty());

            // RObject can transparently expose the pointee type
            EXPECT_TRUE(robj.canViewAs<int>());

            auto intView = robj.view<int>();
            ASSERT_TRUE(intView);

            const int& valueNum = intView->get();
            EXPECT_EQ(valueNum, NUM);

            // RObject can also reflect as the original move-only type
            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<int>>());
            {
                // Multiple independent views to the same stored object- all valid before a move
                auto view0 = robj.view<std::unique_ptr<int>>();
                ASSERT_TRUE(view0);

                auto view1 = robj.view<std::unique_ptr<int>>();
                ASSERT_TRUE(view1);

                auto view2 = robj.view<std::unique_ptr<int>>();
                ASSERT_TRUE(view2);

                // A move from any view transfers ownership of the underlying object
                // RObject remains alive and type-consistent, but now holds an empty unique_ptr
                std::unique_ptr<int> uptr0 = view0->get();
                ASSERT_TRUE(uptr0);

                // Access the moved-out value
                EXPECT_EQ(*uptr0, NUM);

                // Verify the original pointer address matches
                EXPECT_EQ(uptr0.get(), &valueNum);

                // RObject still exists with correct metadata, but the stored unique_ptr is now empty
                EXPECT_FALSE(robj.isEmpty());

                // Any subsequent view will still be obtainable
                auto view3 = robj.view<std::unique_ptr<int>>();
                ASSERT_TRUE(view3);

                // But the unique_ptr inside is now empty due to the earlier move
                std::unique_ptr<int> uptr3 = view3->get();
                ASSERT_TRUE(uptr3 == nullptr);

                // All earlier views now yield empty unique_ptrs as well- no dangling pointers, no UB
                std::unique_ptr<int> uptr2 = view2->get();
                ASSERT_TRUE(uptr3 == nullptr);

                std::unique_ptr<int> uptr1 = view1->get();
                ASSERT_TRUE(uptr3 == nullptr);

                // Even reusing the moved-from view0 is safe- just returns empty
                std::unique_ptr<int> uptr00 = view0->get();
                ASSERT_TRUE(uptr00 == nullptr);
            }
        }
        // No heap leaks- ownership accounting is perfect
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, reflect_init_with_lvalue)
    {
        constexpr const int NUM = 963;
        std::unique_ptr<Node> uptr = std::make_unique<Node>(NUM);
        {
            // Reflect a move-only type directly into RObject
            RObject robj = reflect(std::move(uptr));
            ASSERT_FALSE(robj.isEmpty());

            // RObject can transparently expose the pointee type
            EXPECT_TRUE(robj.canViewAs<Node>());

            auto nodeView = robj.view<Node>();
            ASSERT_TRUE(nodeView);

            const Node& node = nodeView->get();
            EXPECT_EQ(node.data(), NUM);

            // RObject can also reflect as the original move-only type
            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<Node>>());
            {
                // Multiple independent views to the same stored object- all valid before a move
                auto view0 = robj.view<std::unique_ptr<Node>>();
                ASSERT_TRUE(view0);

                auto view1 = robj.view<std::unique_ptr<Node>>();
                ASSERT_TRUE(view1);

                auto view2 = robj.view<std::unique_ptr<Node>>();
                ASSERT_TRUE(view2);

                // A move from any view transfers ownership of the underlying object
                // RObject remains alive and type-consistent, but now holds an empty unique_ptr
                std::unique_ptr<Node> uptr0 = view0->get();
                ASSERT_TRUE(uptr0);

                // Access the moved-out value
                EXPECT_EQ(uptr0->data(), NUM);

                // Verify the original pointer address matches
                EXPECT_EQ(uptr0.get(), &node);

                // RObject still exists with correct metadata, but the stored unique_ptr is now empty
                EXPECT_FALSE(robj.isEmpty());

                // Any subsequent view will still be obtainable
                auto view3 = robj.view<std::unique_ptr<Node>>();
                ASSERT_TRUE(view3);

                // But the unique_ptr inside is now empty due to the earlier move
                std::unique_ptr<Node> uptr3 = view3->get();
                ASSERT_TRUE(uptr3 == nullptr);

                // All earlier views now yield empty unique_ptrs as well- no dangling pointers, no UB
                std::unique_ptr<Node> uptr2 = view2->get();
                ASSERT_TRUE(uptr3 == nullptr);

                std::unique_ptr<Node> uptr1 = view1->get();
                ASSERT_TRUE(uptr3 == nullptr);

                // Even reusing the moved-from view0 is safe- just returns empty
                std::unique_ptr<Node> uptr00 = view0->get();
                ASSERT_TRUE(uptr00 == nullptr);
            }
        }
        // No heap leaks- ownership accounting is perfect
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }



    TEST(RObject_reflecting_unique_ptr, reflect_init_with_lvalue_and_auto_delete)
    {
        {
            const int NUM = 452;
            std::unique_ptr<Node> nodePtr = std::make_unique<Node>(NUM);
            {
                RObject robj = reflect(nodePtr);
                ASSERT_FALSE(robj.isEmpty());

                // Check if RObject can reflect as `Node`
                EXPECT_TRUE(robj.canViewAs<Node>());
                {
                    auto view = robj.view<Node>();
                    ASSERT_TRUE(view);

                    const Node& node = view->get();
                    EXPECT_EQ(node.data(), NUM);
                    // Ensure no copy is made for viewing.
                    EXPECT_TRUE(Node::instanceCount() == 1);
                }
                // Check if RObject can reflect as `shared_ptr<Node>`
                EXPECT_FALSE(robj.canViewAs<std::shared_ptr<Node>>());
                {
                    // Get a view of the view as `shared_ptr<int>`
                    auto view = robj.view<std::shared_ptr<Node>>();
                    ASSERT_FALSE(view);
                }
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }

    
    TEST(RObject_reflecting_unique_ptr, reflect_init_with_rvalue)
    {
        {
            constexpr const int NUM = 943;
            RObject robj = reflect(std::make_unique<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());

            EXPECT_TRUE(Node::instanceCount() == 1);
            EXPECT_TRUE(robj.canViewAs<Node>());
            {
                auto view = robj.view<Node>();
                ASSERT_TRUE(view);

                const Node& node = view->get();
                EXPECT_EQ(node.data(), NUM);
            }
            // Check if RObject can be viewed as `unique_ptr<Node>`
            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<Node>>());
            {
                auto view = robj.view<std::unique_ptr<Node>>();
                ASSERT_TRUE(view);
                EXPECT_FALSE(robj.isEmpty());

                std::unique_ptr<Node> uptrNode = std::move(view->get());
                EXPECT_EQ(uptrNode->data(), NUM);
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, reflect_init_with_const_lvalue)
    {
        {
            const int NUM = 452;
            std::unique_ptr<const Node> nodePtr = std::make_unique<const Node>(NUM);
            {
                RObject robj = reflect(nodePtr);
                ASSERT_FALSE(robj.isEmpty());

                // Check if RObject can reflect as `Node`
                EXPECT_TRUE(robj.canViewAs<Node>());
                {
                    auto view = robj.view<Node>();
                    ASSERT_TRUE(view);

                    const Node& node = view->get();
                    EXPECT_EQ(node.data(), NUM);
                    // Ensure no copy is made for viewing.
                    EXPECT_TRUE(Node::instanceCount() == 1);
                }
                // Check if RObject can reflect as `unique_ptr<Node>`
                EXPECT_FALSE(robj.canViewAs<std::unique_ptr<Node>>());
                {
                    // Get a view of the view as `unique_ptr<Node>`
                    auto view = robj.view<std::unique_ptr<Node>>();
                    ASSERT_FALSE(view);
                }
                // Check if RObject can reflect as `unique_ptr<const Node>`
                EXPECT_FALSE(robj.canViewAs<std::unique_ptr<const Node>>());
                {
                    // Get a view of the view as `unique_ptr<Node>`
                    auto view = robj.view<std::unique_ptr<const Node>>();
                    EXPECT_TRUE(view);
                }
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}
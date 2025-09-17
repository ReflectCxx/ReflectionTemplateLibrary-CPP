
#include <memory>
#include <gtest/gtest.h>
#include <rtl/rtl.h>

#include "Node.h"

using namespace test_utils;
using namespace rtl;

namespace rtl::unit_test
{
    TEST(RObject_reflecting_unique_ptr, clone_on__heap_stack)
    {
        const int NUM = 43728;
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        {
            RObject robj0 = reflect(std::make_unique<Node>(NUM));
            ASSERT_FALSE(robj0.isEmpty());
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
            {
                auto [err, robj] = robj0.clone<alloc::Stack>();
                EXPECT_TRUE(err == error::TypeNotCopyConstructible);
                ASSERT_TRUE(robj.isEmpty());
                ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
            } {
                auto [err, robj] = robj0.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
                ASSERT_TRUE(robj.isEmpty());
                ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
            }
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, lvalue_no_double_delete)
    {
        {
            constexpr int NUM = 1635;
            int* numPtr = new int(NUM);
            std::unique_ptr<int> srcPtr(numPtr);
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

            // Reflect a move-only type directly into RObject
            RObject robj = reflect(std::move(srcPtr));
            ASSERT_FALSE(robj.isEmpty());

            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<int>>());
            // unique_ptr, ownership managed by RTL.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);

            auto view = robj.view<std::unique_ptr<int>>();
            ASSERT_TRUE(view);

            // get() - moves out the 'unique_ptr<int>' from 'robj'.
            // 'robj' still remains alive and type-consistent, but now holds an empty unique_ptr
            std::unique_ptr<int> uptr = view->get();
            ASSERT_TRUE(uptr);
            // RTL gave up the ownership after move-op.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
            // Access the moved-out value
            EXPECT_EQ(*uptr, NUM);

            int* ptr = uptr.release();
            // Addresses must be same.
            EXPECT_EQ(numPtr, ptr);
            delete ptr;     //RTL must not delete again, once 'robj' out of scope.
        }
        // there must not be any crash.
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, rvalue_no_double_delete)
    {
        {
            int NUM = 5323;
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

            // Reflect a move-only type directly into RObject
            RObject robj = reflect(std::unique_ptr<Node>(new Node(NUM)));
            ASSERT_FALSE(robj.isEmpty());

            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<Node>>());
            // unique_ptr, ownership managed by RTL.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);

            auto view = robj.view<std::unique_ptr<Node>>();
            ASSERT_TRUE(view);

            // get() - moves out the 'unique_ptr<int>' from 'robj'.
            // 'robj' still remains alive and type-consistent, but now holds an empty unique_ptr
            std::unique_ptr<Node> uptr = view->get();
            ASSERT_TRUE(uptr);
            // RTL gave up the ownership after move-op.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
            // Access the moved-out value
            EXPECT_EQ(uptr->data(), NUM);

            Node* ptr = uptr.release();
            // Addresses must be same.
            EXPECT_TRUE(ptr->data() == NUM);
            delete ptr;     //RTL must not delete again, once 'robj' out of scope.
        }
        // there must not be any crash.
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, pod_init_with_lvalue)
    {
        constexpr const int NUM = 8839;
        std::unique_ptr<int> uptr = std::make_unique<int>(NUM);
        // No heap leaks- ownership accounting is perfect
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

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

        // Multiple independent views to the same stored object- all valid before a move
        auto view0 = robj.view<std::unique_ptr<int>>();
        ASSERT_TRUE(view0);

        auto view1 = robj.view<std::unique_ptr<int>>();
        ASSERT_TRUE(view1);

        auto view2 = robj.view<std::unique_ptr<int>>();
        ASSERT_TRUE(view2);

        // unique_ptr, ownership managed by RTL.
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);

        // A move from any view transfers ownership of the underlying object
        // RObject remains alive and type-consistent, but now holds an empty unique_ptr
        std::unique_ptr<int> uptr0 = view0->get();
        ASSERT_TRUE(uptr0);

        // Access the moved-out value
        EXPECT_EQ(*uptr0, NUM);

        // Verify the original pointer address matches
        EXPECT_EQ(uptr0.get(), &valueNum);

        // RTL gave up the ownership after move-op.
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

        // RObject still exists with correct metadata, but the stored unique_ptr is now empty
        ASSERT_FALSE(robj.isEmpty());

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


    TEST(RObject_reflecting_unique_ptr, init_with_lvalue)
    {
        constexpr const int NUM = 16238;
        std::unique_ptr<Node> uptr = std::make_unique<Node>(NUM);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
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

            // unique_ptr, ownership managed by RTL.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);

            // A move from any view transfers ownership of the underlying object
            // RObject remains alive and type-consistent, but now holds an empty unique_ptr
            std::unique_ptr<Node> uptr0 = view0->get();
            ASSERT_TRUE(uptr0);

            // Access the moved-out value
            EXPECT_EQ(uptr0->data(), NUM);

            // Verify the original pointer address matches
            EXPECT_EQ(uptr0.get(), &node);

            // RObject still exists with correct metadata, but the stored unique_ptr is now empty
            ASSERT_FALSE(robj.isEmpty());

            // RTL gave up the ownership after move-op.
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
            // Node still exists.
            EXPECT_TRUE(Node::instanceCount() == 1);

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
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }



    TEST(RObject_reflecting_unique_ptr, destructor_call__reflectecting_lvalue)
    {
        const int NUM = 24028;
        std::unique_ptr<Node> nodePtr = std::make_unique<Node>(NUM);
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
        // Check if RObject can reflect as `unique_ptr<Node>`
        EXPECT_TRUE(robj.canViewAs<std::unique_ptr<Node>>());
        {
            // Get a view of the view as `shared_ptr<int>`
            auto view = robj.view<std::unique_ptr<Node>>();
            EXPECT_TRUE(view);
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() != 0);
            {
                std::unique_ptr<Node> movedOutPtr = view->get();
            }
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
            EXPECT_TRUE(Node::instanceCount() == 0);
            EXPECT_TRUE(Node::assertResourcesReleased());
        }
    }


    TEST(RObject_reflecting_unique_ptr, destructor_call__reflectecting_rvalue)
    {
        const int NUM = 28228;
        RObject robj = reflect(std::make_unique<Node>(NUM));
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
        // Check if RObject can reflect as `unique_ptr<Node>`
        EXPECT_TRUE(robj.canViewAs<std::unique_ptr<Node>>());
        {
            // Get a view of the view as `shared_ptr<int>`
            auto view = robj.view<std::unique_ptr<Node>>();
            EXPECT_TRUE(view);
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() != 0);
            {
                std::unique_ptr<Node> movedOutPtr = view->get();
            }
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
            EXPECT_TRUE(Node::instanceCount() == 0);
            EXPECT_TRUE(Node::assertResourcesReleased());
        }
    }


    TEST(RObject_reflecting_unique_ptr, init_with_rvalue)
    {
        {
            constexpr const int NUM = 32443;
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
                ASSERT_FALSE(robj.isEmpty());

                std::unique_ptr<Node> uptrNode = std::move(view->get());
                EXPECT_EQ(uptrNode->data(), NUM);
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RObject_reflecting_unique_ptr, init_with_const_lvalue)
    {
        {
            const int NUM = 35729;
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
                EXPECT_TRUE(robj.canViewAs<std::unique_ptr<const Node>>());
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


    TEST(RObject_reflecting_unique_ptr, init_with_const_rvalue)
    {
        {
            const int NUM = 39929;
            RObject robj = reflect(std::make_unique<const Node>(NUM));
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
            EXPECT_TRUE(robj.canViewAs<std::unique_ptr<const Node>>());
            {
                // Get a view of the view as `unique_ptr<Node>`
                auto view = robj.view<std::unique_ptr<const Node>>();
                EXPECT_TRUE(view);
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }

    TEST(RObject_reflecting_unique_ptr, create_clones)
    {
        const int NUM = 45429;
        RObject robj = reflect(std::make_unique<const Node>(NUM));
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
        } {
            auto [err, robj0] = robj.clone<rtl::alloc::Stack>();
            EXPECT_TRUE(err == rtl::error::TypeNotCopyConstructible);
            ASSERT_TRUE(robj0.isEmpty());
        }
    }
}
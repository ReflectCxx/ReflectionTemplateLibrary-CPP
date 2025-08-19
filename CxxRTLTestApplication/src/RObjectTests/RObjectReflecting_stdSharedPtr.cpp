
#include <memory>
#include <gtest/gtest.h>

#include "Node.h"
#include "MyReflection.h"

using namespace test_utils;
using namespace rtl::access;

namespace rtl::unit_test
{
    TEST(RObject_reflecting_shared_ptr, sharing_semantics__pod)
    {
        constexpr const int NUM = -20438;
        RObject robj = reflect(std::make_shared<int>(NUM));
        ASSERT_FALSE(robj.isEmpty());

        // --- Step 1: Verify reflection at wrapper level ---
        // Ensure RObject recognizes it can be viewed as a shared_ptr<int>.
        EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
        {
            // Obtain a view of the shared_ptr<int>.
            auto view = robj.view<std::shared_ptr<int>>();
            ASSERT_TRUE(view.has_value());

            {
                // Accessing via 'const ref' does not increase reference count.
                const std::shared_ptr<int>& sptrVal = view->get();
                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 1);
            } {
                // Copying the shared_ptr makes a shallow copy (ref-counted).
                std::shared_ptr<int> sptrVal = view->get();
                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 2);
            }
            // Original view is still valid, back to count 1 after local copy goes out of scope.
            const std::shared_ptr<int>& sptr = view->get();
            EXPECT_TRUE(sptr.use_count() == 1);
        }

        // --- Step 2: Final state check ---
        // At the end, ownership should return to robj alone.
        auto view = robj.view<std::shared_ptr<int>>();
        EXPECT_TRUE(view);

        const std::shared_ptr<int>& sptr = view->get();
        ASSERT_TRUE(sptr.use_count() == 1);
    }


    TEST(RObject_reflecting_shared_ptr, sharing_semantics__Node)
    {
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
        {
            constexpr const int NUM = -45109;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());
            ASSERT_TRUE(Node::instanceCount() == 1);

            // --- Step 1: Verify reflection at wrapper level ---
            // Ensure RObject recognizes it can be viewed as a shared_ptr<int>.
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
            {
                // Obtain a view of the shared_ptr<Node>.
                auto view = robj.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(view.has_value());

                {
                    // Accessing via 'const ref' does not increase reference count.
                    const std::shared_ptr<Node>& nptr = view->get();
                    EXPECT_EQ(nptr->data(), NUM);
                    EXPECT_TRUE(nptr.use_count() == 1);
                    ASSERT_TRUE(Node::instanceCount() == 1);
                } {
                    // Copying the shared_ptr makes a shallow copy (ref-counted).
                    std::shared_ptr<Node> nptr = view->get();
                    EXPECT_EQ(nptr->data(), NUM);
                    EXPECT_TRUE(nptr.use_count() == 2);
                    ASSERT_TRUE(Node::instanceCount() == 1);
                }
                // Original view is still valid, back to count 1 after local copy goes out of scope.          
                EXPECT_TRUE(view->get().use_count() == 1);
            }
            // --- Step 4: Final state check ---
            // At the end, ownership should return to robj alone.
            auto view = robj.view<std::shared_ptr<Node>>();
            EXPECT_TRUE(view);

            const std::shared_ptr<Node>& node = view->get();
            ASSERT_TRUE(node.use_count() == 1);
        }
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, cloning_semantics__pod_stack)
    {
        constexpr const int NUM = -20438;
        RObject robj = reflect(std::make_shared<int>(NUM));
        ASSERT_FALSE(robj.isEmpty());

        // --- Step 1: Clone by default (entity::Auto semantics) ---
        {
            // Default cloning shallow-copies the wrapper.
            auto [err, robj0] = robj.clone<alloc::Stack>();
            EXPECT_TRUE(err == error::None);

            // View clone as 'shared_ptr'.
            EXPECT_TRUE(robj0.canViewAs<std::shared_ptr<int>>());

            auto ptrView = robj0.view<std::shared_ptr<int>>();
            ASSERT_TRUE(ptrView); 

            const std::shared_ptr<int>& sptr = ptrView->get();
            EXPECT_EQ(*sptr, NUM);

            // View as the underlying int.
            EXPECT_TRUE(robj0.canViewAs<int>());

            auto view = robj0.view<int>();
            EXPECT_TRUE(view);
            EXPECT_EQ(view->get(), NUM);
        }

        // --- Step 2: Clone by 'Value' (entity::Value semantics) ---
        {
            // Copies the underlying value, *not* the wrapper.
            auto [err, robj0] = robj.clone<alloc::Stack, copy::Value>();
            EXPECT_TRUE(err == error::None);

            // Cannot view as shared_ptr, because we cloned the contained value.
            EXPECT_FALSE(robj0.canViewAs<std::shared_ptr<int>>());

            // Instead, can view as the underlying int.
            EXPECT_TRUE(robj0.canViewAs<int>());

            auto view = robj0.view<int>();
            EXPECT_TRUE(view);
            EXPECT_EQ(view->get(), NUM);
        }

        // --- Step 3: Clone with explicit wrapper semantics ---
        {
            // Explicitly request a clone at the wrapper level (entity::Wrapper).
            // This performs a shallow copy of the shared_ptr, incrementing ref count.
            auto [err, robj0] = robj.clone<alloc::Stack, copy::Wrapper>();
            EXPECT_TRUE(err == error::None);

            // Now the clone can also be viewed as shared_ptr<int>.
            EXPECT_TRUE(robj0.canViewAs<std::shared_ptr<int>>());

            auto ptrView = robj0.view<std::shared_ptr<int>>();
            ASSERT_TRUE(ptrView); 

            const std::shared_ptr<int>& nptr = ptrView->get();
            EXPECT_EQ(*nptr, NUM);

            auto view = robj0.view<std::shared_ptr<int>>();
            ASSERT_TRUE(view.has_value());

            {
                // Access as const ref: no copy, ref count remains shared between robj & robj0.
                const std::shared_ptr<int>& sptrVal = view->get();
                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 2); // shared by robj + robj0
            } {
                // Explicit copy makes another shallow copy of the shared_ptr.
                std::shared_ptr<int> sptrVal = view->get();
                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 3); // shared by robj + robj0 + sptrVal
            }
            // After local copy is gone, back to 2 owners (robj + robj0).
            EXPECT_TRUE(view->get().use_count() == 2);
        }

        // --- Step 4: Final state check ---
        // At the end, ownership should return to robj alone.
        auto view = robj.view<std::shared_ptr<int>>();
        EXPECT_TRUE(view);

        const std::shared_ptr<int>& sptr = view->get();
        ASSERT_TRUE(sptr.use_count() == 1);
    }


    TEST(RObject_reflecting_shared_ptr, cloning_semantics__pod_heap)
    {
        constexpr const int NUM = -291823;
        RObject robj = reflect(std::make_shared<int>(NUM));
        ASSERT_FALSE(robj.isEmpty());

        // --- Step 1: Clone by default (entity::Auto semantics) ---
        {
            // Default cloning shallow-copies the wrapper.
            auto [err, robj0] = robj.clone<alloc::Heap>();
            EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
            EXPECT_TRUE(robj0.isEmpty());
        }

        // --- Step 2: Clone by 'Value' (entity::Value semantics) ---
        {
            // Copies the underlying value, *not* the wrapper.
            auto [err, robj0] = robj.clone<alloc::Stack, copy::Value>();
            EXPECT_TRUE(err == error::None);

            // Cannot view as shared_ptr, because we cloned the contained value.
            EXPECT_FALSE(robj0.canViewAs<std::shared_ptr<int>>());

            // Instead, can view as the underlying int.
            EXPECT_TRUE(robj0.canViewAs<int>());

            auto view = robj0.view<int>();
            EXPECT_TRUE(view);
            EXPECT_EQ(view->get(), NUM);
        }

        // --- Step 3: Clone with explicit wrapper semantics ---
        {
            // Explicitly request a clone at the wrapper level (entity::Wrapper).
            // This performs a shallow copy of the shared_ptr, incrementing ref count.
            auto [err, robj0] = robj.clone<alloc::Heap, copy::Wrapper>();
            EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
            EXPECT_TRUE(robj0.isEmpty());
        }

        // --- Step 4: Final state check ---
        // At the end, ownership should return to robj alone.
        auto view = robj.view<std::shared_ptr<int>>();
        EXPECT_TRUE(view);

        const std::shared_ptr<int>& sptr = view->get();
        ASSERT_TRUE(sptr.use_count() == 1);
    }


    TEST(RObject_reflecting_shared_ptr, cloning_semantics__Node_on_stack)
    {
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
        {
            constexpr const int NUM = -45109;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());
            ASSERT_TRUE(Node::instanceCount() == 1);

            // --- Step 2: Clone by default (entity::Auto semantics) ---
            {
                // Default cloning shallow-copies the wrapper.
                auto [err, robj0] = robj.clone<alloc::Stack>();
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(Node::instanceCount() == 1);

                // View clone as 'shared_ptr'.
                EXPECT_TRUE(robj0.canViewAs<std::shared_ptr<Node>>());

                auto ptrView = robj0.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(ptrView);

                const auto& nptr = ptrView->get();
                EXPECT_EQ(nptr->data(), NUM);

                // View as the underlying Node.
                EXPECT_TRUE(robj0.canViewAs<Node>());
                auto node = robj0.view<Node>();
                EXPECT_EQ(node->get().data(), NUM);
            }

            // --- Step 3: Clone by 'Value' (entity::Value semantics) ---
            {
                // Copies the underlying value, *not* the wrapper.
                auto [err, robj0] = robj.clone<alloc::Stack, copy::Value>();
                EXPECT_TRUE(err == error::TypeNotCopyConstructible);
                ASSERT_TRUE(Node::instanceCount() == 1);
                ASSERT_TRUE(robj0.isEmpty());
            }

            // --- Step 4: Clone with explicit wrapper semantics ---
            {
                // Explicitly request a clone at the wrapper level (entity::Wrapper).
                // This performs a shallow copy of the shared_ptr, incrementing ref count.
                auto [err, robj0] = robj.clone<alloc::Stack, copy::Wrapper>();
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(Node::instanceCount() == 1);

                // Now the clone can also be viewed as shared_ptr<Node>.
                EXPECT_TRUE(robj0.canViewAs<std::shared_ptr<Node>>());
                
                auto view = robj0.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(view.has_value());
                {
                    // Access as const ref: no copy, ref count remains shared between robj & robj0.
                    const std::shared_ptr<Node>& nptr = view->get();
                    EXPECT_EQ(nptr->data(), NUM);
                    EXPECT_TRUE(nptr.use_count() == 2); // shared by robj + robj0
                } {
                    // Explicit copy makes another shallow copy of the shared_ptr.
                    std::shared_ptr<Node> nptr = view->get();
                    EXPECT_EQ(nptr->data(), NUM);
                    EXPECT_TRUE(nptr.use_count() == 3); // shared by robj + robj0 + sptrVal
                }
                // After local copy is gone, back to 2 owners (robj + robj0).
                EXPECT_TRUE(view->get().use_count() == 2);
            }

            // --- Step 4: Final state check ---
            // At the end, ownership should return to robj alone.
            auto view = robj.view<std::shared_ptr<Node>>();
            EXPECT_TRUE(view);

            const std::shared_ptr<Node>& node = view->get();
            ASSERT_TRUE(node.use_count() == 1);
        }
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, cloning_semantics__Node_on_heap)
    {
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
        {
            constexpr const int NUM = 241054;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());
            ASSERT_TRUE(Node::instanceCount() == 1);

            // --- Step 2: Clone by default (entity::Auto semantics) ---
            {
                // Default cloning shallow-copies the wrapper.
                auto [err, robj0] = robj.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
                EXPECT_TRUE(robj0.isEmpty());
                ASSERT_TRUE(Node::instanceCount() == 1);
            }

            // --- Step 3: Clone by 'Value' (entity::Value semantics) ---
            {
                // Copies the underlying value, *not* the wrapper.
                auto [err, robj0] = robj.clone<alloc::Heap, copy::Value>();
                EXPECT_TRUE(err == error::TypeNotCopyConstructible);
                ASSERT_TRUE(Node::instanceCount() == 1);
                ASSERT_TRUE(robj0.isEmpty());
            }

            // --- Step 4: Clone with explicit wrapper semantics ---
            {
                // Explicitly request a clone at the wrapper level (entity::Wrapper).
                // This performs a shallow copy of the shared_ptr, incrementing ref count.
                auto [err, robj0] = robj.clone<alloc::Heap, copy::Wrapper>();
                EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
                EXPECT_TRUE(robj0.isEmpty());
                ASSERT_TRUE(Node::instanceCount() == 1);
            }

            // --- Step 4: Final state check ---
            // At the end, ownership should return to robj alone.
            auto view = robj.view<std::shared_ptr<Node>>();
            EXPECT_TRUE(view);

            const std::shared_ptr<Node>& node = view->get();
            ASSERT_TRUE(node.use_count() == 1);
        }
        ASSERT_TRUE(Node::instanceCount() == 0);
        ASSERT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, reflect_init_with_lvalue)
    {
        {
            const int NUM = -1629;
            std::shared_ptr<Node> nodePtr = std::make_shared<Node>(NUM);
            {
                RObject robj = reflect(nodePtr);
                ASSERT_FALSE(robj.isEmpty());
                EXPECT_TRUE(nodePtr.use_count() == 2);

                // Check if RObject can reflect as `Node`
                EXPECT_TRUE(robj.canViewAs<Node>());
                {
                    auto view = robj.view<Node>();
                    ASSERT_TRUE(view);

                    const Node& node = view->get();
                    EXPECT_EQ(node.data(), NUM);
                    // Ensure no copy is made for viewing.
                    EXPECT_TRUE(Node::instanceCount() == 1);
                    // Being shared by 'nodePtr' & 'robj'.
                    EXPECT_TRUE(nodePtr.use_count() == 2);
                }
                // Check if RObject can reflect as `shared_ptr<Node>`
                EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
                {
                    // Get a view of the view as `shared_ptr<int>`
                    auto view = robj.view<std::shared_ptr<Node>>();
                    ASSERT_TRUE(view.has_value());
                    {
                        std::shared_ptr<Node> node = view->get();
                        EXPECT_EQ(node->data(), NUM);
                        //being shared by 'nodePtr', 'robj' and 'node'.
                        EXPECT_TRUE(nodePtr.use_count() == 3);
                    } {
                        const std::shared_ptr<Node>& node = view->get();
                        EXPECT_EQ(node->data(), NUM);
                        //being shared by 'nodePtr', 'robj' and 'node'.
                        EXPECT_TRUE(nodePtr.use_count() == 2);
                    }
                }
                //still shared by 'nodePtr' & 'robj'.
                EXPECT_TRUE(nodePtr.use_count() == 2);
            }
            //now owned by 'uptr' alone.
            EXPECT_TRUE(nodePtr.use_count() == 1);
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, reflect_init_with_rvalue)
    {
        {
            constexpr const int NUM = 6839;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());

            EXPECT_TRUE(Node::instanceCount() == 1);
            // Check if RObject can reflect as `shared_ptr<Node>`
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
            //view just holds ref/ptr.
            auto view = robj.view<std::shared_ptr<Node>>();
            ASSERT_TRUE(view.has_value());

            const std::shared_ptr<Node>& sptrNode = view->get();    //no copy
            EXPECT_EQ(sptrNode->data(), NUM);
            {
                std::shared_ptr<Node> sptrNode0 = view->get();
                //owned by 'robj' & sptrNode0.
                EXPECT_TRUE(sptrNode.use_count() == 2);
            }
            //owned by 'robj' alone, no 'lvalue' exists in this scope.
            EXPECT_TRUE(sptrNode.use_count() == 1);
            EXPECT_TRUE(robj.canViewAs<Node>());
            {
                auto view = robj.view<Node>();
                ASSERT_TRUE(view);

                const Node& node = view->get();
                EXPECT_EQ(node.data(), NUM);
                //owned by 'robj' alone.
                EXPECT_TRUE(sptrNode.use_count() == 1);
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, reflect_and_create_copies)
    {
        {
            constexpr const int NUM = 10742;
            RObject robj = reflect(std::make_shared<Node>(NUM));

            ASSERT_FALSE(robj.isEmpty());
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());

            auto view = robj.view<std::shared_ptr<Node>>();
            ASSERT_TRUE(view.has_value());

            // Access underlying value via the reflected shared_ptr
            const std::shared_ptr<Node>& sptrNode = view->get();
            EXPECT_EQ(sptrNode->data(), NUM);

            // ---------------------------------------------------------------------
            // 1. Heap-clone of STL wrappers is forbidden.
            //    This prevents accidental deep copies of smart pointers that
            //    could violate ownership semantics (e.g. double-deletion).
            // ---------------------------------------------------------------------
            auto [err, badObj] = robj.clone<alloc::Heap>();
            EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
            EXPECT_TRUE(badObj.isEmpty());

            // ---------------------------------------------------------------------
            // 2. clone using 'entity::Value': tries to copy the contained entity.
            //    Since Node is explicitly non-copyable, this yields an error.
            // ---------------------------------------------------------------------
            {
                auto [err0, robj0] = robj.clone<alloc::Stack, copy::Value>();
                EXPECT_TRUE(err0 == error::TypeNotCopyConstructible);
            }

            // ---------------------------------------------------------------------
            // 3. Explicit clone of the wrapper (entity::Wrapper):
            //    This performs a shallow copy of std::shared_ptr, incrementing the
            //    reference count while leaving the Node untouched.
            //    This demonstrates how RTL allows smart pointer semantics to be
            //    preserved even when the pointee type itself is non-copyable.
            // ---------------------------------------------------------------------
            {
                auto [err0, robj0] = robj.clone<alloc::Stack, copy::Wrapper>();
                EXPECT_TRUE(err0 == error::None);

                auto view = robj0.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(view.has_value());

                const std::shared_ptr<Node>& sptrNode0 = view->get();
                EXPECT_EQ(sptrNode0->data(), NUM);
                {
                    // Making another copy of shared_ptr, still shallow (reference-counted)
                    std::shared_ptr<Node> sptrNode1 = view->get();
                    EXPECT_EQ(sptrNode0->data(), NUM);
                    // Now shared by three entities: robj, robj0, and sptrNode1
                    EXPECT_TRUE(sptrNode.use_count() == 3);
                }
                // Back to two owners: robj and robj0
                EXPECT_TRUE(sptrNode.use_count() == 2);
            }

            // Finally, back to sole ownership by robj
            EXPECT_TRUE(sptrNode.use_count() == 1);
            EXPECT_TRUE(Node::instanceCount() == 1);
        }

        // After leaving scope: no leaks, all resources released
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }



    TEST(RObject_reflecting_shared_ptr, reflect_and_move_copies)
    {
        {
            constexpr const int NUM = -15442;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
            {
                // Get a view of the value as `shared_ptr<int>`
                auto view = robj.view<std::shared_ptr<Node>>();
                // Ensure the view is valid
                ASSERT_TRUE(view.has_value());
                {
                    std::shared_ptr<Node> sptrNode = view->get();
                    EXPECT_EQ(sptrNode->data(), NUM);
                    // Being shared by robj & sptrVal.
                    EXPECT_TRUE(sptrNode.use_count() == 2);
                }
                // Here owned by 'robj' alone.
                EXPECT_TRUE(view->get().use_count() == 1);
            } {
                //create copy of RObject itself.
                RObject robj0 = std::move(robj);
                //robj should be empty now.
                ASSERT_TRUE(robj.isEmpty());

                auto view = robj0.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(view.has_value());
                {
                    const std::shared_ptr<Node>& sptrNode = view->get();

                    EXPECT_EQ(sptrNode->data(), NUM);
                    //single owner now, just robj0.
                    EXPECT_TRUE(sptrNode.use_count() == 1);
                } {
                    //copy of shared_ptr got created.
                    std::shared_ptr<Node> sptrNode = view->get();

                    EXPECT_EQ(sptrNode->data(), NUM);
                    //being shared by two entities- robj0 & sptrVal.
                    EXPECT_TRUE(sptrNode.use_count() == 2);
                }
                //now owned by 'robj0' alone.
                EXPECT_TRUE(view->get().use_count() == 1);
            }
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, reflect_pod_and_move_copies)
    {
        constexpr const int NUM = 25738;
        RObject robj = reflect(std::make_shared<int>(NUM));
        ASSERT_FALSE(robj.isEmpty());

        // Check if RObject can reflect as `shared_ptr<int>`
        EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
        {
            // Get a view of the value as `shared_ptr<int>`
            auto view = robj.view<std::shared_ptr<int>>();
            // Ensure the view is valid
            ASSERT_TRUE(view.has_value());
            {
                std::shared_ptr<int> sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                //being shared by robj & sptrVal.
                EXPECT_TRUE(sptrVal.use_count() == 2);
            }
            //here owned by 'robj' alone.
            EXPECT_TRUE(view->get().use_count() == 1);
        } {
            //create copy of RObject itself.
            RObject robj0 = std::move(robj);
            //robj should be empty now.
            ASSERT_TRUE(robj.isEmpty());

            auto view = robj0.view<std::shared_ptr<int>>();
            ASSERT_TRUE(view.has_value());
            {
                const std::shared_ptr<int>& sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                //single owner now, just robj0.
                EXPECT_TRUE(sptrVal.use_count() == 1);
            } {
                //copy of shared_ptr got created.
                std::shared_ptr<int> sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                //being shared by two entities- robj0 & sptrVal.
                EXPECT_TRUE(sptrVal.use_count() == 2);
            }
            //now owned by 'robj0' alone.
            EXPECT_TRUE(view->get().use_count() == 1);
        }
    }
}
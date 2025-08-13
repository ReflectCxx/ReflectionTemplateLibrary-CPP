
#include <memory>
#include <gtest/gtest.h>

#include "Node.h"
#include "MyReflection.h"

using namespace test_utils;
using namespace rtl::access;

namespace rtl::unit_test
{
    TEST(RObject_reflecting_shared_ptr, reflect_init_with_lvalue)
    {
        {
            const int NUM = 452;
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
            //  robj.canViewAs<const std::shared_ptr<Node>*>();  //should not compile.
            //  robj.view<const std::shared_ptr<Node>*>();       //should not compile.
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
            constexpr const int NUM = 943;
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
            constexpr const int NUM = 293;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            
            ASSERT_FALSE(robj.isEmpty());
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
            
            auto view = robj.view<std::shared_ptr<Node>>();
            ASSERT_TRUE(view.has_value());

            const std::shared_ptr<Node>& sptrNode = view->get();
            EXPECT_EQ(sptrNode->data(), NUM);
            {
                // Clone of RObject reflecting smart-pointer on Heap, not allowed!
                auto [err, badObj] = robj.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::ReflectingStlWrapper_copyOnHeapDisallowed);
                EXPECT_TRUE(badObj.isEmpty());

                //create copy of RObject itself.
                auto [err0, robj0] = robj.clone<alloc::Stack>();
                EXPECT_TRUE(err0 == error::None);

                auto view = robj0.view<std::shared_ptr<Node>>();
                ASSERT_TRUE(view.has_value());

                const std::shared_ptr<Node>& sptrNode0 = view->get();
                EXPECT_EQ(sptrNode0->data(), NUM);
                {
                    std::shared_ptr<Node> sptrNode1 = view->get();
                    EXPECT_EQ(sptrNode0->data(), NUM);
                    //being shared by three entities- robj, robj0 & sptrNode1.
                    EXPECT_TRUE(sptrNode.use_count() == 3);
                }
                // Shared by two entities now- robj, robj0.
                EXPECT_TRUE(sptrNode.use_count() == 2);
            }
            // Owned by 'robj' alone now.
            EXPECT_TRUE(sptrNode.use_count() == 1);
            EXPECT_TRUE(Node::instanceCount() == 1);
        }
        EXPECT_TRUE(Node::instanceCount() == 0);
        EXPECT_TRUE(Node::assertResourcesReleased());
    }


    TEST(RObject_reflecting_shared_ptr, reflect_and_move_copies)
    {
        {
            constexpr const int NUM = -23;
            RObject robj = reflect(std::make_shared<Node>(NUM));
            ASSERT_FALSE(robj.isEmpty());
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<Node>>());
            {
                // Get a view of the value as `shared_ptr<int>`
                auto view = robj.view<std::shared_ptr<Node>>();
                // Ensure the view is valid
                ASSERT_TRUE(view.has_value());
                {
                /*  This is not a move in practice. Because get() returns a const reference,
                *   calling std::move on it does not allow modification of the underlying object (i.e., no move-from).
                *   The shared_ptr's move constructor would require a non-const rvalue to actually
                *   transfer ownership and const prevents that. So, This will COPY, not move.
                */  std::shared_ptr<Node> sptrNode(std::move(view->get()));

                    EXPECT_EQ(sptrNode->data(), NUM);
                    // Being shared by robj & sptrNode.
                    EXPECT_TRUE(sptrNode.use_count() == 2);
                } {
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


    TEST(RObject_reflecting_shared_ptr, reflect_pod_and_create_copies)
    {
        constexpr const int NUM = 293;
        RObject robj = reflect(std::make_shared<int>(NUM));
        ASSERT_FALSE(robj.isEmpty());

        // Check if RObject can reflect as `shared_ptr<int>`
        EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
        {
            // Get a view of the value as `shared_ptr<int>`
            auto view = robj.view<std::shared_ptr<int>>();
            // Ensure the view is valid (conversion succeeded)
            ASSERT_TRUE(view.has_value());
            {
                const std::shared_ptr<int>& sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 1);
            } {
                std::shared_ptr<int> sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                EXPECT_TRUE(sptrVal.use_count() == 2);
            }
            EXPECT_TRUE(view->get().use_count() == 1);
        } {
            //create copy of RObject itself.
            auto [err, robj0] = robj.clone<alloc::Stack>();
            ASSERT_TRUE(err == error::None);

            auto view = robj0.view<std::shared_ptr<int>>();
            ASSERT_TRUE(view.has_value());
            {
                const std::shared_ptr<int>& sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                //being shared by two entities- robj, robj0.
                EXPECT_TRUE(sptrVal.use_count() == 2);
            } {
                std::shared_ptr<int> sptrVal = view->get();

                EXPECT_EQ(*sptrVal, NUM);
                //being shared by three entities- robj, robj0 & sptrVal.
                EXPECT_TRUE(sptrVal.use_count() == 3);
            }
            //being shared by two entities- robj, robj0.
            EXPECT_TRUE(view->get().use_count() == 2);
        }
        //owned by 'robj' alone.
        ASSERT_TRUE(robj.view<std::shared_ptr<int>>()->get().use_count() == 1);
    }


    TEST(RObject_reflecting_shared_ptr, reflect_pod_and_move_copies)
    {
        constexpr const int NUM = -23;
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
            /*  This is not a move in practice. Because get() returns a const reference,
            *   calling std::move on it does not allow modification of the underlying object (i.e., no move-from).
            *   The shared_ptr's move constructor would require a non-const rvalue to actually 
            *   transfer ownership and const prevents that. So, This will COPY, not move.
            */  std::shared_ptr<int> sptrVal(std::move(view->get()));

                EXPECT_EQ(*sptrVal, NUM);
                //being shared by robj & sptrVal.
                EXPECT_TRUE(sptrVal.use_count() == 2);
            } {
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
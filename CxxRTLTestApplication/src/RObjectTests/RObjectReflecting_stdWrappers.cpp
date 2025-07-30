
#include <memory>
#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl::access;

namespace rtl
{
    namespace unit_test
    {
        TEST(RObject_std_wrapper_shared_ptr, reflect_init_with_lvalue)
        {
            constexpr const int NUM = 482;
            std::shared_ptr<int> uptr = std::make_shared<int>(NUM);
            {
                RObject robj = reflect(uptr);

                // Check if RObject can reflect as `int`
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
                // Check if RObject can reflect as `shared_ptr<int>`
                EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
                {
                    // Get a view of the value as `shared_ptr<int>`
                    auto view = robj.view<std::shared_ptr<int>>();

                    // Ensure the view is valid
                    ASSERT_TRUE(view.has_value());

                    // Access the converted bool value
                    const std::shared_ptr<int>& sptrVal = view->get();

                    // Verify the conversion result (non-zero -> true)
                    EXPECT_EQ(*sptrVal, NUM);

                    //being shared by 'uptr' & 'robj'.
                    EXPECT_TRUE(sptrVal.use_count() == 2);
                }
                //still shared by 'uptr' & 'robj'.
                EXPECT_TRUE(uptr.use_count() == 2);
                //  robj.canViewAs<const std::shared_ptr<int>*>();  //should not compile.
                //  robj.view<const std::shared_ptr<int>*>();       //should not compile.
            }
            //now owned by 'uptr' alone.
            EXPECT_TRUE(uptr.use_count() == 1);
        }


        TEST(RObject_std_wrapper_shared_ptr, reflect_init_with_rvalue)
        {
            constexpr const int NUM = 943;
            RObject robj = reflect(std::make_shared<int>(NUM));

            // Check if RObject can reflect as `int`
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
            // Check if RObject can reflect as `shared_ptr<int>`
            EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
            {
                // Get a view of the value as `bool`
                auto view = robj.view<std::shared_ptr<int>>();

                // Ensure the view is valid (conversion succeeded)
                ASSERT_TRUE(view.has_value());

                // Access the converted bool value
                const std::shared_ptr<int>& sptrVal = view->get();

                // Verify the conversion result (non-zero -> true)
                EXPECT_EQ(*sptrVal, NUM);

                //owned by 'robj' alone.
                EXPECT_TRUE(sptrVal.use_count() == 1);
            }
        }


        TEST(RObject_std_wrapper_shared_ptr, reflect_init_with_move)
        {
            constexpr const int NUM = 329;
            std::shared_ptr<int> uptr = std::make_shared<int>(NUM);
            {
                RObject robj = reflect(std::move(uptr));

                // Check if RObject can reflect as `int`
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
                // Check if RObject can reflect as `shared_ptr<int>`
                EXPECT_TRUE(robj.canViewAs<std::shared_ptr<int>>());
                {
                    // Get a view of the value as `bool`
                    auto view = robj.view<std::shared_ptr<int>>();

                    // Ensure the view is valid (conversion succeeded)
                    ASSERT_TRUE(view.has_value());

                    // Access the converted bool value
                    const std::shared_ptr<int>& sptrVal = view->get();

                    // Verify the conversion result (non-zero -> true)
                    EXPECT_EQ(*sptrVal, NUM);

                    //owned by 'robj' alone.
                    EXPECT_TRUE(sptrVal.use_count() == 1);
                }
            }
        }


        TEST(RObject_std_wrapper_shared_ptr, reflect_and_create_copies)
        {
            constexpr const int NUM = 293;
            RObject robj = reflect(std::make_shared<int>(NUM));

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


        TEST(RObject_std_wrapper_shared_ptr, reflect_and_move_copies)
        {
            constexpr const int NUM = -23;
            RObject robj = reflect(std::make_shared<int>(NUM));

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


    TEST(RObject_std_wrapper_unique_ptr, reflect_init_with_lvalue)
    {
        constexpr const int NUM = 963;
        std::unique_ptr<int> uptr = std::make_unique<int>(NUM);
        {
            //RObject robj = reflect(std::move(uptr));

            //// Check if RObject can reflect as `int`
            //EXPECT_TRUE(robj.canViewAs<int>());
            //{
            //    auto view = robj.view<int>();
            //    ASSERT_TRUE(view);

            //    int value = view->get();
            //    EXPECT_EQ(value, NUM);
            //}
            //// Check if RObject can reflect as `int`
            //EXPECT_TRUE(robj.canViewAs<const int*>());
            //{
            //    auto view = robj.view<const int*>();
            //    ASSERT_TRUE(view);

            //    int value = *view->get();
            //    EXPECT_EQ(value, NUM);
            //}
            //// Check if RObject can reflect as `unique_ptr<int>`
            //EXPECT_TRUE(robj.canViewAs<std::unique_ptr<int>>());
            //{
            //    // Get a view of the value as `unique_ptr<int>`
            //    auto view = robj.view<std::unique_ptr<int>>();

            //    // Ensure the view is valid
            //    ASSERT_TRUE(view.has_value());

            //    // Access the converted bool value
            //    const std::unique_ptr<int>& sptrVal = view->get();

            //    // Verify the conversion result (non-zero -> true)
            //    EXPECT_EQ(*sptrVal, NUM);
            //}
            //  robj.canViewAs<const std::unique_ptr<int>*>();  //should not compile.
            //  robj.view<const std::unique_ptr<int>*>();       //should not compile.
        }
    }
}
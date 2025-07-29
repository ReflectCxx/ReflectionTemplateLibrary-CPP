
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

                    EXPECT_TRUE(sptrVal.use_count() == 2);
                }
                EXPECT_TRUE(uptr.use_count() == 2);
                //  robj.canViewAs<const std::shared_ptr<int>*>();  //should not compile.
                //  robj.view<const std::shared_ptr<int>*>();       //should not compile.
            }
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
                {
                    //rtl::view internally holds a reference to std::shared_ptr<int> (always)
                    rtl::view<std::shared_ptr<int>> view0 = *view;

                    //No copy of 'std::shared_ptr<int>' is made internally.
                    EXPECT_TRUE(view0.get().use_count() == 1);

                    //Now we are actually copying from the reference held inside 'view<shared_ptr<int>>'
                    std::shared_ptr<int> sptrVal = view0.get();

                    EXPECT_EQ(*sptrVal, NUM);
                    EXPECT_TRUE(sptrVal.use_count() == 2);
                }
                EXPECT_TRUE(view->get().use_count() == 1);
            } {
                //create copy of RObject itself.
                RObject robj0 = robj;
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
                //being shared by two entities now- robj, robj0.
                EXPECT_TRUE(view->get().use_count() == 2);
                {
                    //rtl::view internally holds a reference to std::shared_ptr<int> (always)
                    rtl::view<std::shared_ptr<int>> view0 = *view;

                    //No copy of 'std::shared_ptr<int>' is made internally.
                    EXPECT_TRUE(view0.get().use_count() == 2);

                    //Now we are actually copying from the reference held inside 'view<shared_ptr<int>>'
                    std::shared_ptr<int> sptrVal = view0.get();

                    EXPECT_EQ(*sptrVal, NUM);
                    //being shared by three entities- robj, robj0 & sptrVal.
                    EXPECT_TRUE(sptrVal.use_count() == 3);
                }
                //being shared by two entities- robj, robj0.
                EXPECT_TRUE(view->get().use_count() == 2);
            }
            //only copy left now is 'robj'.
            ASSERT_TRUE(robj.view<std::shared_ptr<int>>()->get().use_count() == 1);
        }
    }
}
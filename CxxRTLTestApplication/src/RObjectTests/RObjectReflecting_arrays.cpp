/**
 * @file RObjectReflectionTests.cpp
 * @brief Unit tests for rtl::RObject reflection system, validating support for std::vector and trivial C-style arrays.
 *
 * This suite tests the behavior of `rtl::reflect` and `.view<T>()`:
 * - Ensures reflection works for lvalue, rvalue, and pointer forms.
 * - Verifies zero-copy behavior for pointer-based inputs.
 * - Confirms support for reflection of C-style arrays into std::array<T, N>.
 *
 * Components tested:
 * - `rtl::reflect`     -> creates RObject from value or pointer
 * - `RObject::view<T>` -> provides typed, non-owning access to the internal value
 * - `canViewAs<T>`  -> checks if a view of type T is supported
 */

#include <gtest/gtest.h>

#include "MyReflection.h"

using namespace rtl::access;

namespace rtl {
    namespace unit_test {

        // Test: Reflect lvalue std::vector<int>
        TEST(RObject_view_vector, init_with_stdVector_int_lvalue)
        {
            std::vector<int> input = { 1, 2, 3, 4, 5 };
            RObject robj = rtl::reflect(input);  // reflect by copy

            ASSERT_TRUE(robj.canViewAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(inputView, input);
        }

        // Test: Reflect std::vector<int>* (pointer to lvalue)
        TEST(RObject_view_vector, init_with_stdVector_int_lvalue_ptr)
        {
            std::vector<int> input = { 1, 2, 3, 4, 5 };
            RObject robj = rtl::reflect(&input);  // reflect by reference

            ASSERT_TRUE(robj.canViewAs<const std::vector<int>*>());

            const auto& vec_view = robj.view<const std::vector<int>*>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>* inputView = vec_view->get();

            // No copy made since RObject was initialized with a pointer
            ASSERT_EQ(inputView, &input);
        }

        // Test: Reflect rvalue std::vector<int>
        TEST(RObject_view_vector, init_with_stdVector_int_rvalue)
        {
            RObject robj = rtl::reflect(std::vector<int>({ 1, 2, 3, 4, 5 }));

            ASSERT_TRUE(robj.canViewAs<std::vector<int>>());

            auto vec_view = robj.view<std::vector<int>>();
            ASSERT_TRUE(vec_view.has_value());

            const std::vector<int>& inputView = vec_view->get();
            ASSERT_EQ(inputView, std::vector<int>({ 1, 2, 3, 4, 5 }));
        }

        // Test: Reflect int[3] -> std::array<int, 3>
        TEST(RObject_array_reflection, reflect_int_array)
        {
            int data[3] = { 10, 20, 30 };
            RObject robj = rtl::reflect(data);

            using ExpectedArray = std::array<int, 3>;
            ASSERT_TRUE(robj.canViewAs<ExpectedArray>());

            auto view = robj.view<ExpectedArray>();
            ASSERT_TRUE(view.has_value());

            const ExpectedArray& arr = view->get();
            EXPECT_EQ(arr[0], 10);
            EXPECT_EQ(arr[1], 20);
            EXPECT_EQ(arr[2], 30);
        }

        // Macro: Generate tests for trivial C-style arrays -> std::array<T, N>
#define TEST_TRIVIAL_ARRAY_REFLECTION(TYPE, SIZE, ...)                                 \
        TEST(RObject_array_reflection, reflect_##TYPE##_array_##SIZE)                      \
        {                                                                                   \
            TYPE data[SIZE] = { __VA_ARGS__ };                                              \
            RObject robj = rtl::reflect(data);                                              \
            using ExpectedArray = std::array<TYPE, SIZE>;                                   \
            ASSERT_TRUE(robj.canViewAs<ExpectedArray>());                                \
            auto view = robj.view<ExpectedArray>();                                         \
            ASSERT_TRUE(view.has_value());                                                  \
            const ExpectedArray& arr = view->get();                                         \
            for (size_t i = 0; i < SIZE; ++i)                                               \
                EXPECT_EQ(arr[i], data[i]);                                                 \
        }

    // Tests for all trivial types with various array sizes
        TEST_TRIVIAL_ARRAY_REFLECTION(int, 3, 1, 2, 3)
        TEST_TRIVIAL_ARRAY_REFLECTION(float, 4, 1.0f, 2.0f, 3.0f, 4.0f)
        TEST_TRIVIAL_ARRAY_REFLECTION(double, 2, 3.14, 2.71)
        TEST_TRIVIAL_ARRAY_REFLECTION(bool, 3, true, false, true)

    } // namespace unit_test
} // namespace rtl

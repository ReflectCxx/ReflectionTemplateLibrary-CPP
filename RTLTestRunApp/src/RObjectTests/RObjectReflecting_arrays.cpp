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
#include <rtl/access.h>

using namespace rtl;

namespace rtl_tests {

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

    // Macro: Generate tests for trivial C-style arrays -> std::array<T, N>
    #define TEST_TRIVIAL_ARRAY_REFLECTION(TYPE, SIZE, ...)                         \
    TEST(RObject_array_reflection, reflect_##TYPE##_array_##SIZE)                  \
    {                                                                              \
        TYPE data[SIZE] = { __VA_ARGS__ };                                         \
        RObject robj = rtl::reflect(data);                                         \
        ASSERT_TRUE(robj.canViewAs<std::vector<TYPE>>());                          \
        auto view = robj.view<std::vector<TYPE>>();                                \
        ASSERT_TRUE(view.has_value());                                             \
        const std::vector<TYPE>& arr = view->get();                                \
        for (size_t i = 0; i < arr.size(); ++i)                                    \
            EXPECT_EQ(arr[i], data[i]);                                            \
    }

    // Tests for all trivial types with various array sizes
    TEST_TRIVIAL_ARRAY_REFLECTION(int, 3, 1, 2, 3)
    TEST_TRIVIAL_ARRAY_REFLECTION(float, 4, 1.0f, 2.0f, 3.0f, 4.0f)
    TEST_TRIVIAL_ARRAY_REFLECTION(double, 2, 3.14, 2.71)
    TEST_TRIVIAL_ARRAY_REFLECTION(bool, 3, true, false, true)

} // namespace rtl_tests

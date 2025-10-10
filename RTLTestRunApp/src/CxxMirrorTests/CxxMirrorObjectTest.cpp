
#include <gtest/gtest.h>
#include <cstring>
#include <rtl/rtl.h>

#include "CxxMirrorToJson.h"

namespace
{
    const rtl::CxxMirror cxx_mirror() 
    {
        return rtl::CxxMirror({

            // Register char as a record type (fundamental but instantiable).
            rtl::type().record<char>("char").build(),

            // Register strlen as a global function (C library function).
            rtl::type().function("strlen").build(strlen),

            // Register member function push_back(const int&) for std::vector<int>.
            // Demonstrates overload resolution via explicit signature selection.
            rtl::type().member<std::vector<int>>().method<const int&>("push_back").build(&std::vector<int>::push_back),

            // Register const-qualified method empty() for std::vector<int>.
            // RTL enforces const-correctness by separating methodConst.
            rtl::type().member<std::vector<int>>().methodConst("empty").build(&std::vector<int>::empty),

            // Register std::vector<int> itself as a record with name "vector_int".
            rtl::type().record<std::vector<int>>("vector_int").build(),

            // Register strlen again, redundant and gets ignored.
            rtl::type().function("strlen").build(std::strlen)
        });
    }
}


namespace rtl_tests
{

    TEST(CxxMirrorObjectTest, multiple_initializations_same_set__with_std_vector)
    {
        std::string mirrorStr0;
        {
            // Two mirrors constructed from same set of registrations must serialize identically.
            // Confirms stability of metadata and deterministic JSON output.
            rtl::CxxMirror mirror = cxx_mirror();
            rtl::CxxMirror mirror0 = mirror;
            mirrorStr0 = rtl::CxxMirrorToJson::toJson(mirror0);
        }
        std::string mirrorStr1;
        {
            // Freshly constructed mirror should serialize identically to previous one.
            mirrorStr1 = rtl::CxxMirrorToJson::toJson(cxx_mirror());
        }
        EXPECT_EQ(mirrorStr0, mirrorStr1);

        // Retrieve the reflected record for std::vector<int>.
        std::optional<rtl::Record> classVectorInt = cxx_mirror().getRecord("vector_int");
        ASSERT_TRUE(classVectorInt);

        // Create an instance of std::vector<int> on the stack via RTL.
        // Uses RObject with stack lifetime.
        auto [err, robj] = classVectorInt->create<rtl::alloc::Stack>();
        EXPECT_TRUE(err == rtl::error::None);
        ASSERT_FALSE(robj.isEmpty());

        {
            // Lookup the const method empty() in std::vector<int>.
            std::optional<rtl::Method> isEmpty = classVectorInt->getMethod("empty");
            ASSERT_TRUE(isEmpty);

            // Bind the reflected method to the object and call it.
            // Exception-free API: returns error code + result object.
            auto [err, ret] = isEmpty->bind(robj).call();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());

            // Safe typed access to return value via rtl::view<bool>.
            std::optional<rtl::view<bool>> rview = ret.view<bool>();
            ASSERT_TRUE(rview);
            EXPECT_TRUE(rview->get()); // Newly created vector should be empty.
        }

        // Prepare a native vector with values to push.
        std::vector<int> intArr0 = { 1565, 7271, 4357 };
        {
            // Lookup push_back method and call it multiple times with different values.
            std::optional<rtl::Method> push = classVectorInt->getMethod("push_back");
            ASSERT_TRUE(push);
            {
                auto [err, ret] = push->bind<const int&>(robj).call(intArr0[0]);
                EXPECT_TRUE(err == rtl::error::None);
            } {
                auto [err, ret] = push->bind<const int&>(robj).call(intArr0[1]);
                EXPECT_TRUE(err == rtl::error::None);
            } {
                auto [err, ret] = push->bind<const int&>(robj).call(intArr0[2]);
                EXPECT_TRUE(err == rtl::error::None);
            }
        }

        // Verify that reflected object can be safely reinterpreted as std::vector<int>.
        EXPECT_TRUE(robj.canViewAs<std::vector<int>>());

        // Access internal vector instance safely via rtl::view.
        std::optional<rtl::view<std::vector<int>>> vecView = robj.view<std::vector<int>>();
        ASSERT_TRUE(vecView);

        // Get reference to actual underlying vector and compare with expected values.
        auto& intArr1 = vecView->get();
        EXPECT_EQ(intArr0, intArr1);
    }


    // This test demonstrates redundant function registration handling
    // and argument forwarding quirks for C-style strings.
    TEST(CxxMirrorObjectTest, rednudant_registration__std_cstring_function)
    {
        auto cxxMirror = rtl::CxxMirror({

            // Redundant registrations
            rtl::type().function("strlen").build(std::strlen),
            rtl::type().function("strlen").build(std::strlen)

/*          emits warning on console -
            [WARNING] Multiple registrations of the same function-pointer detected.
                      function-pointer already registered as "strlen"
                      This registration is ignored.     */
        });

        std::optional<rtl::Function> cstrLen = cxxMirror.getFunction("strlen");
        ASSERT_TRUE(cstrLen);

        {
            // Case 1: normal pointer (deduces as 'const char*')
            const char* cstr = "Reflection Template Library C++";

            auto [err, ret] = cstrLen->bind().call(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = std::strlen(cstr);
            EXPECT_EQ(rlen, clen);
        } {
            // Case 2: constexpr top-level const (deduces as 'const char* const&')
            constexpr const char* cstr = "Reflection Template Library C++";

            // Need to forward as 'const char*'
            auto [err, ret] = cstrLen->bind<const char*>()(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = std::strlen(cstr);
            EXPECT_EQ(rlen, clen);
        } {
            // Case 3: string literal (deduces as const char[N], here const char[32])
            // Must explicitly forward as 'const char*'.
            auto [err, ret] = cstrLen->bind<const char*>()("Reflection Template Library C++");
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = std::strlen("Reflection Template Library C++");
            EXPECT_EQ(rlen, clen);
        }
    }


    TEST(CxxMirrorObjectTest, redundant_registration__std_cstring_func_with_global_cstring)
    {
        auto cxxMirror = rtl::CxxMirror({

            // Register strlen (C function) under the name "strlen".
            // RTL tracks uniqueness of function-pointer registrations.
            rtl::type().function("strlen").build(strlen),

            // Attempt to register the same function-pointer again.
            // RTL emits a warning and ignores this redundant registration,
            // ensuring stable, non-ambiguous metadata.
            rtl::type().function("strlen").build(std::strlen)

            /* Console output:
                [WARNING] Multiple registrations of the same function-pointer detected.
                          function-pointer already registered as "strlen"
                          This registration is ignored.
            */
        });

        // Retrieve the reflected function "strlen" from the mirror.
        std::optional<rtl::Function> cstrLen = cxxMirror.getFunction("strlen");
        ASSERT_TRUE(cstrLen);

        // Prepare a C-style string for testing.
        const char* cstr = "Modern C++ Reflection Framework";

        // Bind the reflected strlen and call it with cstr.
        // RTL returns error code + result object instead of exceptions.
        auto [err, ret] = cstrLen->bind().call(cstr);

        ASSERT_TRUE(err == rtl::error::None);
        ASSERT_FALSE(ret.isEmpty());
        EXPECT_TRUE(ret.canViewAs<size_t>());

        // Safely extract the return value as size_t via typed view.
        std::optional<rtl::view<size_t>> rview = ret.view<std::size_t>();
        ASSERT_TRUE(rview);

        std::size_t rlen = rview->get();
        std::size_t clen = std::strlen(cstr);

        // Verify RTL-reflected call matches native call.
        EXPECT_EQ(rlen, clen);
    }



    TEST(CxxMirrorObjectTest, redundant_regis_with_namespace__std_cstring_func_with_global_cstring)
    {
        auto cxxMirror = rtl::CxxMirror({
            // Redundant registrations with different namespaces.
            // No warning is emitted, because they produce different rtl::Function entries
            // (one global, one inside namespace "std").
            // Both functions wrap the same function-pointer, so their FunctorIds match.
            rtl::type().function("strlen").build(strlen),
            rtl::type().ns("std").function("strlen").build(std::strlen)
        });

        // Lookup global function "strlen".
        std::optional<rtl::Function> cstrLen = cxxMirror.getFunction("strlen");
        ASSERT_TRUE(cstrLen);
        {
            const char* cstr = "Modern C++ Reflection Framework";

            // Call the reflected global strlen.
            auto [err, ret] = cstrLen->bind().call(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = strlen(cstr);
            EXPECT_EQ(rlen, clen);
        }

        // Lookup namespaced function "std::strlen".
        std::optional<rtl::Function> stdStrLen = cxxMirror.getFunction("std", "strlen");
        ASSERT_TRUE(stdStrLen);
        {
            const char* cstr = "Modern C++ Reflection Framework";

            // Call the reflected std::strlen.
            auto [err, ret] = stdStrLen->bind().call(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = std::strlen(cstr);
            EXPECT_EQ(rlen, clen);
        }

        // Even though the functions are registered in different namespaces,
        // the underlying FunctorIds (which identify function-pointers) must be equal.
        const std::vector<rtl::detail::FunctorId>& cfunctorIds = cstrLen->getFunctors();
        const std::vector<rtl::detail::FunctorId>& stdfunctorIds = stdStrLen->getFunctors();

        EXPECT_EQ(cfunctorIds, stdfunctorIds);
    }



    TEST(CxxMirrorObjectTest, redundant_regis_with_different_names__std_cstring_func_with_global_cstring)
    {
        auto cxxMirror = rtl::CxxMirror({
            // Redundant registrations with different symbolic names.
            // No warning is emitted, since each rtl::Function has a distinct name.
            // Both map to the same underlying function-pointer, so FunctorIds match.
            rtl::type().function("cStrlen").build(strlen),
            rtl::type().function("stdStrlen").build(std::strlen)
        });

        // Lookup function registered as "cStrlen".
        std::optional<rtl::Function> cstrLen = cxxMirror.getFunction("cStrlen");
        ASSERT_TRUE(cstrLen);
        {
            const char* cstr = "Modern C++ Reflection Framework";

            // Call reflected cStrlen.
            auto [err, ret] = cstrLen->bind().call(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = strlen(cstr);
            EXPECT_EQ(rlen, clen);
        }

        // Lookup function registered as "stdStrlen".
        std::optional<rtl::Function> stdStrLen = cxxMirror.getFunction("stdStrlen");
        ASSERT_TRUE(stdStrLen);
        {
            const char* cstr = "Modern C++ Reflection Framework";

            // Call reflected stdStrlen.
            auto [err, ret] = stdStrLen->bind().call(cstr);
            ASSERT_TRUE(err == rtl::error::None);

            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<std::size_t>());

            std::optional<rtl::view<std::size_t>> rview = ret.view<std::size_t>();
            ASSERT_TRUE(rview);

            std::size_t rlen = rview->get();
            std::size_t clen = std::strlen(cstr);
            EXPECT_EQ(rlen, clen);
        }

        // Despite different symbolic names, both reflect the same function-pointer.
        // Hence, their FunctorIds must be identical.
        const std::vector<rtl::detail::FunctorId>& cfunctorIds = cstrLen->getFunctors();
        const std::vector<rtl::detail::FunctorId>& stdfunctorIds = stdStrLen->getFunctors();

        EXPECT_EQ(cfunctorIds, stdfunctorIds);
    }
}

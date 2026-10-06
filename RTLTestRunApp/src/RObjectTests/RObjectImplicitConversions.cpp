
#include <gtest/gtest.h>

#include <rtl/detail/inc/ConversionUtils.h>

namespace rtl_tests
{
    TEST(RObject_conversions, implicit_safe_and_unsafe)
    {
        using rtl::traits::is_safe_conversion_v;

        // === Self conversions (trivial) ===
        static_assert(is_safe_conversion_v<int, int>);
        static_assert(is_safe_conversion_v<const int, int>);
        static_assert(is_safe_conversion_v<int, const int>);

        //static_assert(is_safe_conversion_v<int*, void*>);              // pointer -> void*

        // === Safe conversions (should all be true) ===
        static_assert(is_safe_conversion_v<bool, int>);                 // widening bool -> int
        static_assert(is_safe_conversion_v<bool, double>);              // widening bool -> double

        static_assert(is_safe_conversion_v<int, long>);                 // widening int -> long
        static_assert(is_safe_conversion_v<int, long long>);            // widening int -> long long
        static_assert(is_safe_conversion_v<int, double>);               // exact int -> double
        static_assert(is_safe_conversion_v<int, double>);               // true on typical platforms
        static_assert(is_safe_conversion_v<int32_t, double>);           // true
        static_assert(is_safe_conversion_v<unsigned int, unsigned long>);
        static_assert(is_safe_conversion_v<unsigned int, unsigned long long>);

        static_assert(is_safe_conversion_v<char, int>);                 // widening char -> int
        static_assert(is_safe_conversion_v<short, int>);                // widening short -> int
        static_assert(is_safe_conversion_v<float, double>);             // widening float -> double
        static_assert(is_safe_conversion_v<unsigned char, unsigned int>);
        static_assert(is_safe_conversion_v<unsigned short, unsigned int>);

        // === Unsafe conversions (should all be false) ===
        static_assert(!is_safe_conversion_v<long long, int>);          // narrowing
        static_assert(!is_safe_conversion_v<unsigned long long, unsigned int>);
        static_assert(!is_safe_conversion_v<double, float>);           // narrowing float precision
        static_assert(!is_safe_conversion_v<double, int>);             // narrowing + truncation
        static_assert(!is_safe_conversion_v<float, int>);              // narrowing + truncation
        static_assert(!is_safe_conversion_v<int, char>);                // narrowing
        static_assert(!is_safe_conversion_v<unsigned int, char>);       // narrowing
        static_assert(!is_safe_conversion_v<signed char, unsigned char>); // sign change
        static_assert(!is_safe_conversion_v<unsigned char, signed char>); // sign change
        static_assert(!is_safe_conversion_v<void*, int*>);              // pointer -> pointer different type
        static_assert(!is_safe_conversion_v<const int*, int*>);         // dropping const
        static_assert(!is_safe_conversion_v<int*, const int*>);         // adding const (still not safe in our conservative def)
        static_assert(!is_safe_conversion_v<int, unsigned int>);        // // Technically "safe" but yields large number (-1)
        static_assert(!is_safe_conversion_v<long long, double>); // false
        static_assert(!is_safe_conversion_v<uint64_t, double>); // false

        EXPECT_TRUE(true);
    }
}

/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <type_traits>
#include <limits>
#include <cstdint>

namespace rtl::traits {

    template <typename From, typename To>
    constexpr bool is_safe_conversion_v = [] {
        // 1. Same type check (ignoring cv-qualifiers)
        using NakedFrom = std::remove_cv_t<From>;
        using NakedTo = std::remove_cv_t<To>;

        if constexpr (std::is_same_v<NakedFrom, NakedTo>)
            return true;

        // 2. Boolean conversion handling
        if constexpr (std::is_same_v<NakedTo, bool>)
            return std::is_arithmetic_v<NakedFrom>;
        if constexpr (std::is_same_v<NakedFrom, bool>)
            return std::is_arithmetic_v<NakedTo>;

        // 3. Character type safety
        constexpr bool from_char = std::is_same_v<NakedFrom, char> ||
            std::is_same_v<NakedFrom, signed char> ||
            std::is_same_v<NakedFrom, unsigned char>;
        constexpr bool to_char = std::is_same_v<NakedTo, char> ||
            std::is_same_v<NakedTo, signed char> ||
            std::is_same_v<NakedTo, unsigned char>;

        if constexpr (from_char || to_char) {
            // Block sign changes between char types
            if constexpr ((std::is_same_v<NakedFrom, signed char> && std::is_same_v<NakedTo, unsigned char>) ||
                (std::is_same_v<NakedFrom, unsigned char> && std::is_same_v<NakedTo, signed char>))
                return false;

            // Allow same-sign conversions between char types
            if constexpr (from_char && to_char)
                return (std::is_signed_v<NakedFrom> == std::is_signed_v<NakedTo>);

            // For numeric->char, require size safety
            if constexpr (to_char)
                return sizeof(NakedFrom) < sizeof(NakedTo);
        }

        // 4. Require both types to be arithmetic
        if constexpr (!std::is_arithmetic_v<NakedFrom> || !std::is_arithmetic_v<NakedTo>)
            return false;

        // 5. Numeric conversion safety
        // Floating-point to integer: never safe (truncation)
        if constexpr (std::is_floating_point_v<NakedFrom> && std::is_integral_v<NakedTo>)
            return false;

        // Integer to floating-point: check mantissa precision
        if constexpr (std::is_integral_v<NakedFrom> && std::is_floating_point_v<NakedTo>)
            return std::numeric_limits<NakedTo>::digits >= std::numeric_limits<NakedFrom>::digits;

        // Floating-point to floating-point: check both digits and exponent
        if constexpr (std::is_floating_point_v<NakedFrom> && std::is_floating_point_v<NakedTo>)
            return std::numeric_limits<NakedTo>::digits >= std::numeric_limits<NakedFrom>::digits &&
            std::numeric_limits<NakedTo>::max_exponent >= std::numeric_limits<NakedFrom>::max_exponent;

        // Integer to integer:
        if constexpr (std::is_integral_v<NakedFrom> && std::is_integral_v<NakedTo>) {
            // Different signedness requires larger destination
            if constexpr (std::is_signed_v<NakedFrom> != std::is_signed_v<NakedTo>)
                return sizeof(NakedTo) > sizeof(NakedFrom);

            // Same signedness requires equal or larger size
            return sizeof(NakedTo) >= sizeof(NakedFrom);
        }

        return false;
    }();
}
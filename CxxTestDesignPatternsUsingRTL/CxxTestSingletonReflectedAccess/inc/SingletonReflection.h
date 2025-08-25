#pragma once

#include "RTLibInterface.h"

namespace singleton_test {

    /**
     * @brief The OriginalReflection struct provides reflection capabilities for the "Original" class.
     *
     * This struct is designed as a monostate class, meaning it provides shared functionality
     * without requiring instantiation. It uses the reflection system to dynamically register
     * and retrieve metadata for the "Original" class, including its methods and constructor.
     */
    struct Reflection
    {
        Reflection() = delete;

        Reflection(const Reflection&) = delete;

        Reflection& operator=(const Reflection&) = delete;

        static const std::optional<rtl::Record>& getSingletonClass();
    };
}
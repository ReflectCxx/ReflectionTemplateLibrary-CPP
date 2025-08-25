#pragma once

#include "RTLibInterface.h"

namespace proxy_test {

    /**
     * @brief The OriginalReflection struct provides reflection capabilities for the "Original" class.
     *
     * This struct is designed as a monostate class, meaning it provides shared functionality
     * without requiring instantiation. It uses the reflection system to dynamically register
     * and retrieve metadata for the "Original" class, including its methods and constructor.
     */
    struct OriginalReflection
    {
        /**
         * @brief Deleted default constructor to prevent instantiation.
         *
         * The OriginalReflection struct is designed to be used statically, so no instances
         * of this struct should be created.
         */
        OriginalReflection() = delete;

        /**
         * @brief Deleted copy constructor to prevent copying.
         *
         * Ensures that the struct cannot be copied, maintaining its monostate design.
         */
        OriginalReflection(const OriginalReflection&) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent assignment.
         *
         * Ensures that the struct cannot be assigned, maintaining its monostate design.
         */
        OriginalReflection& operator=(const OriginalReflection&) = delete;

        /**
         * @brief Retrieves the reflection data for the "Original" class.
         *
         * This method uses the reflection system to dynamically register and retrieve
         * metadata for the "Original" class, including its constructor, instance methods,
         * and static methods. The reflection data is stored as a static optional object
         * to ensure it is initialized only once and reused across multiple calls.
         *
         * @return A constant reference to an optional containing the reflection data
         * for the "Original" class. If the reflection data is unavailable, the optional
         * will be empty.
         */
        static const std::optional<rtl::Record>& getClass();
    };
}

#pragma once

#include "RTLibInterface.h"

namespace proxy_test {

    /**
     * @brief The OriginalReflection class provides reflection capabilities for the "Original" class.
     *
     * This class inherits from rtl::access::CxxMirror and uses the singleton pattern to ensure
     * only one instance exists. It holds optional reflection data for the "Original" class.
     */
    class OriginalReflection : rtl::access::CxxMirror
    {
        std::optional<rtl::access::Record> reflectedClass;

        /**
         * @brief Private constructor to enforce singleton pattern.
         */
        OriginalReflection();

    public:

        // Delete copy constructor and assignment operator to enforce singleton pattern
        OriginalReflection(const OriginalReflection&) = delete;
        OriginalReflection& operator=(const OriginalReflection&) = delete;

        /**
         * @brief Get the reflection data for the "Original" class.
         *
         * @return const std::optional<rtl::access::Record>& Reference to the optional reflection data.
         */
        const std::optional<rtl::access::Record>& rclass() const {
            return reflectedClass;
        }

        /**
         * @brief Get the singleton instance of OriginalReflection.
         *
         * @return OriginalReflection& Reference to the singleton instance.
         */
        static OriginalReflection& obj() {
            static OriginalReflection instance;
            return instance;
        }
    };
}

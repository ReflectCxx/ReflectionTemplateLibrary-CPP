#pragma once

#include "RTLibInterface.h"

namespace proxy_test {

    class OriginalReflection : rtl::access::CxxMirror
    {
        std::optional<rtl::access::Record> m_originalClass;

        OriginalReflection();

    public:
        
        OriginalReflection(const OriginalReflection&) = delete;
        OriginalReflection& operator=(const OriginalReflection&) = delete;

		const std::optional<rtl::access::Record>& classRef() const {
			return m_originalClass;
		}

        static OriginalReflection& obj() {
            static OriginalReflection instance;
            return instance;
        }
    };
}
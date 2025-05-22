#pragma once

#include <any>
#include <vector>
#include <functional>
#include "Constants.h"

namespace rtl::detail
{
    using Converter = std::function< std::any(const std::any&) >;

    template<class _fromType>
    class RObjectConverter
    {
        static std::vector<std::pair<std::size_t, Converter>>& conversions();

        template<class _toType>
        static void pushConversion();

        static bool pushKnownConversions();

    public:

        static const std::vector<std::pair<std::size_t, Converter>>& getConversions() {
            return conversions();
        }
	};
}
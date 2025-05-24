#pragma once

#include <any>
#include <vector>
#include <functional>
#include "Constants.h"

namespace rtl::access {
    class CxxMirror;
}

namespace rtl::detail
{
    using Converter = std::function< std::any(const std::any&) >;

    template<class _fromType>
    class RObjectConverter
    {
        static std::vector<std::pair<std::size_t, Converter>>& conversions();

        template<class _toType> static void pushConversion();

    public:

        static const std::vector<std::pair<std::size_t, Converter>>& getConversions();

        friend rtl::access::CxxMirror;
	};

    template<>
    template<>
    void RObjectConverter<std::string>::pushConversion<const char*>();
}
#pragma once

#include <any>
#include <vector>
#include <functional>

#include "Constants.h"

namespace rtl::detail
{
    class RObjectConverterInit;

    using Converter = std::function< std::any(const std::any&) >;

    template<class _fromType>
    class RObjectConverter
    {

    public:

        template<class _toType> static void pushConversion();

        static std::vector<std::pair<std::size_t, Converter>>& conversions();

        static const std::vector<std::pair<std::size_t, Converter>>& getConversions();

        friend RObjectConverterInit;
    };
}


namespace rtl::detail
{
    template<>
    template<>
    void RObjectConverter<std::string>::pushConversion<const char*>();
}
#pragma once

#include <any>
#include <vector>
#include <functional>

namespace rtl::detail
{
    using Converter = std::function< std::any(const std::any&) >;

    template<class _fromType>
    class RObjectConverter
    {
        static std::vector<std::pair<std::size_t, Converter>> m_converters;

    public:

        template<class _toType>
        static void pushConversion();
     
        static bool addKnownConversions();

        static const std::vector<std::pair<std::size_t, Converter>>& getConversions();
	};
}
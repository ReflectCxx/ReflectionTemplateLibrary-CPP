#pragma once

#include <any>
#include <vector>
#include <functional>

#include "rtl_traits.h"

namespace rtl::access {
    class CxxMirror;
}

namespace rtl::detail
{
    class ReflectedConversions
    {
        static void init();
        friend rtl::access::CxxMirror;
    };


    template<class _fromType>
    class ReflectCast
    {
        static std::vector<std::pair<std::size_t, traits::Converter>>& conversions() {
            static std::vector<std::pair<std::size_t, traits::Converter>> converters;
            return converters;
        }

    public:

        template<class _toType> static void pushConversion();

        static const std::vector<std::pair<std::size_t, traits::Converter>>& getConversions() {
            return conversions();
        }
    };
}
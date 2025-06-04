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
    class ReflectedConversions
    {
        static void init();
        friend rtl::access::CxxMirror;
    };


    template<class _fromType>
    class ReflectCast
    {
        static std::vector<std::pair<std::size_t, Converter>>& conversions();

    public:

        template<class _toType> static void pushConversion();

        static const std::vector<std::pair<std::size_t, Converter>>& getConversions();
    };
}
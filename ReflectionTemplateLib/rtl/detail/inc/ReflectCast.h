/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include <any>
#include <vector>
#include <functional>

#include "rtl_traits.h"
#include "forward_decls.h"

namespace rtl::detail
{
    class ReflectedConversions
    {
        static void init();

        friend rtl::CxxMirror;
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
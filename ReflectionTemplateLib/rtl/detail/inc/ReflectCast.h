/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <rtl_traits.h>

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
        ForceInline static std::vector<std::pair<std::size_t, traits::Converter>>& conversions() {
            static std::vector<std::pair<std::size_t, traits::Converter>> converters;
            return converters;
        }

    public:

        template<class _toType> static void pushConversion();

        ForceInline static const std::vector<std::pair<std::size_t, traits::Converter>>& getConversions() {
            return conversions();
        }
    };
}
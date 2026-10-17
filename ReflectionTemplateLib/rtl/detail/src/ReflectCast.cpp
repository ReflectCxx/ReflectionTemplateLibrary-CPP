/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <detail/inc/ReflectCast.hpp>
#include <detail/inc/ReflectCastUtil.h>

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<char>();

    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<char>();

    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>();
}


namespace rtl::detail
{
    void ReflectedConversions::init()
    {
        static const bool _= []()
        { 
            ReflectCast<std::string>::pushConversion<char>();
            ReflectCast<std::string_view>::pushConversion<char>();

            ReflectCast<std::string>::pushConversion<std::string_view>();
            ReflectCast<std::string_view>::pushConversion<std::string>();

            using _safePODTypes = std::tuple
            <bool, char, signed char, unsigned char, short, unsigned short, int>;

            auto conversions = make_conversion_pairs<_safePODTypes>();
            register_all_conversions<decltype(conversions)>();

            return true;
        }();
    }
}
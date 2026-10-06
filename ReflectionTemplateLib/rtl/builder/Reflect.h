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

#include <builder/RecordBuilder.h>

namespace rtl
{
/*  @class: Reflect
    * provides interface to register all kinds of functions (member/non-member).
*/  struct type
    {
        type() = default;
        type(type&&) = delete;
        type(const type&) = delete;
        type& operator=(type&&) = delete;
        type& operator=(const type&) = delete;

        template<class record_t>
        constexpr const builder::MethodBuilder<record_t> member() 
        {
            return builder::MethodBuilder<record_t>();
        }

        template<class record_t>
        constexpr const builder::RecordBuilder<record_t> record(std::string_view pClass)
        {
            return builder::RecordBuilder<record_t>(std::string(pClass), traits::uid<record_t>::value);
        }

        template<class ...signature_t>
        constexpr const builder::Builder<detail::member::None, signature_t...> function(std::string_view pFunction)
        {
            constexpr bool hasConstRValueRef = ((std::is_const_v<std::remove_reference_t<signature_t>> && std::is_rvalue_reference_v<signature_t>) || ...);
            static_assert(!hasConstRValueRef, "Registration of functions with 'const T&&' parameters is not allowed.");

            return builder::Builder<detail::member::None, signature_t...>(traits::uid<>::none, std::string(pFunction));
        }
    };
}
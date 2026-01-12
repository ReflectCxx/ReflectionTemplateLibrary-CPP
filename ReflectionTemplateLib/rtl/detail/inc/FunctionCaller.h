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

#include "type_meta.h"

namespace rtl::detail
{
    template<member member_kind, class ..._signature>
    struct InitFunctionHop
    {
        const std::size_t m_fnIndex;
        const std::vector<rtl::type_meta> m_overloadsMeta = {};

        void init(function<rtl::Return(_signature...)>& pFn) const;

        template<class _returnType = rtl::Return> requires (member_kind == member::None && std::is_same_v<_returnType, rtl::Return>)
        constexpr function<rtl::Return(_signature...)> returnT() const;

        template<class _returnType = rtl::Return> requires (member_kind == member::None && !std::is_same_v<_returnType, rtl::Return>)
        constexpr const function<_returnType(_signature...)> returnT() const;

        template<class _returnType = rtl::Return> requires (member_kind == member::Static && std::is_same_v<_returnType, rtl::Return>)
        constexpr const static_method<rtl::Return(_signature...)> returnT() const;

        template<class _returnType = rtl::Return> requires (member_kind == member::Static && !std::is_same_v<_returnType, rtl::Return>)
        constexpr const static_method<_returnType(_signature...)> returnT() const;
    };


    template<detail::member member_kind>
    struct HopBuilder<member_kind>
    {
        const std::vector<rtl::type_meta>& m_functorsMeta;

        template<class ..._signature>
        constexpr const InitFunctionHop<member_kind, _signature...> argsT() const;
    };
}
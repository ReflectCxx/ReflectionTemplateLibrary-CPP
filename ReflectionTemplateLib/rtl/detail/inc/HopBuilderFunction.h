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

#include <inc/type_meta.h>

namespace rtl::detail
{
    template<member member_kind, class ...signature_t>
    struct InitFunctionHop
    {
        const std::size_t m_fnIndex;
        const std::vector<rtl::type_meta> m_overloadsMeta = {};

        void init(function<rtl::Return(signature_t...)>& pFn) const;

        template<class return_t = rtl::Return> requires (member_kind == member::None && std::is_same_v<return_t, rtl::Return>)
        constexpr function<rtl::Return(signature_t...)> returnT() const;

        template<class return_t = rtl::Return> requires (member_kind == member::None && !std::is_same_v<return_t, rtl::Return>)
        constexpr const function<return_t(signature_t...)> returnT() const;

        template<class return_t = rtl::Return> requires (member_kind == member::Static && std::is_same_v<return_t, rtl::Return>)
        constexpr const static_method<rtl::Return(signature_t...)> returnT() const;

        template<class return_t = rtl::Return> requires (member_kind == member::Static && !std::is_same_v<return_t, rtl::Return>)
        constexpr const static_method<return_t(signature_t...)> returnT() const;
    };


    template<detail::member member_kind>
    struct HopBuilder<member_kind>
    {
        const std::vector<rtl::type_meta>& m_functorsMeta;

        template<class ...signature_t>
        constexpr const InitFunctionHop<member_kind, signature_t...> argsT() const;
    };
}
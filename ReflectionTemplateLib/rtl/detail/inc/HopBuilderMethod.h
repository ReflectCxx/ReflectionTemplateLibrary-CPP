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
    template<member member_kind, class record_t, class ...signature_t>
    struct InitMethodHop
    {
        const Method& m_method;
        const std::vector<rtl::type_meta> m_overloadsMeta;

        template<class return_t>
        static void init(const traits::uid_t pRecordId,
                         const std::vector<rtl::type_meta>& pRefOverloads,
                         typename method<record_t, return_t(signature_t...)>::hopper_t& pMth);

        template<class return_t>
        using method_t = std::conditional_t< member_kind == member::Const,
                                             const_method<record_t, return_t(signature_t...)>,
                                             method<record_t, return_t(signature_t...)> >;

        template<class return_t> requires (traits::type_aware_v<record_t, return_t>)
        constexpr method_t<return_t> returnT() const;

        template<class return_t = rtl::Return> requires (!traits::type_aware_v<record_t, return_t>)
        constexpr method<record_t, return_t(signature_t...)> returnT() const;
    };
}


namespace rtl::detail
{
    template<member member_kind, class record_t>
    struct HopBuilder
    {
        const Method& m_method;

        static std::vector<type_meta> getRefAndValueOverloads(const Method& pMethod,
                                                              const traits::uid_t pNormalId);

        template<class ...signature_t> requires (member_kind != member::None)
        constexpr InitMethodHop<member_kind, record_t, signature_t...> argsT() const;
    };
}
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
#include "rtl_forward_decls.h"

namespace rtl::detail
{		
    template<bool is_binding_v, class ..._signature>
    struct ErasedCaller
    {
        const Function& m_function;

        template<class ..._args>
        rtl::Return call(_args&&...) const noexcept;

        template<class ..._args> requires (is_binding_v == false)
        constexpr rtl::Return operator()(_args&&...params) const noexcept
        {
            return { error::InvalidCaller, RObject{} };
        }

        template<class ..._args> requires (is_binding_v == true)
        constexpr rtl::Return operator()(_args&&...params) const noexcept
        {
            return { error::SignatureMismatch, RObject{} };
        }
    };
}


namespace rtl::detail
{
    template<member member_kind, class ..._signature>
    struct HopFunction
    {
        std::size_t m_fnIndex;

        std::vector<rtl::type_meta> m_overloadsFnMeta = {};

        void initHopper(function<rtl::Return(_signature...)>& pFn) const;

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
    struct Hopper<member_kind>
    {
        const std::vector<rtl::type_meta>& m_functorsMeta;

        template<class ..._signature>
        constexpr const HopFunction<member_kind, _signature...> argsT() const;
    };
}
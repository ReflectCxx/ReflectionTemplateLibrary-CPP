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

#include "RObject.h"
#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

#include "erasure_base.h"
#include "rtl_function_erased_return.h"

namespace rtl::detail
{
    template<bool is_binding_v, class ..._signature>
    template<class ..._args>
    ForceInline Return ErasedCaller<is_binding_v, _signature...>::call(_args&&...params) const noexcept
    {
        using Container = std::conditional_t<sizeof...(_signature) == 0,
            FunctorContainer<std::remove_reference_t<_args>...>,
            FunctorContainer<_signature...>>;

        const detail::FunctorId* functorId = m_function.hasFunctorId(Container::getContainerId());
        if (functorId != nullptr) [[likely]] {
            return Container::template forwardCall<_args...>(*functorId, std::forward<_args>(params)...);
        }
        return { error::SignatureMismatch, RObject{} };
    }
}


namespace rtl::detail
{
    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::None && std::is_same_v<return_t, rtl::Return>)
    inline constexpr function<Return(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        function<Return(traits::normal_sign_t<args_t>...)> erasedFn;
        initHopper(erasedFn);
        return erasedFn;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<Return(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        static_method<Return(traits::normal_sign_t<args_t>...)> erasedFn;
        initHopper(erasedFn);
        return erasedFn;
    }

    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<return_t(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        static_method<return_t(args_t...)> fn;
        if (!m_argsTfnMeta.is_empty()) 
        {
            if (m_argsTfnMeta.get_member_kind() != member::Static) {
                fn.set_init_error(error::InvalidNonStaticMethodCaller);
            }
            else if (m_argsTfnMeta.get_member_kind() == member::Static) {
                
                const auto retId = traits::uid<return_t>::value;
                return m_argsTfnMeta.get_lambda()
                                    .template to_function<args_t...>()
                                    .template get_hopper<return_t>(retId)
                                    .f_ptr();
            }
        }
        return fn;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::None && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const function<return_t(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        function<return_t(args_t...)> fn;
        if (!m_argsTfnMeta.is_empty()) 
        {
            if (m_argsTfnMeta.get_member_kind() == member::Static) {
                fn.set_init_error(error::InvalidStaticMethodCaller);
            }
            else if (m_argsTfnMeta.get_member_kind() == member::None) {

                const auto retId = traits::uid<return_t>::value;
                return m_argsTfnMeta.get_lambda()
                                    .template to_function<args_t...>()
                                    .template get_hopper<return_t>(retId);
            }
        }
        return fn;
    }


    template<member member_kind, class ...args_t>
    inline void HopFunction<member_kind, args_t...>::initHopper(function<rtl::Return(args_t...)>& pHopFn) const
    {
        bool isReturnTvoid = false;
        for (auto& fnMeta : m_overloadsFnMeta)
        {
            if (fnMeta.is_empty())
            {
                pHopFn.get_vhop().push_back(nullptr);
                pHopFn.get_rhop().push_back(nullptr);
                pHopFn.get_overloads().push_back(nullptr);
                continue;
            }

            if (fnMeta.get_member_kind() != member::None && fnMeta.get_member_kind() != member::Static) {
                pHopFn.set_init_error(error::InvalidNonStaticMethodCaller);
                return;
            }

            auto& erasedRetFn = fnMeta.get_erasure_base()
                                      .template to_erased_return<traits::normal_sign_t<args_t>...>();
            if (fnMeta.is_void()) {
                isReturnTvoid = true;
                pHopFn.get_vhop().push_back(erasedRetFn.get_void_hopper());
            }
            else {
                pHopFn.get_rhop().push_back(erasedRetFn.get_return_hopper());
            }
            pHopFn.get_overloads().push_back(&fnMeta.get_lambda());
            pHopFn.set_init_error(error::None);
        }
        if (isReturnTvoid) {
            pHopFn.get_rhop().clear();
        }
        else {
            pHopFn.get_vhop().clear();
        }
    }


    template<detail::member member_kind>
    template<class ...args_t>
    inline constexpr const HopFunction<member_kind, args_t...> Hopper<member_kind>::argsT() const
    {
        auto strictArgsId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        auto normalArgsId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;

        rtl::type_meta argsTfnMeta;
        //initializing pos '0' with empty 'type_meta'.
        std::vector<rtl::type_meta> overloadsFnMeta = { rtl::type_meta() };

        for (auto& fnMeta : m_functorsMeta)
        {
            if (argsTfnMeta.is_empty() && strictArgsId == fnMeta.get_strict_args_id()) {
                argsTfnMeta = fnMeta;
            }
            if (normalArgsId == fnMeta.get_normal_args_id())
            {
                if (normalArgsId == fnMeta.get_strict_args_id()) {
                    // same normal & strict ids, means no refs exists in target function's signature
                    // target's function signature is call by value, always at pos '0'.
                    // if doesn't exists, this pos is occupied by an empty 'type_meta'.
                    overloadsFnMeta[0] = fnMeta;
                }
                else if (!fnMeta.is_any_arg_ncref()) {
                    // its a const-ref-overload with no non-const-ref in signature, added from pos '1' onwards.
                    overloadsFnMeta.push_back(fnMeta);
                }
            }
        }

        for (auto& fnMeta : m_functorsMeta) {
            if (normalArgsId == fnMeta.get_normal_args_id() && fnMeta.is_any_arg_ncref()) {
                // any remaining overload, const/non-const ref added from pos '1' onwards.
                overloadsFnMeta.push_back(fnMeta);
            }
        }
        return { argsTfnMeta, overloadsFnMeta };
    }
}
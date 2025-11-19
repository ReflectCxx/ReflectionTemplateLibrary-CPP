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

#include "functor_cast.h"
#include "function_ptr.h"
#include "rtl_function.h"
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
        function<Return(traits::normal_sign_t<args_t>...)> fn;
        initHopper(fn);
        return fn;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<Return(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        static_method<Return(traits::normal_sign_t<args_t>...)> mth;
        initHopper(mth);
        return mth;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<return_t(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        static_method<return_t(args_t...)> mth;
        if (!m_argsTfnMeta.is_empty()) 
        {
            if (m_argsTfnMeta.get_member_kind() != member::Static) {
                mth.set_init_error(error::InvalidNonStaticMethodCaller);
            }
            else if (m_argsTfnMeta.get_member_kind() == member::Static &&
                     traits::uid<return_t>::value == m_argsTfnMeta.get_return_id()) 
            {                
                using function_t = dispatch::function_ptr<return_t, args_t...>;
                auto fptr = static_cast<const function_t&>(m_argsTfnMeta.get_functor()).f_ptr();
                return static_method<return_t(args_t...)>(fptr);
            }
        }
        return mth;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::None && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const function<return_t(args_t...)> HopFunction<member_kind, args_t...>::returnT() const
    {
        function<return_t(args_t...)> fn;
        if (!m_argsTfnMeta.is_empty()) 
        {
            if (m_argsTfnMeta.get_member_kind() == member::Static) 
            {
                fn.set_init_error(error::InvalidStaticMethodCaller);
            }
            else if (m_argsTfnMeta.get_member_kind() == member::None && 
                     traits::uid<return_t>::value == m_argsTfnMeta.get_return_id()) 
            {
                using function_t = dispatch::function_ptr<return_t, args_t...>;
                auto fptr = static_cast<const function_t&>(m_argsTfnMeta.get_functor()).f_ptr();
                return function<return_t(args_t...)>(fptr);
            }
        }
        return fn;
    }


    template<member member_kind, class ...args_t>
    inline void HopFunction<member_kind, args_t...>::initHopper(function<rtl::Return(args_t...)>& pHopper) const
    {
        bool isReturnTvoid = false;
        for (auto& ty_meta : m_overloadsFnMeta)
        {
            if (ty_meta.is_empty()) {
                pHopper.get_vhop().push_back(nullptr);
                pHopper.get_rhop().push_back(nullptr);
                pHopper.get_overloads().push_back(nullptr);
                continue;
            }

            if constexpr (member_kind == member::Static) {
                if (ty_meta.get_member_kind() != member::Static) {
                    pHopper.set_init_error(error::InvalidNonStaticMethodCaller);
                    return;
                }
            }
            else if constexpr (member_kind == member::None) {
                if (ty_meta.get_member_kind() == member::Static) {
                    pHopper.set_init_error(error::InvalidStaticMethodCaller);
                    return;
                }
            }

            if (isReturnTvoid = ty_meta.is_void()) 
            {
                using fn_cast = dispatch::functor_cast<dispatch::fn_void::yes, traits::normal_sign_t<args_t>...>;
                auto fn = fn_cast(ty_meta.get_functor()).template to_function<dispatch::erase::t_return>();
                pHopper.get_vhop().push_back(fn.f_ptr());
            }
            else 
            {
                using fn_cast = dispatch::functor_cast<dispatch::fn_void::no, traits::normal_sign_t<args_t>...>;
                auto fn = fn_cast(ty_meta.get_functor()).template to_function<dispatch::erase::t_return>();
                pHopper.get_rhop().push_back(fn.get_hop());
            }

            pHopper.get_overloads().push_back(&ty_meta.get_functor());
            pHopper.set_init_error(error::None);
        }
        if (isReturnTvoid) {
            pHopper.get_rhop().clear();
        }
        else {
            pHopper.get_vhop().clear();
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

        for (auto& ty_meta : m_functorsMeta)
        {
            if (argsTfnMeta.is_empty() && strictArgsId == ty_meta.get_strict_args_id()) {
                argsTfnMeta = ty_meta;
            }
            if (normalArgsId == ty_meta.get_normal_args_id())
            {
                if (normalArgsId == ty_meta.get_strict_args_id()) {
                    // same normal & strict ids, means no refs exists in target function's signature
                    // target's function signature is call by value, always at pos '0'.
                    // if doesn't exists, this pos is occupied by an empty 'type_meta'.
                    overloadsFnMeta[0] = ty_meta;
                }
                else if (!ty_meta.is_any_arg_ncref()) {
                    // its a const-ref-overload with no non-const-ref in signature, added from pos '1' onwards.
                    overloadsFnMeta.push_back(ty_meta);
                }
            }
        }

        for (auto& ty_meta : m_functorsMeta) {
            if (normalArgsId == ty_meta.get_normal_args_id() && ty_meta.is_any_arg_ncref()) {
                // any remaining overload, const/non-const ref added from pos '1' onwards.
                overloadsFnMeta.push_back(ty_meta);
            }
        }
        return { argsTfnMeta, overloadsFnMeta };
    }
}
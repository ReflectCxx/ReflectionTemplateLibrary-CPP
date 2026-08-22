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

#include <inc/RObject.h>
#include <inc/Function.h>
#include <rtl_function.h>
#include <rtl_function_erased_return.h>
#include <dispatch/functor_cast.h>
#include <dispatch/function_ptr.h>
#include <detail/inc/HopBuilderFunction.h>

namespace rtl::detail
{
    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::None && std::is_same_v<return_t, rtl::Return>)
    inline constexpr function<Return(args_t...)> InitFunctionHop<member_kind, args_t...>::returnT() const
    {
        function<Return(traits::normal_sign_t<args_t>...)> fn;
        init(fn);
        return fn;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<Return(args_t...)> InitFunctionHop<member_kind, args_t...>::returnT() const
    {
        static_method<Return(traits::normal_sign_t<args_t>...)> mth;
        init(mth);
        return mth;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::Static && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const static_method<return_t(args_t...)> InitFunctionHop<member_kind, args_t...>::returnT() const
    {
        static_method<return_t(args_t...)> mth;
        if (m_fnIndex == rtl::index_none) {
            mth.set_init_error(error::SignatureMismatch);
            return mth;
        }

        auto& ty_meta = m_overloadsMeta[m_fnIndex];
        if (ty_meta.get_member_kind() != member::Static) {
            mth.set_init_error(error::InvalidNonStaticMethodCaller);
        }
        else if (ty_meta.get_member_kind() == member::Static){
            if (traits::uid<return_t>::value == ty_meta.get_return_id())
            {
                using function_t = dispatch::function_ptr<return_t, args_t...>;
                auto fptr = static_cast<const function_t&>(ty_meta.get_functor()).f_ptr();
                return static_method<return_t(args_t...)>(fptr);
            }
            mth.set_init_error(error::ReturnTypeMismatch);
        }
        return mth;
    }


    template<member member_kind, class ...args_t>
    template<class return_t> requires (member_kind == member::None && !std::is_same_v<return_t, rtl::Return>)
    inline constexpr const function<return_t(args_t...)> InitFunctionHop<member_kind, args_t...>::returnT() const
    {
        function<return_t(args_t...)> fn;
        if (m_fnIndex == rtl::index_none) {
            fn.set_init_error(error::SignatureMismatch);
            return fn;
        }
        
        auto& ty_meta = m_overloadsMeta[m_fnIndex];
        if (ty_meta.get_member_kind() == member::Static) {
            fn.set_init_error(error::InvalidStaticMethodCaller);
        }
        else if (ty_meta.get_member_kind() == member::None) {
            if (traits::uid<return_t>::value == ty_meta.get_return_id())
            {
                using function_t = dispatch::function_ptr<return_t, args_t...>;
                auto fptr = static_cast<const function_t&>(ty_meta.get_functor()).f_ptr();
                return function<return_t(args_t...)>(fptr);
            }
            fn.set_init_error(error::ReturnTypeMismatch);
        }
        return fn;
    }


    template<detail::member member_kind>
    template<class ...args_t>
    inline constexpr const InitFunctionHop<member_kind, args_t...> HopBuilder<member_kind>::argsT() const
    {
        std::size_t index = rtl::index_none;
        std::vector<rtl::type_meta> fnTyMetas(call_by::ncref);
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        auto strictId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        
        for (auto& ty_meta : m_functorsMeta)
        {
            if (normalId == ty_meta.get_normal_args_id())
            {
                if (normalId == ty_meta.get_strict_args_id()) {
                    fnTyMetas[call_by::value] = ty_meta;
                }
                else if (!ty_meta.is_any_arg_ncref()) {
                    fnTyMetas[call_by::cref] = ty_meta;
                }
                else fnTyMetas.push_back(ty_meta);
            }
        }
        for (int i = 0; i < fnTyMetas.size(); i++)
        {
            auto& ty_meta = fnTyMetas[i];
            if (!ty_meta.is_empty() && ty_meta.get_strict_args_id() == strictId) {
                index = i;
                break;
            }
        }
        return { index, fnTyMetas };
    }


    template<member member_kind, class ...args_t>
    inline void InitFunctionHop<member_kind, args_t...>::init(function<rtl::Return(args_t...)>& pHopper) const
    {
        for (auto& ty_meta : m_overloadsMeta)
        {
            if (ty_meta.is_empty()) {
                pHopper.get_hopper().push_back(nullptr);
                pHopper.get_overloads().push_back(nullptr);
                continue;
            }
            //TODO: simplifiy these errors. confusing!
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

            using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
            auto fn = fn_cast(ty_meta.get_functor()).template to_function<dispatch::erase::t_return>();

            pHopper.get_hopper().push_back(fn.f_ptr());
            pHopper.get_overloads().push_back(&ty_meta.get_functor());
            pHopper.set_init_error(error::None);
        }

        if (pHopper.get_init_error() != error::None) {
            pHopper.set_init_error(error::SignatureMismatch);
        }
    }
}
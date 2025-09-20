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

#include "rtl_typeid.h"
#include "lambda_hop_function.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    inline lambda_hop_function<signature_ts...>::lambda_hop_function(const functor* functor) noexcept
    {
        m_functor = functor;
        m_signatureId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
        detail::TypeId<signature_ts...>::get(m_argumentsId);
    }


    template<class ...signature_ts>
    template<class ret_t, class ...args_t>
    inline decltype(auto) lambda_hop_function<signature_ts...>::dispatch(args_t&& ...params) const noexcept
    {
        constexpr bool signature_ok = std::is_same_v< std::tuple<traits::raw_t<args_t>...>,
                                                      std::tuple<signature_ts...>>;

        static_assert( signature_ok, "Argument types don't match signature.");

        auto* functor = return_type<traits::raw_t<ret_t>>().template signature<traits::raw_t<args_t>...>().f_ptr();

        if constexpr (std::is_same_v<ret_t, void>) {
            (*functor)(std::forward<args_t>(params)...);
        }
        else {
            return (*functor)(std::forward<args_t>(params)...);
        }
    }
}
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

#include "lambda_hop_function.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    template<class return_t>
    inline lambda_hop_function<signature_ts...> lambda_hop_function<signature_ts...>::create(const functor* fptr_hopper)
    {
        return lambda_hop_function(detail::TypeId<return_t>::get(), fptr_hopper, nullptr);
    }

    template<class ...signature_ts> //TODO: static-assert signature_ts == args_t.
    inline decltype(auto) lambda_hop_function<signature_ts...>::operator()(signature_ts&& ...params) const noexcept
    {
        return m_hopper(*this, params...);
    }

    template<class ...signature_ts>
    template<class return_t, class ...args_t>   //TODO: static-assert signature_ts == args_t.
    inline decltype(auto) lambda_hop_function<signature_ts...>::dispatch(args_t&& ...params) const noexcept
    {
        if constexpr (std::is_same_v<return_t, void>) {
            hopper::dispatch<return_t>(*this, std::forward<args_t>(params)...);
        }
        else {
            return hopper::dispatch<return_t>(*this, std::forward<args_t>(params)...);
        }
    }
}
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
                      //&hopper<signature_ts...>::template dispatch<std::is_same_v<return_t, void>, return_t>);
    }

    template<class ...signature_ts>
    inline decltype(auto) lambda_hop_function<signature_ts...>::operator()(const signature_ts& ...params) const noexcept
    {
        //TODO: static-assert signature_ts == args_t.
        return m_hopper(*this, params...);
    }

    template<class ...signature_ts>
    template<class return_t>
    inline decltype(auto) lambda_hop_function<signature_ts...>::dispatch(const signature_ts&...params) const noexcept
    {
        //TODO: static-assert signature_ts == args_t.
        if constexpr (std::is_same_v<return_t, void>) {
            hopper<signature_ts...>::template dispatch<return_t>(*this, params...);
        }
        else {
            return hopper<signature_ts...>::template dispatch<return_t>(*this, params...);
        }
    }
}
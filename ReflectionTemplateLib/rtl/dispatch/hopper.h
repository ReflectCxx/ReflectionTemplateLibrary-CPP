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

#include <cassert>

#include "lambda_hop_function.h"
#include "function_ptr.h"

namespace rtl::dispatch
{
    struct hopper
    {
        template<class ret_t, class ...params_t> //requires (std::is_same_v<return_t, ret_t> == false)
        static decltype(auto) dispatch(const lambda_hop& lambda_ref, params_t&&...params) noexcept
        {
            auto functor = lambda_ref.get_functor().template args_t<traits::raw_t<params_t>...>()
                                                   .template return_t<traits::raw_t<ret_t>>();

            if constexpr (std::is_same_v<ret_t, void>) {
                (*functor)(std::forward<params_t>(params)...);
            }
            else {
                return (*functor)(std::forward<params_t>(params)...);
            }
        }


        // template<bool void_t, class return_t> requires (void_t == true)
        // static Return dispatch(const lambda_hop& lambda_ref, const signature_ts&...params) noexcept
        // {
        //     if constexpr (std::is_same_v<return_t, void>) 
        //     {
        //         auto functor = lambda_ref.functor().template get<signature_ts...>()
        //                                            .template get<return_t>(lambda_ref.m_returnId);

        //         (*functor)(params...);
        //     }
        //     else 
        //     {
        //         static_assert("return-type mismatch.");
        //     }
        //     return { error::None, RObject{} };
        // }


        // template<bool void_t, class return_t> requires (void_t == false)
        // static Return dispatch(const lambda_hop& lambda_ref, const signature_ts&...params) noexcept
        // {
        //     constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

        //     auto functor = lambda_ref.functor().template get<signature_ts...>()
        //                                        .template get<return_t>(lambda_ref.m_returnId);

        //     if constexpr (std::is_reference_v<return_t>)
        //     {
        //         using T = traits::raw_t<return_t>;
        //         const T& retObj = (*functor)(params...);
        //         return { error::None, RObject{} };
        //     }
        //     else {

        //         auto&& retObj = (*functor)(params...);
        //         using T = std::remove_cvref_t<decltype(retObj)>;
        //         return { error::None, RObject{} };
        //     }
        // }
    };
}
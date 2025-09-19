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

#include "forward_decls.h"

#include "lambda_function.h"
#include "functor.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct hopper_nonconst
    {
        template<class record_t, class return_t> requires (std::is_same_v<return_t, Return> == false)
        static decltype(auto) dispatch(record_t& target, const lambda_hop& lambda_ref, const signature_ts&...params) noexcept
        {
            auto functor = lambda_ref.functor().template get_nonconst<record_t, signature_ts...>()
                                               .template get<return_t>(lambda_ref.m_returnId);

            if constexpr (std::is_same_v<return_t, void>) {
                (target.*functor)(params...);
            }
            else {
                return (target.*functor)(params...);
            }
        }


        template<bool void_t, class record_t, class return_t> requires (void_t == true)
        static Return dispatch(record_t& target, const lambda_hop& lambda_ref, const signature_ts&...params) noexcept
        {
            if constexpr (std::is_same_v<return_t, void>)
            {
                auto functor = lambda_ref.functor().template get_nonconst<record_t, signature_ts...>()
                                                   .template get<return_t>(lambda_ref.m_returnId);

                (target.*functor)(params...);
            }
            else
            {
                static_assert("return-type mismatch.");
            }
            return { error::None, RObject{} };
        }


        template<bool void_t, class record_t, class return_t> requires (void_t == false)
        static Return dispatch(record_t& target, const lambda_hop& lambda_ref, const signature_ts&...params) noexcept
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

            auto functor = lambda_ref.functor().template get_nonconst<record_t, signature_ts...>()
                                               .template get<return_t>(lambda_ref.m_returnId);

            if constexpr (std::is_reference_v<return_t>)
            {
                using T = traits::raw_t<return_t>;
                const T& retObj = (target.*functor)(params...);
                return { error::None, RObject{} };
            }
            else {

                auto&& retObj = (target.*functor)(params...);
                using T = std::remove_cvref_t<decltype(retObj)>;
                return { error::None, RObject{} };
            }
        }
    };
}
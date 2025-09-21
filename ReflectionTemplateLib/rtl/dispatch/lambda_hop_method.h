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

#include "lambda_hop.h"
#include "method_ptr.h"
#include <utility>

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct lambda_hop_method : public lambda_hop
    {
        template<class return_t>
        using fptr_t = typename method_ptr<record_t, return_t, signature_ts...>::functor_t;

        lambda_hop_method(const functor* functor) noexcept
        {
            m_functor = functor;
            m_signatureId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

        template<class return_t>
        constexpr const method_ptr<record_t, return_t, signature_ts...>& get_functor() const
        {
            // Unchecked: using an incorrect argument or return type is undefined behaviour.
            // No validation is performed and the function will not return nullptr on mismatch. (By Design)
            return *(static_cast<const method_ptr<record_t, return_t, signature_ts...>*>(m_functor));
        }

        template<class return_t, class...args_t>
        constexpr decltype(auto) dispatch(record_t& target, args_t&& ...params) const
                                        noexcept(noexcept(
                                            (std::declval<record_t&>().*std::declval<fptr_t<return_t>>())(std::declval<args_t>()...)
                                        ))
        {
            constexpr bool signature_ok = std::is_same_v<
                std::tuple<traits::raw_t<args_t>...>,
                std::tuple<signature_ts...>
            >;
            
            static_assert( signature_ok, "Argument types don't match signature.");

            fptr_t<return_t> functor = get_functor<return_t>().f_ptr();

            if constexpr (std::is_same_v<return_t, void>) {
                (target.*functor)(std::forward<args_t>(params)...);
            }
            else {
                return (target.*functor)(std::forward<args_t>(params)...);
            }
        }
    };
}
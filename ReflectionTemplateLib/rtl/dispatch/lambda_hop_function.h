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
#include "function_ptr.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_hop_function: public lambda_hop
    {
        lambda_hop_function(const functor* fptr) noexcept
        {
            m_functor = fptr;
            m_signatureId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

        template<class return_t>
        constexpr const function_ptr<return_t, signature_ts...>& get_functor() const
        {
            // Unchecked: using an incorrect argument or return type is undefined behaviour.
            // No validation is performed and the function will not return nullptr on mismatch. (By Design)
            return *(static_cast<const function_ptr<return_t, signature_ts...>*>(m_functor));
        }

        template<class return_t, class...args_t>
        constexpr decltype(auto) dispatch(args_t&&...params) const
                                        noexcept(noexcept(
                                            std::invoke(get_functor<return_t>().f_ptr(),std::declval<args_t>()...)
                                        ))
        {
            constexpr bool signature_ok = std::is_same_v<
                std::tuple<traits::raw_t<args_t>...>,
                std::tuple<signature_ts...>
            >;
            static_assert( signature_ok, "Argument types don't match signature.");

            using fptr_t = typename function_ptr<return_t, signature_ts...>::functor_t;

            fptr_t functor = get_functor<return_t>().f_ptr();

            if constexpr (std::is_same_v<return_t, void>) {
                (*functor)(std::forward<args_t>(params)...);
            }
            else {
                return (*functor)(std::forward<args_t>(params)...);
            }
        }
    };
}
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
    class lambda_function: public lambda
    {
        template<class return_t>
        using fptr_t = typename function_ptr<return_t, signature_ts...>::functor_t;

        template<class ...args_t>
        static constexpr bool is_argst_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

        template<class return_t>
        static constexpr bool noexcept_v = noexcept(std::declval<fptr_t<return_t>>()(std::declval<signature_ts>()...));

    public:

        lambda_function(const functor& fptr) noexcept
            :lambda(fptr)
        { }

        template<class return_t>
        constexpr const function_ptr<return_t, signature_ts...>& get_functor() const
        {
            // Unchecked: using an incorrect argument or return type is undefined behaviour.
            // No validation is performed and the function will not return nullptr on mismatch. (By Design)
            return static_cast<const function_ptr<return_t, signature_ts...>&>(m_functor);
        }

        template<class return_t, class...args_t>
        constexpr decltype(auto) hop(args_t&&...params) const  //noexcept(noexcept_v)
        {
            static_assert(is_argst_ok<args_t...>, "Argument types don't match signature.");

            fptr_t<return_t> functor = get_functor<return_t>().f_ptr();
            if constexpr (std::is_same_v<return_t, void>) {
                (*functor)(std::forward<args_t>(params)...);
            }
            else {
                return (*functor)(std::forward<args_t>(params)...);
            }
        }
    };
}
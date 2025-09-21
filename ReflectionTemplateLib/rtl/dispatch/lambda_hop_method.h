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

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    class lambda_method : public lambda
    {
        template<class return_t>
        using fptr_t = typename method_ptr<record_t, return_t, signature_ts...>::functor_t;

        template<class ...args_t>
        static constexpr bool is_argst_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

        template<class return_t>
        static constexpr bool noexcept_v = noexcept((std::declval<record_t>().*std::declval<fptr_t<return_t>>())(std::declval<signature_ts>()...));

    public:

        lambda_method(const functor& fptr) noexcept
            :lambda(fptr)
        { }

        // Unsafe: using an incorrect argument or return type is undefined behaviour.
        // Not validated here and the function will not return nullptr on mismatch. (By Design)
        template<class return_t>
        constexpr const method_ptr<record_t, return_t, signature_ts...>& get_functor() const
        {
            return static_cast<const method_ptr<record_t, return_t, signature_ts...>&>(m_functor);
        }

        template<class return_t, class...args_t>
        constexpr decltype(auto) hop(record_t& target, args_t&& ...params) const noexcept(noexcept_v<return_t>)
        {
            static_assert(is_argst_ok<args_t...>, "Argument types don't match signature.");

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
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

#include "lambda.h"
#include "function_ptr.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_function: public lambda
    {
        template<class return_t>
        using fptr_t = typename function_ptr<return_t, signature_ts...>::functor_t;

        lambda_function(const functor& fptr) noexcept
            :lambda(fptr)
        { }

        template<class return_t>
        struct hopper
        {
            constexpr auto f_ptr() const {
                return m_functor;
            }

            constexpr auto is_valid() const {
                return (m_functor != nullptr);
            }

            template<class ...args_t>
            [[nodiscard]] constexpr decltype(auto) operator()(args_t&&...params) const noexcept(noexcept_v<args_t...>)
            {
                static_assert(is_args_t_ok<args_t...>, "Argument types don't match the expected signature.");
                return (*m_functor)(std::forward<args_t>(params)...);
            }

            const fptr_t<return_t> m_functor = nullptr;

        private:

            template<class ...args_t>
            static constexpr bool is_args_t_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

            template<class ...args_t>
            static constexpr bool noexcept_v = noexcept(std::declval<fptr_t<return_t>>()(std::declval<args_t>()...));
        };

        template<class return_t>
        [[nodiscard]] constexpr const hopper<return_t> get_hopper() const
        {
            if (m_functor.m_returnId == detail::TypeId<return_t>::get())
            {
                fptr_t<return_t> func_ptr = (static_cast<const function_ptr<return_t, signature_ts...>&>(m_functor)).f_ptr();
                return hopper<return_t>{ func_ptr };
            }
            return hopper<return_t>();
        }
    };
}
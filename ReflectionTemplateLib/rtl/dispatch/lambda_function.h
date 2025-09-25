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

namespace  rtl 
{
    template<class return_t, class ...signature_ts>
    struct function<return_t(signature_ts...)>
    {
        using fptr_t = return_t(*)(signature_ts...);

        const fptr_t m_functor = nullptr;

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        template<class ...args_t>
        [[nodiscard]] constexpr decltype(auto) operator()(args_t&&...params) const noexcept(noexcept_v<args_t...>)
        {
            static_assert(is_args_t_ok<args_t...>, "Argument types don't match the expected signature.");
            return (*m_functor)(std::forward<args_t>(params)...);
        }

    private:

        template<class ...args_t>
        static constexpr bool is_args_t_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

        template<class ...args_t>
        static constexpr bool noexcept_v = noexcept(std::declval<return_t(*)(signature_ts...)>()(std::declval<args_t>()...));
    };
}

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_function: public lambda_base
    {
        template<class return_t>
        using hopper_t = function<return_t(signature_ts...)>;

        lambda_function(const functor& p_functor) noexcept
            :lambda_base(p_functor)
        { }

        template<class return_t>
        constexpr const hopper_t<return_t> get_hopper(const std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                return hopper_t<return_t> {
                    static_cast<const function_ptr<return_t, signature_ts...>&>(m_functor).f_ptr()
                };
            }
            return hopper_t<return_t>();
        }
    };
}
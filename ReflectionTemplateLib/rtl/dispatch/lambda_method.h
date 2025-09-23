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
#include "method_ptr.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct lambda_method : public lambda
    {
        template<class return_t>
        using fptr_t = typename method_ptr<record_t, return_t, signature_ts...>::functor_t;

    public:

        lambda_method(const functor& fptr) noexcept
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
            [[nodiscard]] constexpr decltype(auto) operator()(record_t& target, args_t&&...params) const noexcept(noexcept_v<args_t...>)
            {
                static_assert(is_args_t_ok<args_t...>, "Argument types don't match the expected signature.");
                return (target.*m_functor)(std::forward<args_t>(params)...);
            }

            const fptr_t<return_t> m_functor = nullptr;

        private:

            template<class ...args_t>
            static constexpr bool is_args_t_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

            template<class ...args_t>
            static constexpr bool noexcept_v = noexcept((std::declval<record_t>().*std::declval<fptr_t<return_t>>())(std::declval<args_t>()...));
        };


        template<class return_t>
        [[nodiscard]] constexpr const hopper<return_t> get_hopper() const
        {
            if (m_functor.m_returnId == detail::TypeId<return_t>::get())
            {
                fptr_t<return_t> func_ptr = (static_cast<const method_ptr<record_t, return_t, signature_ts...>&>(m_functor)).f_ptr();
                return hopper<return_t>{ func_ptr };
            }
            return hopper<return_t>();
        }
    };
}
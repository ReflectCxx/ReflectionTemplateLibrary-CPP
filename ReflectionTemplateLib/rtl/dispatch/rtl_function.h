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

#include "rtl_traits.h"
#include "rtl_forward_decls.h"

namespace rtl
{
    template<class return_t, class ...signature_ts>
    struct function<return_t(signature_ts...)>
    {
        using fptr_t = return_t(*)(signature_ts...);

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        template<class ...args_t>
        [[nodiscard]] constexpr decltype(auto) operator()(args_t&&...params) const noexcept // (noexcept_v<args_t...>)
        {
            //static_assert(is_args_t_ok<args_t...>, "Argument types don't match the expected signature.");
            return (*m_functor)(std::forward<args_t>(params)...);
        }

        function(fptr_t p_functor): m_functor(p_functor)
        { }
        
        function() = default;
        function(function&&) = default;
        function(const function&) = default;

        function& operator=(function&&) = default;
        function& operator=(const function&) = default;

    private:

        fptr_t m_functor = nullptr;

        template<class ...args_t>
        static constexpr bool is_args_t_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

        //template<class ...args_t>
        //static constexpr bool noexcept_v = noexcept(std::declval<return_t(*)(signature_ts...)>()(std::declval<args_t>()...));

        template<class ...args_t>
        friend struct dispatch::lambda_function;
    };
}

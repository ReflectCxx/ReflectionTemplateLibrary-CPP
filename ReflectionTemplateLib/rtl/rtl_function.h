/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <rtl_traits.h>
#include <rtl_forward_decls.h>

namespace rtl
{
    template<class return_t, class ...signature_t>
    struct function<return_t(signature_t...)>
    {
        using fptr_t = return_t(*)(signature_t...);

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        template<class ...args_t>
        [[nodiscard]] [[gnu::hot]]
        constexpr decltype(auto) operator()(args_t&&...params) const noexcept
        {
            return (*m_functor)(std::forward<args_t>(params)...);
        }

        function(fptr_t p_functor)
            : m_init_err(error::None)
            , m_functor(p_functor)
        { }
        
        function() = default;
        function(function&&) = default;
        function(const function&) = default;

        function& operator=(function&&) = default;
        function& operator=(const function&) = default;

        GETTER(rtl::error, _init_error, m_init_err)

    protected:

        fptr_t m_functor = nullptr;
        error m_init_err = error::InvalidCaller;

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

        template<detail::member, class ...>
        friend struct detail::InitFunctionHop;
    };
}


namespace rtl 
{
    template<class return_t, class ...signature_t>
    struct static_method<return_t(signature_t...)> : function<return_t(signature_t...)> 
    {
        using base_t = function<return_t(signature_t...)>;

        static_method(base_t::fptr_t p_functor) : base_t(p_functor)
        { }

        static_method() = default;
        static_method(static_method&&) = default;
        static_method(const static_method&) = default;

        static_method& operator=(static_method&&) = default;
        static_method& operator=(const static_method&) = default;

        template<detail::member, class ...>
        friend struct detail::InitFunctionHop;
    };
}
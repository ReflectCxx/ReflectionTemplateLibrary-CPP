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

#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    template<class known_t, class...args_t>
    struct method_lambda<fn_void::yes, erase::t_return, known_t, args_t...> : lambda
    {
        using record_t = known_t;
        using lambda_t = std::function<void(const lambda_base&, const record_t&, traits::normal_sign_t<args_t>...)>;

        const lambda_t& get_hop() const {
            return m_lambda;
        }

    private:
		
        void set_hop(const lambda_t& lambda) {
            m_lambda = lambda;
        }

        lambda_t m_lambda;

        template<class, class , class...>
        friend struct method_ptr;
    };
}


namespace rtl::dispatch
{
    template<class known_t, class...args_t>
    struct method_lambda<fn_void::no, erase::t_return, known_t, args_t...> : lambda
    {
        using record_t = known_t;
        using lambda_t = std::function<std::any(const lambda_base&, const record_t&, traits::normal_sign_t<args_t>...)>;

        const lambda_t& get_hop() const {
            return m_lambda;
        }

    private:

        void set_hop(const lambda_t& lambda) {
            m_lambda = lambda;
        }

        lambda_t m_lambda;

        template<class, class, class...>
        friend struct method_ptr;
    };
}


namespace rtl::dispatch
{
    template<class known_t, class...args_t>
    struct method_lambda<fn_void::yes, erase::t_target, known_t, args_t...> : lambda
    {
        using return_t = known_t;
        using lambda_t = std::function<void(const lambda_base&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;

        const lambda_t& get_hop() const {
            return m_lambda;
        }

    private:

        void set_hop(const lambda_t& lambda) {
            m_lambda = lambda;
        }

        lambda_t m_lambda;

        template<class, class, class...>
        friend struct method_ptr;
    };
}


namespace rtl::dispatch
{
    template<class known_t, class...args_t>
    struct method_lambda<fn_void::no, erase::t_target, known_t, args_t...> : lambda
    {
        using return_t = known_t;
        using lambda_t = std::function<return_t(const lambda_base&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;

        const lambda_t& get_hop() const {
            return m_lambda;
        }

    private:

        void set_hop(const lambda_t& lambda) {
            m_lambda = lambda;
        }

        lambda_t m_lambda;

        template<class, class, class...>
        friend struct method_ptr;
    };
}
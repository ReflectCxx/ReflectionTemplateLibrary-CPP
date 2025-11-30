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
        using fptr_t = void(*)(const functor&, const record_t&, traits::normal_sign_t<args_t>&&...);

        fptr_t f_ptr() const {
            return m_fptr;
        }

    private:

        void init(fptr_t fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

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
        using fptr_t = std::any(*)(const functor&, const record_t&, traits::normal_sign_t<args_t>&&...);

        const fptr_t& get_hop() const {
            return m_fptr;
        }

    private:

        void set_hop(const fptr_t& fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

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
        using fptr_t = void(*)(const functor&, const rtl::RObject&, traits::normal_sign_t<args_t>&&...);

        fptr_t f_ptr() const {
            return m_fptr;
        }

    private:

        void init(fptr_t fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

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
        using fptr_t = return_t(*)(const functor&, const rtl::RObject&, traits::normal_sign_t<args_t>&&...);

        const fptr_t& get_hop() const {
            return m_fptr;
        }

    private:

        void set_hop(const fptr_t& fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

        template<class, class, class...>
        friend struct method_ptr;
    };
}
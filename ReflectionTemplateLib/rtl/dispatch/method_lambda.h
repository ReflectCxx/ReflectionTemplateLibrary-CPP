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

#include <rtl_forward_decls.h>

namespace rtl::dispatch
{
    template<class known_t, class...args_t>
    struct method_lambda<erase::t_return, known_t, args_t...> : lambda
    {
        using record_t = known_t;
        using fptr_t = Return(*)(const functor&, const record_t&, traits::normal_sign_t<args_t>&&...);

        const fptr_t& f_ptr() const {
            return m_fptr;
        }

    private:

        void init(const fptr_t& fptr) {
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
    struct method_lambda<erase::t_target, known_t, args_t...> : lambda
    {
        using if_ref_t = std::conditional_t<std::is_reference_v<known_t>, std::remove_reference_t<known_t>*, known_t>;

        using if_void_t = std::conditional_t<std::is_void_v<known_t>, void*, if_ref_t>;

        using return_t = std::pair<error, std::optional<if_void_t>>;

        using fptr_t =  return_t(*)(const functor&, const rtl::RObject&, traits::normal_sign_t<args_t>&&...);

        const fptr_t& f_ptr() const {
            return m_fptr;
        }

    private:

        void init(const fptr_t& fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

        template<class, class, class...>
        friend struct method_ptr;
    };
}
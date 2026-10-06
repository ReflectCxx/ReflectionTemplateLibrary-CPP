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

#include <dispatch/functor.h>
#include <dispatch/method_lambda.h>
#include <dispatch/function_lambda.h>

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct method_ptr<const record_t, return_t, signature_t...> : functor
    {
        using functor_t = return_t(record_t::*)(signature_t...) const;

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr bool is_same(functor_t fptr) const {
            return (fptr == m_functor);
        }

        method_ptr(functor_t fptr) : m_functor(fptr)
        {
            m_member_kind = detail::member::Const;

            m_is_void = std::is_void_v<return_t>;
            m_return_id = traits::uid<return_t>::value;
            m_record_id = traits::uid<record_t>::value;

            m_is_any_arg_ncref = (traits::is_nonconst_ref_v<signature_t> || ...);
            m_normal_args_id = traits::uid<traits::normal_sign_id_t<signature_t...>>::value;
            m_strict_args_id = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;

            m_signature_str = detail::TypeId<return_t>::toString() + " [" + 
                              detail::TypeId<record_t>::toString() + "]::(" +
                              detail::TypeId<signature_t...>::toString() + ") const";
        }

    private:

        const functor_t m_functor;

        function_lambda<erase::t_method, signature_t...> m_erased_method;
        method_lambda<erase::t_return, record_t, signature_t...> m_erased_return;
        method_lambda<erase::t_target, return_t, signature_t...> m_erased_target;

        void init_lambda();

        template<class, class, class ...>
        friend struct cache::method_ptr;
    };
}
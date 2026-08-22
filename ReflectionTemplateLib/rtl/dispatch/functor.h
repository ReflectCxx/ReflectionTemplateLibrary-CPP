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

namespace rtl::dispatch
{
    struct functor
    {
        GETTER_BOOL(_void, m_is_void)
        GETTER_BOOL(_any_arg_ncref, m_is_any_arg_ncref)
        GETTER(traits::uid_t, _record_id, m_record_id)
        GETTER(traits::uid_t, _strict_sign_id, m_strict_args_id)
        GETTER(traits::uid_t, _normal_sign_id, m_normal_args_id)

    protected:

        enum index {
            erased_ctor = 0,
            erased_return = 0,
            erased_target = 1,
            erased_method = 2
        };

        std::string m_signature_str;

        traits::uid_t m_record_id = traits::uid<>::none;
        traits::uid_t m_return_id = traits::uid<>::none;

        traits::uid_t m_normal_args_id = traits::uid<>::none;
        traits::uid_t m_strict_args_id = traits::uid<>::none;

        bool m_is_void = false;
        bool m_is_any_arg_ncref = false;

        detail::member m_member_kind = detail::member::None;
        
        std::vector<lambda*> m_lambdas;
        std::vector<std::size_t> m_args_type_ids = {};
        
        friend rtl::type_meta;

        template<class...>
        friend struct functor_cast;
    };
}
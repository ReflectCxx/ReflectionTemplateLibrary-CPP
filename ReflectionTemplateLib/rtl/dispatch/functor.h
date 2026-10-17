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
        constexpr const bool is_void() const {
            return m_is_void;
        }

        constexpr const bool is_any_arg_ncref() const {
            return m_is_any_arg_ncref;
        }

        constexpr const traits::uid_t get_record_id() const {
            return m_record_id;
        }

        constexpr const traits::uid_t get_strict_sign_id() const {
            return m_strict_args_id;
        }

        constexpr const traits::uid_t get_normal_sign_id() const {
            return m_normal_args_id;
        }

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
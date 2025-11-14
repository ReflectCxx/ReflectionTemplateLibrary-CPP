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

#include <vector>

#include "rtl_traits.h"

namespace rtl::dispatch
{
	struct fn_meta 
	{
        constexpr bool is_void() const {
            return m_is_void;
        }

    protected:

        std::string m_record_str;
        std::string m_return_str;
        std::string m_signature_str;

        traits::uid_t m_record_id = traits::uid<>::none;
        traits::uid_t m_return_id = traits::uid<>::none;

        traits::uid_t m_normal_args_id = traits::uid<>::none;
        traits::uid_t m_strict_args_id = traits::uid<>::none;

        bool m_is_void = false;
        bool m_is_any_arg_ncref = false;
        std::vector<std::size_t> m_args_type_ids = {};

        detail::member m_member_kind = detail::member::None;

        enum index {
            ctor = 0,       // constructor
            fn_eret = 0,    // function-erased-return
            mth_eret = 0,   // method-erased-return
            mth_etar = 1    // method-erased-target
        };

        std::vector<fn_lambda*> m_lambda;
	};
}
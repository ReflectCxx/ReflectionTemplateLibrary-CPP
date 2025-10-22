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

#include "RObjectId.h"
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
	struct erasure_base
	{
        template<class ...args_t>
        using erased_return_t = erase_return<traits::normal_sign_t<args_t>...>;

        template<class ...args_t>
        using erased_record_t = erase_return_n_target<traits::normal_sign_t<args_t>...>;

        template<class record_t, class ...args_t>
        using e_ret_a_target_t = erase_return_aware_target<record_t, traits::normal_sign_t<args_t>...>;

        template<class return_t, class ...args_t>
        using e_target_a_ret_t = erase_target_aware_return<return_t, traits::normal_sign_t<args_t>...>;

        template<class ...signature_t>
        constexpr const erased_return_t<signature_t...>& to_erased_return() const
        {
            return static_cast<const erased_return_t<signature_t...>&>(*this);
        }

        template<class ...signature_t>
        constexpr const erased_record_t<signature_t...>& to_erased_record() const
        {
            return static_cast<const erased_record_t<signature_t...>&>(*this);
        }

        template<class record_t, class ...signature_t>
        constexpr const e_ret_a_target_t<record_t, signature_t...>& to_erased_return_aware_target() const;

        template<class return_t, class ...signature_t>
        constexpr const e_target_a_ret_t<return_t, signature_t...>& to_erased_target_aware_return() const;

    protected:

        detail::RObjectId m_return_id = {};

        friend lambda_base;
	};
}
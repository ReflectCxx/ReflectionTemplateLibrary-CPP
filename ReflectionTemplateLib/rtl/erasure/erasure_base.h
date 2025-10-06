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

#include "functor.h"
#include "RObjectId.h"

namespace rtl::erase
{
	struct erasure_base
	{
        template<class ...args_t>
        using ehop_t = erased_hopper<traits::normal_sign_t<args_t>...>;

        template<class ...signature_t>
        constexpr const ehop_t<signature_t...>& to_erased_ret_function() const
        {
            return static_cast<const ehop_t<signature_t...>&>(*this);
        }

        template<class record_t, class ...args_t>
        using ehop_mt = erased_method_hop<record_t, args_t...>;

        template<class record_t, class ...signature_t>
        constexpr const ehop_mt<record_t, signature_t...>& to_erased_ret_method() const
        {
            return static_cast<const ehop_mt<record_t, signature_t...>&>(*this);
        }

        erasure_base(const dispatch::functor& p_functor, const detail::RObjectId& p_robj_id) noexcept
            : m_functor(p_functor)
            , m_robj_id(p_robj_id)
        { }

        const dispatch::functor& m_functor;

        const detail::RObjectId m_robj_id;

        GETTER(detail::RObjectId, _return_id, m_robj_id);

        GETTER(dispatch::lambda_base, _lambda, (*m_functor.get_lambda()));
	};
}
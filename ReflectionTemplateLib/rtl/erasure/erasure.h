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
        using function_t = erased_function<args_t...>;

        template<class ...signature_ts>
        constexpr const function_t<signature_ts...>& to_erased_ret_function() const
        {
            return static_cast<const function_t<signature_ts...>&>(*this);
        }

        template<class record_t, class ...args_t>
        using method_t = erased_method<record_t, args_t...>;

        template<class record_t, class ...signature_ts>
        constexpr const method_t<record_t, signature_ts...>& to_erased_ret_method() const
        {
            return static_cast<const method_t<record_t, signature_ts...>&>(*this);
        }

        erasure_base(const dispatch::functor& p_functor, const detail::RObjectId& p_robj_id) noexcept
            : m_functor(p_functor)
            , m_robj_id(p_robj_id)
        { }

        const dispatch::functor& m_functor;

        const detail::RObjectId m_robj_id;

        GETTER(detail::RObjectId, _return_id, m_robj_id);
	};
}
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

#include <functional>

#include "erasure_base.h"

namespace rtl::dispatch::erase
{
    template<class ...norm_sign_t>
    struct erased_hopper : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, norm_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, norm_sign_t...)>;

        using lambda_robj_vt = std::function<void(const lambda_base&, const RObject&, norm_sign_t...)>;

        using lambda_robj_rt = std::function<std::any(const lambda_base&, const RObject&, norm_sign_t...)>;

        template<class...args_t>
        constexpr void hop_void(args_t&&...params) const noexcept
        {
            m_void_hop(get_lambda(), std::forward<args_t>(params)...);
        }

        template<class...args_t>
        ForceInline std::any hop_return(args_t&&...params) const noexcept
        {
            return m_any_ret_hop(get_lambda(), std::forward<args_t>(params)...);
        }

        template<class...args_t>
        constexpr void hop_void(const RObject& p_robj, args_t&&...params) const noexcept
        {
            m_void_method_hop(get_lambda(), p_robj, std::forward<args_t>(params)...);
        }

        template<class...args_t>
        ForceInline std::any hop_return(const RObject& p_robj, args_t&&...params) const noexcept
        {
            return m_any_ret_method_hop(get_lambda(), p_robj, std::forward<args_t>(params)...);
        }

    protected:

        lambda_vt m_void_hop;

        lambda_rt m_any_ret_hop;

        lambda_robj_vt m_void_method_hop;

        lambda_robj_rt m_any_ret_method_hop;

        erased_hopper( const dispatch::functor& p_functor,
                       const detail::RObjectId& p_robj_id,
                       const lambda_vt& p_void_hop,
                       const lambda_rt& p_any_ret_hop ) noexcept

            : erasure_base(p_functor, p_robj_id)
            , m_void_hop(p_void_hop)
            , m_any_ret_hop(p_any_ret_hop)
        { }

        erased_hopper( const dispatch::functor& p_functor,
                       const detail::RObjectId& p_robj_id,
                       const lambda_robj_vt& p_void_method_hop,
                       const lambda_robj_rt& p_any_ret_method_hop ) noexcept

            : erasure_base(p_functor, p_robj_id)
            , m_void_method_hop(p_void_method_hop)
            , m_any_ret_method_hop(p_any_ret_method_hop)
        { }
    };
}
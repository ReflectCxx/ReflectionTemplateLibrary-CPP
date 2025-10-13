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
    template<class ...normal_sign_t>
    struct erased_hopper : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, normal_sign_t...)>;

        using lambda_robj_vt = std::function<void(const lambda_base&, const RObject&, normal_sign_t...)>;

        using lambda_robj_rt = std::function<std::any(const lambda_base&, const RObject&, normal_sign_t...)>;

        GETTER(lambda_vt, _void_hopper, m_void_hop)
        GETTER(lambda_rt, _return_hopper, m_any_ret_hop)
        GETTER(lambda_robj_vt, _void_method_hopper, m_void_method_hop)
        GETTER(lambda_robj_rt, _return_method_hopper, m_any_ret_method_hop)

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
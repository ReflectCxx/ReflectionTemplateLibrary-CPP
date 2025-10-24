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

namespace rtl::dispatch
{
    template<class ...normal_sign_t>
    struct erase_return_n_target : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, const RObject&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, const RObject&, normal_sign_t...)>;

        GETTER_CREF(lambda_vt, _void_hopper, m_vhopper)
        GETTER_CREF(lambda_rt, _return_hopper, m_rhopper)

        template<class record_t>
        constexpr const erase_return_aware_target<record_t, normal_sign_t...>& to_erased_return() const
        {
            return static_cast<const erase_return_aware_target<record_t, normal_sign_t...>&>(*m_erased_return);
        }

        template<class return_t>
        constexpr const erase_target_aware_return<return_t, normal_sign_t...>& to_erased_target() const
        {
            return static_cast<const erase_target_aware_return<return_t, normal_sign_t...>&>(*m_erased_target);
        }

    protected:

        lambda_vt m_vhopper;
        lambda_rt m_rhopper;

        const erasure_base* m_erased_return;
        const erasure_base* m_erased_target;

        erase_return_n_target( const lambda_vt& p_void_hop,
                               const lambda_rt& p_any_ret_hop ) noexcept

            : m_vhopper(p_void_hop)
            , m_rhopper(p_any_ret_hop)
        { }
    };
}
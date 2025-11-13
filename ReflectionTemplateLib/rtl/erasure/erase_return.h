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
    struct erase_return : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, normal_sign_t...)>;

        using lambda_ctor_t = std::function<Return(alloc, normal_sign_t...)>;

        GETTER_CREF(lambda_vt, _void_hopper, m_vhopper)
        GETTER_CREF(lambda_rt, _return_hopper, m_rhopper)

    private:

        lambda_vt m_vhopper = nullptr;

        lambda_rt m_rhopper = nullptr;

        lambda_ctor_t m_ctor_hopper = nullptr;

        template<class return_t>
        void init_base()
        {
            constexpr static bool is_const_cast_safe = (!traits::is_const_v<return_t>);
            m_return_id = detail::RObjectId::create<return_t, alloc::Stack>(is_const_cast_safe);
        }

        template<class, class...>
        friend struct cache::lambda_function;
    };
}
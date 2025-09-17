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

#include <tuple>
#include <functional>

#include "forward_decls.h"
#include "dispatch_interface.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda: public lambda_hop
    {
        using lambda_t = std::function<Return(const lambda_hop*, signature_ts...)>;

        template<class record_t>
        void init_ctor() const;

        template<class record_t>
        void init_cloner() const;

        template<class return_t>
        void init_function() const;

        template<class record_t, class return_t>
        void init_method_const() const;

        template<class record_t, class return_t>
        void init_method_nonconst() const;

        Return operator()(signature_ts&&...params) const
        {
            return m_hopper(this, std::forward<signature_ts>(params)...);
        }

    private:

        lambda(const functor_hop* fptr_hopper)
        {
            detail::TypeId<signature_ts...>::get(m_argsTypeIds);
            m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
            m_functor = fptr_hopper;
        }

        lambda_t m_hopper;
    };
}
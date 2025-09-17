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
#include "rtl_typeid.h"
#include "rtl_constants.h"

namespace rtl::dispatch
{
    struct functor_hop;

    template<class ...signature_ts>
    struct lambda;

    struct lambda_hop
    {
        std::size_t m_signatureId = detail::TypeId<>::None;

        traits::args_t m_argumentsId = {};

        const functor_hop* m_functor = nullptr;

        const functor_hop& functor() const
        {
            return *m_functor;
        }

        template<class ...signature_ts>
        const lambda<signature_ts...>& get() const
        { 
            return (*static_cast<const lambda<signature_ts...>*>(this));
        }
    };
}


namespace rtl::dispatch
{
    template<class return_t, class ...signature_ts>
    struct functor;

    template<class record_t, class return_t, class ...signature_ts>
    struct functor_const;

    template<class record_t, class return_t, class ...signature_ts>
    struct functor_nonconst;

    struct functor_hop
    {
        mutable const lambda_hop* m_lambda = nullptr;

        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;
        detail::methodQ m_qualifier = detail::methodQ::None;

        void set_lambda(const lambda_hop* lambda) const
        {
            m_lambda = lambda;
        }

        template<class return_t, class ...signature_ts>
        const functor<return_t, signature_ts...>& get() const
        {
            return *(static_cast<const functor<return_t, signature_ts...>*>(this));
        }

        template<class record_t, class return_t, class ...signature_ts>
        const functor_const<record_t, return_t, signature_ts...>& get_const() const
        {
            return *(static_cast<const functor_const<record_t, return_t, signature_ts...>*>(this));
        }

        template<class record_t, class return_t, class ...signature_ts>
        const functor_nonconst<record_t, return_t, signature_ts...>& get_nonconst() const
        {
            return *(static_cast<const functor_nonconst<record_t, return_t, signature_ts...>*>(this));
        }
    };
}
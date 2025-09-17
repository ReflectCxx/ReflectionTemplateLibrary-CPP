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

#include "rtl_typeid.h"
#include "rtl_constants.h"

namespace rtl::dispatch
{
    struct functor_hop;

    template<class ...signature_ts>
    struct lambda;

    struct lambda_hop
    {
        const functor_hop* m_functor = nullptr;

        std::vector<std::size_t> m_argsTypeIds;
        std::size_t m_signatureId = detail::TypeId<>::None;

        template<class ...signature_ts>
        const lambda<signature_ts...>& get() const
        { 
            return (*static_cast<lambda<signature_ts...>*>(this));
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
        const lambda_hop* m_lambda = nullptr;

        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;
        detail::methodQ m_qualifier = detail::methodQ::None;

        template<class return_t, class ...signature_ts>
        const functor<return_t, signature_ts...>& get() const
        {
            return *(static_cast<functor<return_t, signature_ts...>*>(this));
        }

        template<class record_t, class return_t, class ...signature_ts>
        const functor_const<record_t, return_t, signature_ts...>& get_const() const
        {
            return *(static_cast<functor_const<record_t, return_t, signature_ts...>*>(this));
        }

        template<class record_t, class return_t, class ...signature_ts>
        const functor_nonconst<record_t, return_t, signature_ts...>& get_nonconst() const
        {
            return *(static_cast<functor_nonconst<record_t, return_t, signature_ts...>*>(this));
        }
    };
}
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
#include "functor.h"

namespace rtl::dispatch
{
    struct lambda_hop
    {
        template<class record_t>
        constexpr bool is_member() const
        {
            return (m_functor->getRecordId() == detail::TypeId<traits::raw_t<record_t>>::get() ||
                    m_functor->getRecordId() == detail::TypeId<const traits::raw_t<record_t>>::get());
        }

        template<class return_t>
        constexpr bool is_returning() const
        {
            return (m_functor->getReturnId() == detail::TypeId<traits::raw_t<return_t>>::get());
        }

        template<class...args_t>
        constexpr bool is_signature() const
        {
            return (m_signatureId == detail::TypeId<std::tuple<traits::raw_t<args_t>...>>::get());
        }

        template<class ...signature_ts>
        constexpr const lambda_hop_function<signature_ts...>* get_function() const
        {
            const std::size_t typeId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            if (typeId == m_signatureId) 
            {
                return static_cast<const lambda_hop_function<signature_ts...>*>(this);
            }
            return nullptr;
        }

        template<class record_t, class ...signature_ts>
        const lambda_hop_method<record_t, signature_ts...>* get_method() const
        {
            std::size_t recordId = detail::TypeId<record_t>::get();
            std::size_t typeId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            if (typeId == m_signatureId && recordId == m_functor->getRecordId())
            {
                return static_cast<const lambda_hop_method<record_t, signature_ts...>*>(this);
            }
            return nullptr;
        }

        GETTER(std::size_t, SignatureId, m_signatureId);

//    protected:

        const functor* m_functor = nullptr;
        std::size_t m_signatureId = detail::TypeId<>::None;
        std::vector<std::size_t> m_argumentsId = {};
    };
}
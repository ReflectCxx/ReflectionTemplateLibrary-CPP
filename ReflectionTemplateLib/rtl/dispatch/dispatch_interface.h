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
    struct lambda_hop
    {
        const functor_hop& functor() const
        {
            return *m_functor;
        }

        template<class record_t>
        bool is_member() const
        {
            return (m_recordId == detail::TypeId<traits::raw_t<record_t>>::get() || 
                    m_recordId == detail::TypeId<const traits::raw_t<record_t>>::get());
        }

        template<class return_t>
        bool is_returning() const
        {
            return (m_returnId == detail::TypeId<return_t>::get());
        }

        template<class...args_t>
        bool is_signature() const
        {
            return (m_signatureId == detail::TypeId<std::tuple<args_t...>>::get());
        }

        template<class ...signature_ts>
        const lambda<signature_ts...>* get_function() const
        { 
            std::size_t typeId = detail::TypeId<std::tuple<signature_ts...>>::get();
            if (typeId == m_signatureId) {
                return static_cast<const lambda<signature_ts...>*>(this);
            }
            return nullptr;
        }

        template<class record_t, class ...signature_ts>
        const lambda_method<record_t, signature_ts...>* get_method() const
        {
            std::size_t recordId = detail::TypeId<record_t>::get();
            std::size_t typeId = detail::TypeId<std::tuple<signature_ts...>>::get();
            if (typeId == m_signatureId && recordId == m_recordId) {
                return static_cast<const lambda_method<record_t, signature_ts...>*>(this);
            }
            return nullptr;
        }

//    protected:

        const functor_hop* m_functor = nullptr;
        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;
        std::vector<std::size_t> m_argumentsId = {};
    };
}


namespace rtl::dispatch
{
    struct functor_hop
    {
        void set_lambda(const lambda_hop* lambda) const
        {
            m_lambda = lambda;
        }

        template<class ...signature_ts>
        const functor<signature_ts...>& get() const
        {
            return *(static_cast<const functor<signature_ts...>*>(this));
        }

        template<class record_t, class ...signature_ts>
        const functor_const<record_t, signature_ts...>& get_const() const
        {
            return *(static_cast<const functor_const<record_t, signature_ts...>*>(this));
        }

        template<class record_t, class ...signature_ts>
        const functor_nonconst<record_t, signature_ts...>& get_nonconst() const
        {
            return *(static_cast<const functor_nonconst<record_t, signature_ts...>*>(this));
        }

//    protected:
        
        mutable const lambda_hop* m_lambda = nullptr;

        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;
        detail::methodQ m_qualifier = detail::methodQ::None;
    };
}
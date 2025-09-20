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

#include "rtl_traits.h"
#include "rtl_typeid.h"
#include "rtl_constants.h"
#include "forward_decls.h"


namespace rtl::dispatch
{
    template<class return_t>
    struct functor_cast
    {
        const functor* m_functor;

        template<class ...signature_ts>
        constexpr const function_ptr<return_t, signature_ts...>& signature() const
        {
            return *(static_cast<const function_ptr<return_t, signature_ts...>*>(m_functor));
        }
    };

    struct functor
    {
        constexpr void set_lambda(const lambda_hop* lambda) const
        {
            m_lambda = lambda;
        }

        //template<class record_t, class ...signature_ts>
        //constexpr const const_method_ptr<record_t, signature_ts...>& get_const() const
        //{
        //    return *(static_cast<const const_method_ptr<record_t, signature_ts...>*>(this));
        //}

        //template<class record_t, class ...signature_ts>
        //constexpr const method_ptr<record_t, signature_ts...>& get_nonconst() const
        //{
        //    return *(static_cast<const method_ptr<record_t, signature_ts...>*>(this));
        //}

        GETTER(std::size_t, ReturnId, m_returnId);
        GETTER(std::size_t, RecordId, m_recordId);
        GETTER(std::size_t, SignatureId, m_signatureId);

//    protected:

        mutable const lambda_hop* m_lambda = nullptr;

        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;
        detail::methodQ m_qualifier = detail::methodQ::None;
    };
}
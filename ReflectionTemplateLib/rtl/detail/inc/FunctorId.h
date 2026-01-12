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


#include "rtl_constants.h"
#include "functor.h"

namespace rtl::detail
{
/*  @class: FunctorId
    * 'FunctorId' object is generated for every functor (member/non-member function pointer) registered.
    * acts as a hash-key to lookup a particular functor in the functor-table.
    * first, using 'm_containerId', the functor-table container is found.
    * once table is found, the functor is accessed at index 'm_index', (never fails, noexcept)
    * 'FunctorId' generated for a each functor is unique, even for overloaded functions.
    * multiple registartion of same functor will generate same duplicate 'FunctorId'.
*/  struct FunctorId
    {
        //return type-id of the functor registered.
        std::size_t m_returnId;

        //if functor is a member-function, type id of class/struct it belongs to.
        traits::uid_t m_recordId;

        const dispatch::functor* m_functor = nullptr;

        GETTER(std::size_t, ReturnId, m_returnId)
        GETTER(traits::uid_t, RecordId, m_recordId)
        GETTER(traits::uid_t, SignatureId, (m_functor->get_strict_sign_id()))
        GETTER_CREF(dispatch::functor, _functor, (*m_functor))

        const bool operator==(const FunctorId& pOther) const
        {
            return (m_returnId == pOther.m_returnId && 
                    m_recordId == pOther.m_recordId &&
                    m_functor == pOther.m_functor);
        }

        const std::string getSignatureStr(const std::string& pFunctionName = "") const {

            const auto& recordStr = m_functor->get_record_str();
            if (recordStr.empty()) {
                return m_functor->get_return_str() + " " + pFunctionName + 
                       "(" + m_functor->get_signature_str() + ")";
            }
            else {
                return m_functor->get_return_str() + " " + recordStr + "::" +
                       pFunctionName + "(" + m_functor->get_signature_str() + ")";
            }
        }
    };
}
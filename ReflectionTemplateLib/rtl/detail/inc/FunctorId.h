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
#include "rtl_forward_decls.h"

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
        //index of the functor in the functor-table.
        std::size_t m_lambdaIndex;

        //return type-id of the functor registered.
        std::size_t m_returnId;

        //if functor is a member-function, type id of class/struct it belongs to.
        std::size_t m_recordId;

        //containerId of the functor-table.
        std::size_t m_containerId;

        //signature of functor as string. platform dependent, may not be very much readable format.
        std::string m_signature;

        const dispatch::functor* m_functor = nullptr;

        GETTER(std::size_t, ReturnId, m_returnId);
        GETTER(std::size_t, RecordId, m_recordId);
        GETTER(std::size_t, SignatureId, m_containerId)
        GETTER_CREF(std::string, SignatureStr, m_signature)
        GETTER_CREF(dispatch::functor, _functor, (*m_functor))

        const bool operator==(const FunctorId& pOther) const
        {
            return (m_returnId == pOther.m_returnId && 
                    m_recordId == pOther.m_recordId &&
                    m_containerId == pOther.m_containerId &&
                    m_lambdaIndex == pOther.m_lambdaIndex &&
                    m_signature == pOther.m_signature);
        }
    };
}
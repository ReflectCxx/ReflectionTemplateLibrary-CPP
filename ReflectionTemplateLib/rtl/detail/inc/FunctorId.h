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

        const dispatch::lambda_base* m_lambda = nullptr;

        GETTER(std::size_t, LambdaIndex, m_lambdaIndex)
        GETTER(std::size_t, ReturnId, m_returnId);
        GETTER(std::size_t, RecordId, m_recordId);
        GETTER(std::size_t, SignatureId, m_containerId)
        GETTER_CREF(std::string, SignatureStr, m_signature)
        GETTER_CREF(dispatch::lambda_base, _lambda, (*m_lambda))

    /*  @method: getHashCode()
        @return: std::size_t (a unique hash-code for a functor)
        * 'm_containerId' will be same for functors(non-member) with same signatures.
        * for member functions, a functor will have three atrributes
            - signature
            - whether it is const or non-const
            - class/struct type
            'm_containerId' will be same for functors with same above attributes.
        * every functor will have a distinct index in the functor-wrapped-lambda-table.
        * so, combination of m_containerId & m_index is unique for every functor.
    */  std::size_t getHashCode() const
        {
            return std::stoull(std::to_string(m_containerId) +
                               std::to_string(m_lambdaIndex) +
                               std::to_string(m_recordId) +
                               std::to_string(m_returnId));
        }

        const bool operator==(const FunctorId& pOther) const
        {
            return (m_returnId == pOther.m_returnId && 
                    m_recordId == pOther.m_recordId &&
                    m_containerId == pOther.m_containerId &&
                    m_lambdaIndex == pOther.m_lambdaIndex &&
                    m_signature == pOther.m_signature);
        }

        template<class ..._signature>
        using lambda_ft = dispatch::lambda_function<_signature...>;

        template<class rec_t, class ..._signature>
        using lambda_mt = dispatch::lambda_method<rec_t, _signature...>;

        template<class ...args_t>
        constexpr const lambda_ft<args_t...>* get_lambda_function(std::size_t p_argsId = 0) const;
        
        template<class record_t, class ...args_t>
        constexpr const lambda_mt<record_t, args_t...>* get_lambda_method(std::size_t p_recordId = 0, std::size_t p_argsId = 0) const;
    };
}
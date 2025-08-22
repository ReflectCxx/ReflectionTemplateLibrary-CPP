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

#include "ReflectionBuilder.h"
#include "FunctorContainer.h"
#include "MethodContainer.h"
#include "SetupMethod.hpp"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl::detail 
{	

    inline ReflectionBuilder::ReflectionBuilder(const std::string_view pFunction, std::size_t pRecordId,
                                                const std::string_view pNamespace /* = ""*/, 
                                                const std::string_view pRecord /* = ""*/)
        : m_recordId(pRecordId)
        , m_record(pRecord)
        , m_function(pFunction)
        , m_namespace(pNamespace)
    { }


/*  @method: buildFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with,
    *       '_returnType' & '_signature...'(auto deduced).
    * adds the function pointer in 'FunctorContainer'
    * accepts only a non-member or static-member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _returnType, class ..._signature>
    inline const access::Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...)) const
    {
        using Container = FunctorContainer< traits::remove_const_if_not_reference<_signature>...>;
        const FunctorId& functorId = Container::template addFunctor<_returnType, _signature...>(pFunctor, m_recordId);
        //assert(functorId.getRecordId() == m_recordId && "function pointer is not member-function of specified record type");
        return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::None);
    }


/*  @method: buildFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
    *       '_returnType' & '_signature...'(auto deduced).
    * adds the function pointer in 'MethodContainer'
    * accepts only a non-static, non-const member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const
    {
        using Container = MethodContainer<methodQ::NonConst, traits::remove_const_if_not_reference<_signature>...>;
        const FunctorId& functorId = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::NonConst);
    }


/*  @method: buildMethodFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
    *       '_returnType' & '_signature...'(auto deduced).
    * adds the function pointer in 'MethodContainer'
    * accepts only a const member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const
    {
        using Container = MethodContainer<methodQ::Const, traits::remove_const_if_not_reference<_signature>...>;
        const FunctorId& functorId = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::Const);
    }


/*  @method: buildConstructor()
    @return: 'Function', object associated with the (specified parametrized) constructor.
    @param: '_recordType'(class/struct type) & '_ctorSignature...' (explicitly specified),
    * adds the lambda invoking constructor (type-erased) in 'FunctorContainer'
    * builds the 'Function' object containing hash-key & meta-data for the constructor.
*/  template<typename _recordType, class ..._ctorSignature>
    inline const access::Function ReflectionBuilder::buildConstructor() const
    {
        using Container = FunctorContainer<rtl::alloc, traits::remove_const_if_not_reference<_ctorSignature>...>;
        const FunctorId& functorId = Container::template addConstructor<_recordType, _ctorSignature...>();
            
        return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::None);
    }
}

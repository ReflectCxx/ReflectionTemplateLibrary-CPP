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
#include "SetupConstructor.h"

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
    inline const Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...), member pMemberType, traits::uid_t pRecordUid) const
    {
        using Container = FunctorContainer< traits::remove_const_if_not_reference<_signature>...>;
        auto [typeMeta, functorId] = Container::template addFunctor<_returnType, _signature...>(pFunctor, pRecordUid, m_recordId, pMemberType);
        return Function(m_namespace, m_record, m_function, typeMeta, functorId, m_recordId, pMemberType);
    }


/*  @method: buildFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
    *       '_returnType' & '_signature...'(auto deduced).
    * adds the function pointer in 'MethodContainer'
    * accepts only a non-static, non-const member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const
    {
        using Container = MethodContainer<detail::member::NonConst, traits::remove_const_if_not_reference<_signature>...>;
        auto [typeMeta, functorId] = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return Function(m_namespace, m_record, m_function, typeMeta, functorId, m_recordId, member::NonConst);
    }


/*  @method: buildMethodFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
    *       '_returnType' & '_signature...'(auto deduced).
    * adds the function pointer in 'MethodContainer'
    * accepts only a const member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const
    {
        using Container = MethodContainer<detail::member::Const, traits::remove_const_if_not_reference<_signature>...>;
        auto [typeMeta, functorId] = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return Function(m_namespace, m_record, m_function, typeMeta, functorId, m_recordId, member::Const);
    }


/*  @method: buildConstructor()
    @return: 'Function', object associated with the (specified parametrized) constructor.
    @param: '_recordType'(class/struct type) & '_ctorSignature...' (explicitly specified),
    * adds the lambda invoking constructor (type-erased) in 'FunctorContainer'
    * builds the 'Function' object containing hash-key & meta-data for the constructor.
*/  template<typename _recordType, class ..._ctorSignature>
    inline const Function ReflectionBuilder::buildConstructor() const
    {
        auto [typeMeta, functorId] = SetupConstructor::addConstructor<_recordType, _ctorSignature...>();
        const Function& ctorFunction = Function(m_namespace, m_record, m_function, typeMeta, functorId, m_recordId, member::None);
        return ctorFunction;
    }
}
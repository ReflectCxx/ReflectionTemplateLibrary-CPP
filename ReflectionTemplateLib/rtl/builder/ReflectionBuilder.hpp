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


#include "SetupMethod.h"
#include "RegisterCtor.h"
#include "RegisterFunction.h"
#include "ReflectionBuilder.h"

namespace rtl::detail 
{	

    inline ReflectionBuilder::ReflectionBuilder(const std::string& pFunction, std::size_t pRecordId,
                                                const std::string& pRecordStr, const std::string& pNamespace)
        : m_recordId(pRecordId)
        , m_recordStr(pRecordStr)
        , m_function(pFunction)
        , m_namespaceStr(pNamespace)
    { }


/*  @method: buildFunctor()
    @return: 'Function', object associated with the given functor.
    @param: 'pFunctor', function pointer with,
    *       '_returnType' & '_signature...'(auto deduced).
    * accepts only a non-member or static-member function pointer.
    * builds the 'Function' object containing hash-key & meta-data for the given functor.
*/  template<class _returnType, class ..._signature>
    inline const Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...), member pMemberType) const
    {
        type_meta fnMeta = RegisterFunction::template addFunctor<_returnType, _signature...>(pFunctor, m_recordId, pMemberType);
        return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, pMemberType);
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
        type_meta fnMeta = RegisterMethod::template addMethodFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, member::NonConst);
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
        type_meta fnMeta = RegisterMethod::template addMethodFunctor<_recordType, _returnType, _signature...>(pFunctor);
        return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, member::Const);
    }


/*  @method: buildConstructor()
    @return: 'Function', object associated with the (specified parametrized) constructor.
    @param: '_recordType'(class/struct type) & '_ctorSignature...' (explicitly specified),
    * builds the 'Function' object containing hash-key & meta-data for the constructor.
*/  template<typename _recordType, class ..._ctorSignature>
    inline const Function ReflectionBuilder::buildConstructor() const
    {
        type_meta fnMeta = RegisterCtor::template addConstructor<_recordType, _ctorSignature...>();
        return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, fnMeta.get_member_kind());
    }
}
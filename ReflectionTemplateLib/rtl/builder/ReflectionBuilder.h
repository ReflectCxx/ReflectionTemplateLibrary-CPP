/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/Function.h>
#include <builder/RegisterCtor.h>
#include <builder/RegisterMethod.h>
#include <builder/RegisterFunction.h>

namespace rtl::builder {

/*  @class: ReflectionBuilder
    * adds the given non-member, static-member 'functor' to the 'FunctionContainer'.
    * adds the given const/non-const member, non-static-member 'functor' to the 'MethodContainer'.
    * adds the constructor to 'FunctionContainer'.
*/  struct ReflectionBuilder
    {
    protected:

        const traits::uid_t m_recordId;
        const std::string m_recordStr;
        const std::string m_function;
        const std::string m_namespaceStr;

        ReflectionBuilder(const std::string& pFunction, std::size_t pRecordId,
                            const std::string& pRecordStr, const std::string& pNamespace) 
            : m_recordId(pRecordId)
            , m_recordStr(pRecordStr)
            , m_function(pFunction)
            , m_namespaceStr(pNamespace)
        { }

        template<class record_t, class ...signature_t>
        const Function buildConstructor() const
        {
            type_meta fnMeta = RegisterCtor::template addConstructor<record_t, signature_t...>();
            return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, fnMeta.get_member_kind());
        }

        template<class return_t, class ...signature_t>
        const Function buildFunctor(return_t(*pFunctor)(signature_t...), detail::member pMemberType) const
        {
            type_meta fnMeta = RegisterFunction::template addFunctor<return_t, signature_t...>(pFunctor, m_recordId, pMemberType);
            return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, pMemberType);
        }

        //adds 'pFunctor' to the 'MethodContainer'.
        template<class record_t, class return_t, class ...signature_t>
        const Function buildMethodFunctor(return_t(record_t::* pFunctor)(signature_t...)) const
        {
            type_meta fnMeta = RegisterMethod::template addMethodFunctor<record_t, return_t, signature_t...>(pFunctor);
            return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, detail::member::NonConst);
        }

        //adds 'pFunctor' to the 'MethodContainer'.
        template<class record_t, class return_t, class ...signature_t>
        const Function buildMethodFunctor(return_t(record_t::* pFunctor)(signature_t...) const) const
        {
            type_meta fnMeta = RegisterMethod::template addMethodFunctor<record_t, return_t, signature_t...>(pFunctor);
            return Function(m_namespaceStr, m_recordStr, m_function, fnMeta, m_recordId, detail::member::Const);
        }
    };
}
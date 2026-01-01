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

#include "Function.h"

namespace rtl {

    namespace detail 
    {
    /*  @class: ReflectionBuilder
        * adds the given non-member, static-member 'functor' to the 'FunctionContainer'.
        * adds the given const/non-const member, non-static-member 'functor' to the 'MethodContainer'.
        * adds the constructor to 'FunctionContainer'.
    */  class ReflectionBuilder
        {
        protected:

            const traits::uid_t m_recordId;
            const std::string m_recordStr;
            const std::string m_function;
            const std::string m_namespaceStr;

            ReflectionBuilder(const std::string& pFunction, std::size_t pRecordId,
                              const std::string& pRecordStr, const std::string& pNamespace);

            template<class _recordType, class ..._ctorSignature>
            const Function buildConstructor() const;

            template<class _returnType, class ..._signature>
            const Function buildFunctor(_returnType(*pFunctor)(_signature...), member pMemberType) const;

            //adds 'pFunctor' to the 'MethodContainer'.
            template<class _recordType, class _returnType, class ..._signature>
            const Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const;

            //adds 'pFunctor' to the 'MethodContainer'.
            template<class _recordType, class _returnType, class ..._signature>
            const Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const;
        };
    }
}
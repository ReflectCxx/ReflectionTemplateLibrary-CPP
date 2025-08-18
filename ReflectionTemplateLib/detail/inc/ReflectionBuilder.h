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

            const std::string& m_record;
            const std::string& m_function;
            const std::string& m_namespace;
            const std::size_t m_recordId;

            explicit ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord,
                                       const std::string& pFunction, std::size_t pRecordId);

            //adds constructor (any overload) to the 'FunctorContainer'.
            template<class _recordType, class ..._ctorSignature>
            const access::Function buildConstructor() const;

            //adds 'pFunctor' to the 'FunctorContainer'.
            template<class _returnType, class ..._signature>
            const access::Function buildFunctor(_returnType(*pFunctor)(_signature...)) const;

            //adds 'pFunctor' to the 'MethodContainer'.
            template<class _recordType, class _returnType, class ..._signature>
            const access::Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const;

            //adds 'pFunctor' to the 'MethodContainer'.
            template<class _recordType, class _returnType, class ..._signature>
            const access::Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const;
        };
    }
}
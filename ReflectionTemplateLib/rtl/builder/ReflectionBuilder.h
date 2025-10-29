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
#include "rtl_constants.h"

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

            const std::size_t m_recordId;
            const std::string_view m_record;
            const std::string_view m_function;
            const std::string_view m_namespace;

            ReflectionBuilder(const std::string_view pFunction, std::size_t pRecordId,
                              const std::string_view pNamespace = "",
                              const std::string_view pRecord = "");

            //adds constructor (any overload) to the 'FunctorContainer'.
            template<class _recordType, class ..._ctorSignature>
            const Function buildConstructor() const;

            //adds 'pFunctor' to the 'FunctorContainer'.
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
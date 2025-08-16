/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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
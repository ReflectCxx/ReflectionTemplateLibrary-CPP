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

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
    /*  @struct: SetupMethod
        @param: _derivedType (type which inherits this class)
        * creates a lambda to perform call on the registered functor.
        * adds it to the functor-container, maintains the already added functor set as well.
        * deriving classes is MethodContainer<methodQ::NonConst, _signature...> &
          MethodContainer<methodQ::Const, _signature...>, which must implement -
            - std::size_t& _derived::getContainerId();
            - std::string _derivedType::getSignatureStr();
            - std::size_t& _derived::pushBack(std::function < access::RObject (error&, const rtl::access::RObject&, _signature...) >,
                                              std::function<const std::size_t()>,
                                              std::function<void(const std::size_t&)>);
        * sets up only non-static-member-function functors in lambda table.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupMethod
        {
            template<class ..._signature>
            using MethodLambda = std::function < access::RObject(error&, const rtl::access::RObject&, _signature...) >;

            template<class _recordType, class _returnType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...));

            template<class _recordType, class _returnType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...) const);
            
        protected:

            template<class _recordType, class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(_recordType::* pFunctor)(_signature...));

            template<class _recordType, class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(_recordType::* pFunctor)(_signature...) const);
        };
    }
}
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
    /*  @struct: SetupFunction
        @param: _derivedType (type which inherits this class)
        * creates a functor-wrapped-lambda to perform call on the registered functor.
        * adds it to the functor-container, maintains the already added functor set as well.
        * deriving classes is FunctorContainer<...>, which must implement -
            - std::size_t& _derived::getContainerId();
            - std::string _derivedType::getSignatureStr();
            - std::size_t& _derived::pushBack(std::function<access::RObject(error&, _signature...)>,
                                              std::function<const std::size_t()>,
                                              std::function<void(const std::size_t&)>);
        * sets up only non-member or static-member-function functors in table.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupFunction
        {
            template<class ..._signature>
            using FunctionLambda = std::function < access::RObject(error&, _signature...) >;

            template<class _returnType, class ..._signature>
            static FunctionLambda<_signature...> getCaller(_returnType(*pFunctor)(_signature...));

        protected:

            template<class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(*pFunctor)(_signature...), std::size_t pRecordId);
        };
    }
}
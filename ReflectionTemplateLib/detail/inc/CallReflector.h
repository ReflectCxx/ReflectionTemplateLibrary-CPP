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

#include <optional>
#include "RObject.h"
#include "Constants.h"

namespace rtl {

    namespace detail
    {
    /*  @struct: CallReflector
        @param: _derivedType (type which inherits this class)
        * retrieves the lambda at given index and calls it with the arguments supplied.
        * deriving classes are, MethodContainer & FunctorContainer.
    */  template<class _derivedType>
        struct CallReflector
        {
        /*  @method: forwardCall
            @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
            * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
            * this 'forwardCall' is for calling lambda containing non-member-function and static-member-function functors.
        */  template<class ..._params>
            static access::RObject forwardCall(error& pError, std::size_t pFunctorIndex, _params&&..._args)
            {
                //'getFunctors()' must be implemented by _derivedType (FunctorContainer).
                return _derivedType::getFunctors().at(pFunctorIndex)(pError, std::forward<_params>(_args)...);
            }


        /*  @method: forwardCall
            @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
            * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
            * this 'forwardCall' is for calling lambda containing constructors.
        */  template<class ..._params>
            static access::RObject forwardCall(error& pError, rtl::alloc&& pAllocType, std::size_t pFunctorIndex, _params&&..._args)
            {
                //'getFunctors()' must be implemented by _derivedType (FunctorContainer).
                return _derivedType::getFunctors().at(pFunctorIndex)(pError, std::forward<rtl::alloc>(pAllocType), std::forward<_params>(_args)...);
            }


        /*  @method: forwardCall
            @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
            * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
            * this 'forwardCall' is for calling lambda containing member-function functors.
        */  template<class ..._params>
            static access::RObject forwardCall(error& pError, const rtl::access::RObject& pTarget, std::size_t pFunctorIndex, _params&&..._args)
            {
                //'getMethodFunctors()' is implemented by _derivedType (MethodContainer)
                return _derivedType::getMethodFunctors().at(pFunctorIndex)(pError, pTarget, std::forward<_params>(_args)...);
            }
        };
    }
}
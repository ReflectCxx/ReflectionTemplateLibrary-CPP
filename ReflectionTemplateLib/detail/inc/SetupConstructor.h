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
    /*  @struct: SetupConstructor
        @param: _derivedType ('FunctorContainer')
        * creates a constructor-call-wrapped-lambda to perform constructor call.
        * adds it to the functor-container, maintains the already added constructor set as well.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupConstructor
        {	
        protected:

            //adds the lambda, wrapping constructor call, recordType(_signature...), to '_derivedType' (FunctorContainer)
            template<class _recordType, class ..._signature>
            static const detail::FunctorId addConstructor();
        };
    }
}
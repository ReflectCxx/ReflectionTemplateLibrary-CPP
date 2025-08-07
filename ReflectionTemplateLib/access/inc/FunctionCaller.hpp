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

#include "RObject.h"
#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

namespace rtl
{
    namespace access
    {
        class RObject;

        template<class ..._signature>
        //FunctionCaller, holds only 'Method' associated with a static-member-function.
        inline FunctionCaller<_signature...>::FunctionCaller(const Function& pFunction)
            :m_function(pFunction) {
        }

        template<class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> rtl::access::FunctionCaller<_signature...>::call(_args&&...params) const noexcept
        {
            using Container = std::conditional_t<sizeof...(_signature) == 0,
                                                 detail::FunctorContainer<std::remove_reference_t<_args>...>,
                                                 detail::FunctorContainer<_signature...>>;

            std::size_t index = m_function.hasSignatureId(Container::getContainerId());
            if (index != rtl::index_none) {

                error err = error::None;
                return { err, Container::template forwardCall<_args...>(err, index, std::forward<_args>(params)...) };
            }

            return { error::SignatureMismatch, RObject{} };
        }
    }
}
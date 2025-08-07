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
#include "Method.h"
#include "MethodInvoker.hpp"

namespace rtl
{
    namespace access
    {
        template<class ..._signature>
        inline const MethodInvoker<_signature...> Method::bind(const RObject& pTarget) const
        {
            return MethodInvoker<_signature...>(*this, pTarget);
        }


        template<methodQ _Q, class ..._signature>
        inline const MethodInvokerQ<_Q, _signature...> Method::bind(const RObject& pTarget) const
        {
            static_assert(_Q != methodQ::None, "Invalid method-qualifier, use 'Const' or 'NonConst'");
            return MethodInvokerQ<_Q, _signature...>(*this, pTarget);
        }


    /*  @method: invokeCtor()
        @params: variable arguments.
        @return: RStatus
        * calls the constructor with given arguments.
    */  template<class ..._args>
        inline std::pair<error, RObject> Method::invokeCtor(alloc&& pAllocType, _args&& ...params) const
        {
            return Function::bind().call<alloc, _args...>(std::forward<alloc>(pAllocType), std::forward<_args>(params)...);
        }


    /*  @method: hasSignature<...>()
        @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
        @return: bool
        * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
    */  template<class ..._args>
        inline bool Method::hasSignature() const
        {
            switch (getQualifier())
            {
                case methodQ::None: {
                    return Function::hasSignature<_args...>();
                }
                case methodQ::NonConst: {
                    using Container = detail::MethodContainer<methodQ::NonConst, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
                case methodQ::Const: {
                    using Container = detail::MethodContainer<methodQ::Const, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
            }
            return false;
        }
    }
}
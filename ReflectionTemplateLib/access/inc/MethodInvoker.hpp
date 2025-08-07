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
#include "RObject.h"
#include "MethodInvoker.h"
#include "MethodContainer.h"

namespace rtl 
{
    namespace access
    {
        //MethodInvoker, holds const-ref of the 'Method' and 'RObject' on which it will be invoked.
        template<class ..._signature>
        inline MethodInvoker<_signature...>::MethodInvoker(const Method& pMethod, const RObject& pTarget)
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RObject, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
    */  template<class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> MethodInvoker<_signature...>::call(_args&& ...params) const noexcept
        {
            //Only static-member-functions have Qualifier- 'methodQ::None'
            if (m_method.getQualifier() == methodQ::None) {
                return static_cast<Function>(m_method).bind().call(std::forward<_args>(params)...);
            }

            if (m_target.isEmpty()) {
                //if the target is empty.
                return { error::EmptyRObject, RObject() };
            }
            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
                //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return { error::MethodTargetMismatch, RObject() };
            }
            if constexpr (sizeof...(_signature) == 0) {
                error err = error::None;
                return { err, Invoker<traits::remove_const_n_reference<_args>...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
            else {
                error err = error::None;
                return { err, Invoker<_signature...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
        }


        // Invoker struct's static method definition
        template<class ..._signature>
        template<class ..._finalSignature>
        template<class ..._args>
        inline RObject MethodInvoker<_signature...>::Invoker<_finalSignature...>::invoke(error& pError,
                                                                                         const Method& pMethod,
                                                                                         const RObject& pTarget,
                                                                                         _args&&... params)
        {
            if (pMethod.getQualifier() == methodQ::NonConst && pTarget.isConst()) {
                pError = error::ImplicitCallToNonConstOnConstTarget;
                return RObject();
            }

            using containerConst = detail::MethodContainer<methodQ::Const, _finalSignature...>;
            using containerNonConst = detail::MethodContainer<methodQ::NonConst, _finalSignature...>;

            std::size_t constMethodIndex = pMethod.hasSignatureId(containerConst::getContainerId());
            std::size_t nonConstMethodIndex = pMethod.hasSignatureId(containerNonConst::getContainerId());

            if (constMethodIndex != rtl::index_none && nonConstMethodIndex != rtl::index_none) {
                pError = error::AmbiguousConstOverload;
            }
            else if (constMethodIndex != rtl::index_none) {
                return containerConst::template forwardCall<_args...>(pError, pTarget, constMethodIndex, std::forward<_args>(params)...);
            }
            else if (nonConstMethodIndex != rtl::index_none) {
                return containerNonConst::template forwardCall<_args...>(pError, pTarget, nonConstMethodIndex, std::forward<_args>(params)...);
            }
            else {
                pError = error::SignatureMismatch;
            }
            return RObject();
        }
    }


    namespace access
    {
        //MethodInvokerQ, holds const-ref of the 'Method' and 'RObject' on which it will be invoked.
        template<methodQ _Q, class ..._signature>
        inline MethodInvokerQ<_Q, _signature...>::MethodInvokerQ(const Method& pMethod, const RObject& pTarget)
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RObject, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
    */  template<methodQ _Q, class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> MethodInvokerQ<_Q, _signature...>::call(_args&& ...params) const noexcept
        {
            if (m_method.getQualifier() == methodQ::None) {
                return static_cast<Function>(m_method).bind().call(std::forward<_args>(params)...);
            }

            if (m_target.isEmpty()) {
                //if the target is empty.
                return { error::EmptyRObject, RObject() };
            }
            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
                //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return { error::MethodTargetMismatch, RObject() };
            }
            if constexpr (sizeof...(_signature) == 0) {
                error err = error::None;
                return { err, Invoker<traits::remove_const_n_reference<_args>...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
            else {
                error err = error::None;
                return { err, Invoker<_signature...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
        }


        // Invoker struct's static method definition
        template<methodQ _Q, class ..._signature>
        template<class ..._finalSignature>
        template<class ..._args>
        inline RObject MethodInvokerQ<_Q, _signature...>::Invoker<_finalSignature...>::invoke(error& pError,
                                                                                              const Method& pMethod,
                                                                                              const RObject& pTarget,
                                                                                              _args&&... params)
        {
            static_assert(_Q != methodQ::None, "Invalid qualifier used.");

            using container0 = detail::MethodContainer<_Q, _finalSignature...>;
            const std::size_t index = pMethod.hasSignatureId(container0::getContainerId());
            if (index != rtl::index_none) {
                return container0::template forwardCall<_args...>(pError, pTarget, index, std::forward<_args>(params)...);
            }
            else {
                if constexpr (_Q == methodQ::Const) {
                    using container1 = detail::MethodContainer<methodQ::NonConst, _finalSignature...>;
                    std::size_t index = pMethod.hasSignatureId(container1::getContainerId());
                    if (index != rtl::index_none) {
                        pError = error::ConstMethodOverloadNotFound;
                        return RObject();
                    }
                }
                else if constexpr (_Q == methodQ::NonConst) {
                    using container2 = detail::MethodContainer<methodQ::Const, _finalSignature...>;
                    std::size_t index = pMethod.hasSignatureId(container2::getContainerId());
                    if (index != rtl::index_none) {
                        pError = error::NonConstMethodOverloadNotFound;
                        return RObject();
                    }
                }
                pError = error::SignatureMismatch;
                return RObject();
            }
        }
    }
}
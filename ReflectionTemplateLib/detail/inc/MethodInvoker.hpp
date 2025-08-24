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

#include "Method.h"
#include "RObject.h"
#include "MethodInvoker.h"
#include "MethodContainer.h"

namespace rtl::detail
{
    //MethodInvoker, holds const-ref of the 'access::Method' and 'access::RObject' on which it will be invoked.
    template<class ..._signature>
    inline MethodInvoker<_signature...>::MethodInvoker(const access::Method& pMethod, const access::RObject& pTarget)
        : m_method(pMethod)
        , m_target(pTarget) {
    }


/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: access::RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    inline std::pair<error, access::RObject> MethodInvoker<_signature...>::call(_args&& ...params) const noexcept
    {
        //Only static-member-functions have Qualifier- 'methodQ::None'
        if (m_method.getQualifier() == methodQ::None) {
            return static_cast<access::Function>(m_method).bind().call(std::forward<_args>(params)...);
        }

        if (m_target.isEmpty()) {
            //if the target is empty.
            return { error::EmptyRObject, access::RObject() };
        }
        if (m_target.getTypeId() != m_method.getRecordTypeId()) {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, access::RObject() };
        }
        if constexpr (sizeof...(_signature) == 0) {
            // executes when bind doesn't have any explicit signature types specified. (e.g. perfect-forwaring)
            error err = error::None;
            return { err, Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
        }
        else {
            error err = error::None;
            return { err, Invoker<_signature...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
        }
    }


    // Invoker struct's static method definition
    template<class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    inline access::RObject MethodInvoker<_signature...>::Invoker<_invokSignature...>::invoke(error& pError,
                                                                                             const access::Method& pMethod,
                                                                                             const access::RObject& pTarget,
                                                                                             _args&&... params)
    {
        using containerConst = detail::MethodContainer<methodQ::Const, _invokSignature...>;
        std::size_t constMethodIndex = pMethod.hasSignatureId(containerConst::getContainerId());

        if (constMethodIndex != rtl::index_none)
        {
            return containerConst::template forwardCall<_args...>(pError, pTarget, constMethodIndex, std::forward<_args>(params)...);
        }
        else
        {
            using containerNonConst = detail::MethodContainer<methodQ::NonConst, _invokSignature...>;
            std::size_t nonConstMethodIndex = pMethod.hasSignatureId(containerNonConst::getContainerId());

            if (nonConstMethodIndex != rtl::index_none) 
            {
                if (pMethod.getQualifier() == methodQ::NonConst && !pTarget.isConstCastSafe()) {
                    pError = error::ConstCallViolation;
                    return access::RObject();
                }
                return containerNonConst::template forwardCall<_args...>(pError, pTarget, nonConstMethodIndex, std::forward<_args>(params)...);
            }
            else {
                pError = error::SignatureMismatch;
            }
        }
        return access::RObject();
    }
}


namespace rtl::detail
{
    //MethodInvokerQ, holds const-ref of the 'access::Method' and 'access::RObject' on which it will be invoked.
    template<methodQ _Q, class ..._signature>
    inline MethodInvokerQ<_Q, _signature...>::MethodInvokerQ(const access::Method& pMethod, const access::RObject& pTarget)
        : m_method(pMethod)
        , m_target(pTarget) {
    }


/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: access::RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<methodQ _Q, class ..._signature>
    template<class ..._args>
    inline std::pair<error, access::RObject> MethodInvokerQ<_Q, _signature...>::call(_args&& ...params) const noexcept
    {
        if (m_method.getQualifier() == methodQ::None) {
            return static_cast<access::Function>(m_method).bind().call(std::forward<_args>(params)...);
        }

        if (m_target.isEmpty()) {
            //if the target is empty.
            return { error::EmptyRObject, access::RObject() };
        }
        if (m_target.getTypeId() != m_method.getRecordTypeId()) {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, access::RObject() };
        }
        if constexpr (sizeof...(_signature) == 0) {
            error err = error::None;
            return { err, Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
        }
        else {
            error err = error::None;
            return { err, Invoker<_signature...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
        }
    }


    // Invoker struct's static method definition
    template<methodQ _Q, class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    inline access::RObject MethodInvokerQ<_Q, _signature...>::Invoker<_invokSignature...>::invoke(error& pError,
                                                                                                  const access::Method& pMethod,
                                                                                                  const access::RObject& pTarget,
                                                                                                  _args&&... params)
    {

        if constexpr (_Q == methodQ::Const)
        {
            pError = error::ConstOverloadMissing;
            return access::RObject();
        }

        using container0 = detail::MethodContainer<methodQ::NonConst, _invokSignature...>;
        const std::size_t index = pMethod.hasSignatureId(container0::getContainerId());
        if (index != rtl::index_none) {
            return container0::template forwardCall<_args...>(pError, pTarget, index, std::forward<_args>(params)...);
        }
        else 
        {
            // check if the const-overload method is present.
            using container2 = detail::MethodContainer<methodQ::Const, _invokSignature...>;
            std::size_t index = pMethod.hasSignatureId(container2::getContainerId());
            if (index != rtl::index_none) {
                // So, const-overload is present and non-const overload is not registered or doesn't exists.
                pError = error::NonConstOverloadMissing;
                return access::RObject();
            }
            // else the signature might be wrong.
            pError = error::SignatureMismatch;
            return access::RObject();
        }
    }
}
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
    //DefaultInvoker, holds const-ref of the 'Method' and 'RObject' on which it will be invoked.
    template<class ..._signature>
    inline DefaultInvoker<_signature...>::DefaultInvoker(const Method& pMethod, const RObject& pTarget)
        : m_method(pMethod)
        , m_target(pTarget) {
    }


/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    inline Return DefaultInvoker<_signature...>::call(_args&& ...params) const noexcept
    {
        //Only static-member-functions have Qualifier- 'methodQ::None'
        if (m_method.getQualifier() == methodQ::None) {
            return static_cast<Function>(m_method).bind().call(std::forward<_args>(params)...);
        }
        if (m_target.isEmpty()) {
            //if the target is empty.
            return { error::EmptyRObject, RObject{ } };
        }
        if (m_target.getTypeId() != m_method.getRecordTypeId()) {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, RObject{ } };
        }
        if constexpr (sizeof...(_signature) == 0) {
            // executes when bind doesn't have any explicit signature types specified. (e.g. perfect-forwaring)
            return Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(m_method, m_target, std::forward<_args>(params)...);
        }
        else {
            return Invoker<_signature...>::invoke(m_method, m_target, std::forward<_args>(params)...);
        }
    }


    // Invoker struct's static method definition
    template<class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    inline Return 
    DefaultInvoker<_signature...>::Invoker<_invokSignature...>::invoke(const Method& pMethod,
                                                                       const RObject& pTarget,
                                                                       _args&&... params)
    {
        using containerConst = detail::MethodContainer<detail::methodQ::Const, _invokSignature...>;
        std::size_t constMethodIndex = pMethod.hasSignatureId(containerConst::getContainerId());

        if (constMethodIndex != rtl::index_none)
        {
            return containerConst::template forwardCall<_args...>(pTarget, constMethodIndex, std::forward<_args>(params)...);
        }
        else
        {
            using containerNonConst = detail::MethodContainer<detail::methodQ::NonConst, _invokSignature...>;
            std::size_t nonConstMethodIndex = pMethod.hasSignatureId(containerNonConst::getContainerId());

            if (nonConstMethodIndex != rtl::index_none) 
            {
                if (!pTarget.isConstCastSafe()) {
                    return { error::ConstOverloadMissing, RObject{} };
                }
                return containerNonConst::template forwardCall<_args...>(pTarget, nonConstMethodIndex, std::forward<_args>(params)...);
            }
        }
        return { error::SignatureMismatch, RObject{} };
    }
}


namespace rtl::detail
{
    //NonConstInvoker, holds const-ref of the 'Method' and 'RObject' on which it will be invoked.
    template<class ..._signature>
    inline NonConstInvoker<_signature...>::NonConstInvoker(const Method& pMethod, const RObject& pTarget)
        : m_method(pMethod)
        , m_target(pTarget) {
    }


/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    inline Return NonConstInvoker<_signature...>::call(_args&& ...params) const noexcept
    {
        if (m_method.getQualifier() == methodQ::None) {
            return static_cast<Function>(m_method).bind().call(std::forward<_args>(params)...);
        }
        if (m_target.isEmpty()) {
            //if the target is empty.
            return { error::EmptyRObject, RObject{} };
        }
        if (m_target.getTypeId() != m_method.getRecordTypeId()) {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, RObject{} };
        }
        if constexpr (sizeof...(_signature) == 0) {
            return Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(m_method, m_target, std::forward<_args>(params)...);
        }
        else {
            return Invoker<_signature...>::invoke(m_method, m_target, std::forward<_args>(params)...);
        }
    }


    // Invoker struct's static method definition
    template<class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    inline Return
    NonConstInvoker<_signature...>::Invoker<_invokSignature...>::invoke(const Method& pMethod,
                                                                        const RObject& pTarget,
                                                                        _args&&... params)
    {
        using container0 = detail::MethodContainer<detail::methodQ::NonConst, _invokSignature...>;
        const std::size_t index = pMethod.hasSignatureId(container0::getContainerId());
        if (index != rtl::index_none) {
            return container0::template forwardCall<_args...>(pTarget, index, std::forward<_args>(params)...);
        }
        else 
        {
            // check if the const-overload method is present.
            using container2 = detail::MethodContainer<detail::methodQ::Const, _invokSignature...>;
            std::size_t index = pMethod.hasSignatureId(container2::getContainerId());
            if (index != rtl::index_none) {
                // So, const-overload is present and non-const overload is not registered or doesn't exists.
                return { error::NonConstOverloadMissing, RObject{} };
            }
            // else the signature might be wrong.
            return { error::SignatureMismatch , RObject{} };
        }
    }
}
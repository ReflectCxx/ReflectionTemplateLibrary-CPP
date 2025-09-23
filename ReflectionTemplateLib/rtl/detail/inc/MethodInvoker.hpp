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
/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    FORCE_INLINE Return DefaultInvoker<_signature...>::call(_args&& ...params) const noexcept
    {
        //Only static-member-functions have Qualifier- 'methodQ::None'
        if (m_method->getQualifier() == methodQ::None) [[unlikely]] {
            return static_cast<Function>(*m_method).bind().call(std::forward<_args>(params)...);
        }
        else if (m_target->isEmpty()) [[unlikely]] {
            //if the target is empty.
            return { error::EmptyRObject, RObject{} };
        }
        else if (m_target->getTypeId() != m_method->getRecordTypeId()) [[unlikely]] {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, RObject{} };
        }
        else [[likely]]
        {
            if constexpr (sizeof...(_signature) == 0) {
                // executes when bind doesn't have any explicit signature types specified. (e.g. perfect-forwaring)
                return Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
            }
            else {
                return Invoker<_signature...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
            }
        }
    }


    // Invoker struct's static method definition
    template<class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    FORCE_INLINE Return
    DefaultInvoker<_signature...>::Invoker<_invokSignature...>::invoke(const Method& pMethod,
                                                                       const RObject& pTarget,
                                                                       _args&&... params)
    {
        using containerConst = detail::MethodContainer<detail::methodQ::Const, _invokSignature...>;
        const FunctorId* constFunctorId = pMethod.hasFunctorId(containerConst::getContainerId());

        if (constFunctorId != nullptr) [[likely]]
        {
            return containerConst::template forwardCall<_args...>(*constFunctorId, pTarget, std::forward<_args>(params)...);
        }
        else [[unlikely]]
        {
            using containerNonConst = detail::MethodContainer<detail::methodQ::NonConst, _invokSignature...>;
            const FunctorId* functorId = pMethod.hasFunctorId(containerNonConst::getContainerId());

            if (functorId != nullptr)
            {
                if (!pTarget.isConstCastSafe()) {
                    return { error::ConstOverloadMissing, RObject{} };
                }
                return containerNonConst::template forwardCall<_args...>(*functorId, pTarget, std::forward<_args>(params)...);
            }
        }
        return { error::SignatureMismatch, RObject{} };
    }
}


namespace rtl::detail
{
/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    FORCE_INLINE Return NonConstInvoker<_signature...>::call(_args&& ...params) const noexcept
    {
        if (m_method->getQualifier() == methodQ::None) [[unlikely]] {
            return static_cast<Function>(*m_method).bind().call(std::forward<_args>(params)...);
        }
        else if (m_target->isEmpty()) [[unlikely]] {
            //if the target is empty.
            return { error::EmptyRObject, RObject{} };
        }
        else if (m_target->getTypeId() != m_method->getRecordTypeId()) [[unlikely]] {
            //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
            return { error::TargetMismatch, RObject{} };
        }
        else [[likely]]
        {
            if constexpr (sizeof...(_signature) == 0) {
                return Invoker<traits::remove_const_n_ref_t<_args>...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
            }
            else {
                return Invoker<_signature...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
            }
        }
    }


    // Invoker struct's static method definition
    template<class ..._signature>
    template<class ..._invokSignature>
    template<class ..._args>
    FORCE_INLINE Return
    NonConstInvoker<_signature...>::Invoker<_invokSignature...>::invoke(const Method& pMethod,
                                                                        const RObject& pTarget,
                                                                        _args&&... params)
    {
        using container0 = detail::MethodContainer<detail::methodQ::NonConst, _invokSignature...>;
        const FunctorId* functorId = pMethod.hasFunctorId(container0::getContainerId());

        if (functorId != nullptr) [[likely]] {
            return container0::template forwardCall<_args...>(*functorId, pTarget, std::forward<_args>(params)...);
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


namespace rtl::detail
{
    template<class _recordType>
    template<class ..._signature>
    const Hopper<_recordType>::Build<_signature...> Hopper<_recordType>::argsT() const
    {
        for (auto& functorId : m_functorIds)
        {
            if (functorId.m_lambda->is_member<_recordType>() &&
                functorId.m_lambda->is_signature<_signature...>()) [[likely]]
            {
                return { functorId.get_lambda_method<_recordType, _signature...>() };
            }
        }
        return Build<_signature...>();
    }


    template<class _recordType>
    template<class ..._signature>
    template<class _returnType>
    inline constexpr const method<_returnType(_recordType::*)(_signature...)> Hopper<_recordType>::Build<_signature...>::returnT() const
    {
        if (m_lambda != nullptr && m_lambda->template is_returning<_returnType>()) {
            return m_lambda->template get_hopper<_returnType>();
        }
        return method<_returnType(_recordType::*)(_signature...)>();
    }
}
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
#include "erased_hopper_rec.h"

namespace rtl::detail
{
/*  @method: call()
    @params: params... (corresponding to functor associated with 'm_method')
    @return: RObject, indicating success of the reflected call.
    * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
*/  template<class ..._signature>
    template<class ..._args>
    ForceInline Return DefaultInvoker<_signature...>::call(_args&& ...params) const noexcept
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
                return Invoker<traits::remove_cref_t<_args>...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
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
    ForceInline Return
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
    ForceInline Return NonConstInvoker<_signature...>::call(_args&& ...params) const noexcept
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
                return Invoker<traits::remove_cref_t<_args>...>::invoke(*m_method, *m_target, std::forward<_args>(params)...);
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
    ForceInline Return
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
            return { error::SignatureMismatch, RObject{} };
        }
    }
}


namespace rtl::detail
{
    template<class record_t>
    template<class ...args_t>
    inline constexpr HopMethod<record_t, args_t...> Hopper<record_t>::argsT() const
    {
        auto recordId = traits::uid<record_t>::value;
        auto strictArgsId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        auto normalArgsId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;

        const dispatch::lambda_method<record_t, args_t...>* lambda_fn = nullptr;
        std::vector<const dispatch::lambda_base*> refOverloads = { nullptr };

        for (auto& functorId : m_functorIds)
        {
            auto& lambda = functorId.get_lambda();
            if (recordId != lambda.get_record_id()) {
                continue;
            }
            if (!lambda_fn && strictArgsId == lambda.get_strict_sign_id()) {
                lambda_fn = &(lambda.to_method<record_t, args_t...>());
            }
            if (normalArgsId == lambda.get_normal_sign_id())
            {
                if (normalArgsId == lambda.get_strict_sign_id()) {
                    refOverloads[0] = &lambda;
                }
                else if (!lambda.is_any_ncref()) {
                    refOverloads.push_back(&lambda);
                }
            }
        }
        for (auto& functorId : m_functorIds)
        {
            auto& lambda = functorId.get_lambda();
            if (recordId == lambda.get_record_id() && 
                normalArgsId == lambda.get_normal_sign_id() && lambda.is_any_ncref()) {
                refOverloads.push_back(&lambda);
            }
        }
        return { lambda_fn, refOverloads };
    }


    template<class record_t, class ...args_t>
    template<class _returnType> requires (std::is_const_v<record_t> == false)
    inline constexpr const method<_returnType(record_t::*)(args_t...)>
                                       HopMethod<record_t, args_t...>::returnT() const
    {
        if (m_lambda != nullptr) [[likely]]
        {
            const auto retId = traits::uid<_returnType>::value;
            return m_lambda->template get_hopper<_returnType>(retId);
        }
        return method<_returnType(record_t::*)(args_t...)>();
    }


    template<class record_t, class ...args_t>
    template<class _returnType> requires (std::is_const_v<record_t> == true)
    inline constexpr const method<_returnType(record_t::*)(args_t...) const> 
                                       HopMethod<record_t, args_t...>::returnT() const
    {
        if (m_lambda != nullptr) [[likely]]
        {
            const auto retId = traits::uid<_returnType>::value;
            return m_lambda->template get_hopper<_returnType>(retId);
        }
        return method<_returnType(record_t::*)(args_t...) const>();
    }
}


namespace rtl::detail 
{
    template<class record_t>
    template<class ...argsT> requires (std::is_same_v<traits::raw_t<record_t>, RObject> == false)
    ForceInline constexpr Return ErasedInvoker<record_t>::operator()(argsT&&...params) const noexcept
    {
        return { error::InvalidCaller, RObject{} };

        auto functorId = m_method.getLambdaByNormalId(traits::uid<traits::normal_sign_id_t<argsT...>>::value);
        if (functorId.first) [[likely]]
        {
            const auto& erased = functorId.first->m_lambda->get_unerasure();
            const auto& caller = erased.template to_erased_return_rec<record_t, argsT...>();
            //if(functorId.first->m_lambda->is_void())
            //{
            //    caller.hop_void(m_target, std::forward<argsT>(params)...);
                return { error::None, RObject{} };
            //}
            //else
            //{
            //    return{ error::None,
            //            RObject{ caller.hop_return(m_target, std::forward<argsT>(params)...),
            //                     caller.get_return_id(), nullptr }
            //        };
            //}
        }
        else [[unlikely]] {
            return { (functorId.second ? error::ExplicitRefBindingRequired:error::SignatureMismatch), RObject{} };
        }
    }


    template<class record_t>
    template<class ...argsT> requires (std::is_same_v<traits::raw_t<record_t>, RObject> == true)
    ForceInline constexpr Return ErasedInvoker<record_t>::operator()(argsT&&...params) const noexcept
    {
        return { error::InvalidCaller, RObject{} };

        auto functorId = m_method.getLambdaByNormalId(traits::uid<traits::normal_sign_id_t<argsT...>>::value);
        if (functorId.first) [[likely]]
        {
            const auto& erased = functorId.first->m_lambda->get_unerasure();
            const auto& caller = erased.template to_erased_return<argsT...>();
            //if (functorId.first->m_lambda->is_void())
            //{
            //    caller.hop_void(m_target, std::forward<argsT>(params)...);
                return { error::None, RObject{} };
            //}
            //else
            //{
            //    return{ error::None,
            //            RObject{ caller.hop_return(m_target, std::forward<argsT>(params)...),
            //                     caller.get_return_id(), nullptr }
            //    };
            //}
        }
        else return { (functorId.second ? error::ExplicitRefBindingRequired:error::SignatureMismatch), RObject{} };
    }
}
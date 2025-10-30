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
#include "erasure_base.h"


#include "erasure_base.hpp"
#include "rtl_method_erased.h"
#include "rtl_method_erased_target.h"
#include "rtl_method_erased_return.h"

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
        //Only static-member-functions have Qualifier- 'member::None'
        if (m_method->getQualifier() == member::None) [[unlikely]] {
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
        using containerConst = detail::MethodContainer<detail::member::Const, _invokSignature...>;
        const FunctorId* constFunctorId = pMethod.hasFunctorId(containerConst::getContainerId());

        if (constFunctorId != nullptr) [[likely]]
        {
            return containerConst::template forwardCall<_args...>(*constFunctorId, pTarget, std::forward<_args>(params)...);
        }
        else [[unlikely]]
        {
            using containerNonConst = detail::MethodContainer<detail::member::NonConst, _invokSignature...>;
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
        if (m_method->getQualifier() == member::None) [[unlikely]] {
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
        using container0 = detail::MethodContainer<detail::member::NonConst, _invokSignature...>;
        const FunctorId* functorId = pMethod.hasFunctorId(container0::getContainerId());

        if (functorId != nullptr) [[likely]] {
            return container0::template forwardCall<_args...>(*functorId, pTarget, std::forward<_args>(params)...);
        }
        else 
        {
            // check if the const-overload method is present.
            using container2 = detail::MethodContainer<detail::member::Const, _invokSignature...>;
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
    template<class record_t, class ...args_t>
    template<class return_t> requires (traits::type_aware_v<record_t, return_t>)
    inline constexpr const
    method<record_t, return_t(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        if (!m_argsTfnMeta.is_empty() && m_argsTfnMeta.get_member_kind() != member::Static)
        {
            const auto retId = traits::uid<return_t>::value;
            return m_argsTfnMeta.get_lambda()
                                .template to_method<record_t, args_t...>()
                                .template get_hopper<return_t>(retId);
        }
        return method<record_t, return_t(args_t...)>();
    }


    template<class record_t, class ...args_t>
    template<class return_t> requires (traits::type_erased_v<record_t, return_t>)
    inline constexpr const
    method<RObject, Return(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        bool isReturnTvoid = false;
        method<RObject, Return(traits::normal_sign_t<args_t>...)> erasedRetHop;

        for (auto& fnMeta : m_overloadsFnMeta)
        {
            if (!fnMeta.is_empty())
            {
                auto& erasedRetFn = fnMeta.get_erasure_base()
                                          .template to_erased_record<traits::normal_sign_t<args_t>...>();
                if (fnMeta.is_void()) {
                    isReturnTvoid = true;
                    erasedRetHop.get_vhop().push_back(erasedRetFn.get_void_hopper());
                }
                else {
                    erasedRetHop.get_rhop().push_back(erasedRetFn.get_return_hopper());
                }
                erasedRetHop.get_overloads().push_back(&fnMeta.get_lambda());
            }
            else {
                erasedRetHop.get_vhop().push_back(nullptr);
                erasedRetHop.get_rhop().push_back(nullptr);
                erasedRetHop.get_overloads().push_back(nullptr);
            }
        }
        if (isReturnTvoid) {
            erasedRetHop.get_rhop().clear();
        }
        else {
            erasedRetHop.get_vhop().clear();
        }
        return erasedRetHop;
    }


    template<class record_t, class ...args_t>
    template<class return_t> requires (traits::target_erased_v<record_t, return_t>)
    inline constexpr const
    method<RObject, return_t(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        bool isReturnTvoid = false;
        method<RObject, return_t(traits::normal_sign_t<args_t>...)> erasedRetHop;

        for (auto& fnMeta : m_overloadsFnMeta)
        {
            if (!fnMeta.is_empty())
            {
                auto& erasedRetFn = fnMeta.get_erasure_base()
                                          .template to_erased_target_aware_return<return_t, traits::normal_sign_t<args_t>...>();
                if (fnMeta.is_void()) {
                    isReturnTvoid = true;
                    erasedRetHop.get_vhop().push_back(erasedRetFn.get_void_hopper());
                }
                else {
                    erasedRetHop.get_rhop().push_back(erasedRetFn.get_return_hopper());
                }
                erasedRetHop.get_overloads().push_back(&fnMeta.get_lambda());
            }
            else {
                erasedRetHop.get_vhop().push_back(nullptr);
                erasedRetHop.get_rhop().push_back(nullptr);
                erasedRetHop.get_overloads().push_back(nullptr);
            }
        }
        if (isReturnTvoid) {
            erasedRetHop.get_rhop().clear();
        }
        else {
            erasedRetHop.get_vhop().clear();
        }
        return erasedRetHop;
    }


    template<class record_t, class ...args_t>
    template<class return_t> requires (traits::return_erased_v<record_t, return_t>)
    inline constexpr const
    method<record_t, Return(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        bool isReturnTvoid = false;
        method<record_t, Return(traits::normal_sign_t<args_t>...)> erasedRetHop;

        for (auto& fnMeta : m_overloadsFnMeta)
        {
            if (!fnMeta.is_empty())
            {
                auto& erasedRetFn = fnMeta.get_erasure_base()
                                          .template to_erased_return_aware_target<record_t, traits::normal_sign_t<args_t>...>();
                if (fnMeta.is_void()) {
                    isReturnTvoid = true;
                    erasedRetHop.get_vhop().push_back(erasedRetFn.get_void_hopper());
                }
                else {
                    erasedRetHop.get_rhop().push_back(erasedRetFn.get_return_hopper());
                }
                erasedRetHop.get_overloads().push_back(&fnMeta.get_lambda());
            }
            else {
                erasedRetHop.get_vhop().push_back(nullptr);
                erasedRetHop.get_rhop().push_back(nullptr);
                erasedRetHop.get_overloads().push_back(nullptr);
            }
        }
        if (isReturnTvoid) {
            erasedRetHop.get_rhop().clear();
        }
        else {
            erasedRetHop.get_vhop().clear();
        }
        return erasedRetHop;
    }


    template<member member_kind, class record_t>
    template<class ...args_t>
    inline constexpr HopMethod<record_t, args_t...> Hopper<member_kind, record_t>::argsT() const
    {
        auto recordId = traits::uid<record_t>::value;
        auto strictArgsId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        auto normalArgsId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;

        type_meta argsTfnMeta;
        //initializing pos '0' with empty 'type_meta'.
        std::vector<type_meta> overloadsFnMeta = { type_meta() };

        for (auto& fnMeta : m_functorsMeta)
        {
            if constexpr (!std::is_same_v<record_t, RObject>)
            {
                if (recordId != fnMeta.get_record_id()) {
                    return { argsTfnMeta, overloadsFnMeta };
                }
            }

            if (argsTfnMeta.is_empty() && strictArgsId == fnMeta.get_strict_args_id()) {
                argsTfnMeta = fnMeta;
            }
            if (normalArgsId == fnMeta.get_normal_args_id())
            {
                if (normalArgsId == fnMeta.get_strict_args_id()) {
                    // same normal & strict ids, means no refs exists in target function's signature
                    // target's function signature is call by value, always at pos '0'.
                    // if doesn't exists, this pos is occupied by an empty 'type_meta'.
                    overloadsFnMeta[0] = fnMeta;
                }
                else if (!fnMeta.is_any_arg_ncref()) {
                    // its a const-ref-overload with no non-const-ref in signature, added from pos '1' onwards.
                    overloadsFnMeta.push_back(fnMeta);
                }
            }
        }

        for (auto& fnMeta : m_functorsMeta) {
            if (recordId == fnMeta.get_record_id() &&
                normalArgsId == fnMeta.get_normal_args_id() && fnMeta.is_any_arg_ncref()) {
                overloadsFnMeta.push_back(fnMeta);
            }
        }
        return { argsTfnMeta, overloadsFnMeta };
    }
}
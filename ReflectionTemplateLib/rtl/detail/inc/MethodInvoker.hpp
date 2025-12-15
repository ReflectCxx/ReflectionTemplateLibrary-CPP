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

#include "method_ptr.h"
#include "method_ptr_const.h"

#include "rtl_method.h"
#include "rtl_method_const.h"
#include "rtl_method_erased.h"
#include "rtl_method_erased_target.h"
#include "rtl_method_erased_return.h"

namespace rtl::detail
{
    /*  @lambda: call()
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


    // Invoker struct's static lambda definition
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
    /*  @lambda: call()
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


    // Invoker struct's static lambda definition
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
            // check if the const-overload lambda is present.
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
    template<class return_t> requires (!traits::type_aware_v<record_t, return_t>)
    inline constexpr const method<record_t, return_t(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        method<record_t, return_t(traits::normal_sign_t<args_t>...)> mth;
        initHopper<return_t>(mth);
        return mth;
    }


    template<class record_t, class ...args_t>
    template<class return_t> requires (traits::type_aware_v<record_t, return_t>)
    inline constexpr const method<record_t, return_t(args_t...)> HopMethod<record_t, args_t...>::returnT() const
    {
        method<record_t, return_t(args_t...)> mth;
        if (m_fnIndex == rtl::index_none) {
            mth.set_init_error(error::SignatureMismatch);
            return mth;
        }

        auto& ty_meta = m_overloadsFnMeta[m_fnIndex];
        if (ty_meta.get_member_kind() == member::Static) {
            mth.set_init_error(error::InvalidStaticMethodCaller);
        }
        else {
            if (traits::uid<return_t>::value == ty_meta.get_return_id())
            {
                using method_t = dispatch::method_ptr<record_t, return_t, args_t...>;
                auto fptr = static_cast<const method_t&>(ty_meta.get_functor()).f_ptr();
                return method<record_t, return_t(args_t...)>(fptr);
            }
            mth.set_init_error(error::ReturnTypeMismatch);
        }
        return mth;
    }


    template<member member_kind, class record_t>
    template<class ...args_t>
    inline constexpr HopMethod<record_t, args_t...> Hopper<member_kind, record_t>::argsT() const
    {
        std::size_t index = rtl::index_none; 
        std::vector<rtl::type_meta> fnTyMetas(call_by::ncref);

        auto recordId = traits::uid<record_t>::value;
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        auto strictId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;

        for (auto& ty_meta : m_functorsMeta)
        {
            if constexpr (!std::is_same_v<record_t, RObject>)
            {
                if (recordId != ty_meta.get_record_id()) {
                    return { rtl::index_none, fnTyMetas };
                }
            }
            if (normalId == ty_meta.get_normal_args_id())
            {
                if (normalId == ty_meta.get_strict_args_id()) {
                    fnTyMetas[call_by::value] = ty_meta;
                }
                else if (!ty_meta.is_any_arg_ncref()) {
                    fnTyMetas[call_by::cref] = ty_meta;
                }
                else fnTyMetas.push_back(ty_meta);
            }
        }
        for (int i = 0; i < fnTyMetas.size(); i++)
        {
            auto& ty_meta = fnTyMetas[i];
            if (!ty_meta.is_empty() && ty_meta.get_strict_args_id() == strictId) {
                index = i;
                break;
            }
        }
        return { index, fnTyMetas };
    }


    template<class record_t, class ...args_t>
    template<class return_t> requires (!traits::type_aware_v<record_t, return_t>)
    inline void HopMethod<record_t, args_t...>::initHopper(method<record_t, return_t(args_t...)>& pHopper) const
    {
        bool isReturnTvoid = false;
        for (auto& ty_meta : m_overloadsFnMeta)
        {
            if (ty_meta.is_empty())
            {
                pHopper.get_vhop().push_back(nullptr);
                pHopper.get_rhop().push_back(nullptr);
                pHopper.get_overloads().push_back(nullptr);
                continue;
            }

            if (ty_meta.get_member_kind() == member::Static) {
                pHopper.set_init_error(error::InvalidStaticMethodCaller);
                return;
            }

            auto lambda = [&]<dispatch::fn_void void_v>() -> decltype(auto)
            {
                if constexpr (traits::type_erased_v<record_t, return_t>)
                {
                    using fn_cast = dispatch::functor_cast<void_v, traits::normal_sign_t<args_t>...>;
                    return fn_cast(ty_meta.get_functor()).to_method();
                }
                else if constexpr (traits::target_erased_v<record_t, return_t>)
                {
                    using fn_cast = dispatch::functor_cast<void_v, traits::normal_sign_t<args_t>...>;
                    return fn_cast(ty_meta.get_functor()).template to_method<dispatch::erase::t_target, return_t>();
                }
                else if constexpr (traits::return_erased_v<record_t, return_t>)
                {
                    using fn_cast = dispatch::functor_cast<void_v, traits::normal_sign_t<args_t>...>;
                    return fn_cast(ty_meta.get_functor()).template to_method<dispatch::erase::t_return, record_t>();
                }
            };

            if ((isReturnTvoid = ty_meta.is_void())){
                auto fn = lambda.template operator() < dispatch::fn_void::yes > ();
                pHopper.get_vhop().push_back(fn.f_ptr());
            }
            else {
                auto fn = lambda.template operator() < dispatch::fn_void::no > ();
                pHopper.get_rhop().push_back(fn.f_ptr());
            }
            pHopper.get_overloads().push_back(&ty_meta.get_functor());
            pHopper.set_init_error(error::None);
        }

        if (isReturnTvoid) {
            pHopper.get_rhop().clear();
        }
        else {
            pHopper.get_vhop().clear();
        }
    }
}
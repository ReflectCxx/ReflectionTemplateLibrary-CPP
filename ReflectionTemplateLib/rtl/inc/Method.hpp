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
#include "MethodInvoker.hpp"

namespace rtl
{
    template<class ..._signature>
    FORCE_INLINE const detail::DefaultInvoker<_signature...> Method::bind(const RObject& pTarget) const
    {
        return detail::DefaultInvoker<_signature...>{ this, &pTarget };
    }


    template<class ..._signature>
    FORCE_INLINE const detail::NonConstInvoker<_signature...> Method::bind(constCast<RObject>&& pTarget) const
    {
        return detail::NonConstInvoker<_signature...>{ this, &pTarget.m_target };
    }


    template<class _recordType, class ..._signature>
    const Method::HopBuilder<_recordType, _signature...> Method::args_t() const
    {
        for (auto& functorId : getFunctorIds())
        {
            if (functorId.m_lambda->is_member<_recordType>() &&
                functorId.m_lambda->is_signature<_signature...>()) [[likely]] 
            {
                return { functorId.get_lambda_method<_recordType, _signature...>() };
            }
        }
        return HopBuilder<_recordType, _signature...>();
    }


    template<class _recordType, class ..._signature>
    template<class _returnType>
    inline constexpr const method_hop<_returnType (_recordType::*)(_signature...)> Method::HopBuilder<_recordType, _signature...>::return_t() const
    {
        if (m_lambda != nullptr && m_lambda->template is_returning<_returnType>()) {
            return m_lambda->template get_hopper<_returnType>();
        }
        return method_hop<_returnType (_recordType::*)(_signature...)>();
    }


/*  @method: invokeCtor()
    @params: variable arguments.
    @return: RStatus
    * calls the constructor with given arguments.
*/  template<class ..._args>
    inline Return Method::invokeCtor(alloc pAllocType, const detail::FunctorId& pClonerId, _args&& ...params) const
    {
        using Container = detail::FunctorContainer<alloc, detail::FunctorId, std::remove_reference_t<_args>...>;

        const detail::FunctorId* functorId = hasFunctorId(Container::getContainerId());
        if (functorId != nullptr) [[likely]] {
            return Container::template forwardCall<_args...>(*functorId, pAllocType, pClonerId, std::forward<_args>(params)...);
        }
        return { error::SignatureMismatch, RObject{} };
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
            case detail::methodQ::None: {
                return Function::hasSignature<_args...>();
            }
            case detail::methodQ::NonConst: {
                using Container = detail::MethodContainer<detail::methodQ::NonConst, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
            case detail::methodQ::Const: {
                using Container = detail::MethodContainer<detail::methodQ::Const, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
        }
        return false;
    }
}
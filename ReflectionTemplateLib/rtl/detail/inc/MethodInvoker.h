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

#include "rtl_typeid.h"
#include "rtl_forward_decls.h"
#include "type_meta.h"

namespace rtl::detail
{
    template<class _recordType>
    struct ErasedInvoker
    {
        const Method& m_method;

        const _recordType& m_target;

        template<class ..._args> requires (std::is_same_v<traits::raw_t<_recordType>, RObject> == false)
        constexpr Return operator()(_args&&...params) const noexcept
        {
            return { error::InvalidCaller, RObject{} };
        }
        
        template<class ..._args> requires (std::is_same_v<traits::raw_t<_recordType>, RObject> == true)
        constexpr Return operator()(_args&&...params) const noexcept
        {
            return { error::InvalidCaller, RObject{} };
        }
    };
}


namespace rtl::detail {

    template<class ..._signature>
    struct DefaultInvoker
    {
        //the method to be called.
        const Method* m_method;

        //the object on which, the method needs to be called.
        const RObject* m_target;

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static Return invoke(const Method& pMethod, const RObject& pTarget, _args&&...);
        };

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }
    };


    template<class ..._signature>
    struct NonConstInvoker
    {
        //the method to be called.
        const Method* m_method;

        //the object on which, the method needs to be called.
        const RObject* m_target;

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static Return invoke(const Method& pMethod, const RObject& pTarget, _args&&...);
        };

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }
    };
}


namespace rtl::detail
{
    template<member member_kind, class record_t, class ...signature_t>
    struct HopMethod
    {
        std::size_t m_fnIndex;

        traits::uid_t m_recordId;

        std::vector<rtl::type_meta> m_overloadsFnMeta = {};

        template<class return_t>
        using method_t = std::conditional_t< member_kind == member::Const,
                                             const_method<record_t, return_t(signature_t...)>,
                                             method<record_t, return_t(signature_t...)> >;

        template<class return_t> requires (traits::type_aware_v<record_t, return_t>)
        constexpr const method_t<return_t> returnT() const;

        template<class return_t = rtl::Return> requires (!traits::type_aware_v<record_t, return_t>)
        constexpr const method<record_t, return_t(signature_t...)> returnT() const;

        template<class return_t> requires (!traits::type_aware_v<record_t, return_t>)
        void initHopper(method<record_t, return_t(signature_t...)>& pMth) const;
    };

    template<member member_kind, class record_t>
    struct Hopper
    {
        const traits::uid_t m_recordId;

        const std::vector<rtl::type_meta>& m_functorsMeta;

        template<class ...signature_t>
        constexpr HopMethod<member_kind, record_t, signature_t...> argsT() const;
    };
}
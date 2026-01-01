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

#include "Builder.h"

namespace rtl::builder
{
    template<class _recordType>
    class RecordBuilder;

    template<class _recordType>
    class MethodBuilder;
}


namespace rtl
{
/*  @class: Reflect
    * provides interface to register all kinds of functions (member/non-member).
*/  struct type_ns
    {
        type_ns() = delete;
        type_ns(type_ns&&) = delete;
        type_ns(const type_ns&) = delete;
        type_ns& operator=(type_ns&&) = delete;
        type_ns& operator=(const type_ns&) = delete;

        type_ns(const std::string& pNamespace);

        template<class _recordType>
        constexpr const builder::RecordBuilder<_recordType> record(const std::string& pClass);

        template<class ..._signature>
        constexpr const builder::Builder<detail::member::None, _signature...> function(const std::string& pFunction);

    private:

        //name of the class, struct being registered.
        std::string m_recordStr;

        //name of the namespace being registered.
        std::string m_namespaceStr;
    };



/*  @class: Reflect
    * provides interface to register all kinds of functions (member/non-member).
*/  struct type
    {
        type() = default;
        type(type&&) = delete;
        type(const type&) = delete;
        type& operator=(type&&) = delete;
        type& operator=(const type&) = delete;

        type_ns ns(const std::string& pNamespace);

        template<class _recordType>
        constexpr const builder::MethodBuilder<_recordType> member() {
            return builder::MethodBuilder<_recordType>();
        }

        template<class _recordType>
        constexpr const builder::RecordBuilder<_recordType> record(const std::string& pClass) {
            return ns(detail::NAMESPACE_GLOBAL).record<_recordType>(pClass);
        }

        template<class ..._signature>
        constexpr const builder::Builder<detail::member::None, _signature...> function(const std::string& pFunction) 
        {
            constexpr bool hasConstRValueRef = ((std::is_const_v<std::remove_reference_t<_signature>> && std::is_rvalue_reference_v<_signature>) || ...);
            static_assert(!hasConstRValueRef, "Registration of functions with 'const T&&' parameters is not allowed.");

            return ns(detail::NAMESPACE_GLOBAL).function<_signature...>(pFunction);
        }
    };
}
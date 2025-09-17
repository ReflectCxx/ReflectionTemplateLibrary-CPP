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

#include <string>
#include "rtl_constants.h"
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

        type_ns(const std::string_view pNamespace);

        template<class _recordType>
        constexpr const builder::RecordBuilder<_recordType> record(const std::string_view pClass);

        template<class ..._signature>
        constexpr const builder::Builder<detail::methodQ::None, _signature...> function(const std::string_view pFunction);

    private:

        //name of the class, struct being registered.
        std::string_view m_record;

        //name of the namespace being registered.
        std::string_view m_namespace;
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

        type_ns ns(const std::string_view pNamespace = detail::NAMESPACE_GLOBAL);

        template<class _recordType>
        constexpr const builder::MethodBuilder<_recordType> member() {
            return builder::MethodBuilder<_recordType>();
        }

        template<class _recordType>
        constexpr const builder::RecordBuilder<_recordType> record(const std::string_view pClass) {
            return ns().record<_recordType>(pClass);
        }

        template<class ..._signature>
        constexpr const builder::Builder<detail::methodQ::None, _signature...> function(const std::string_view pFunction) {
            return ns().function<_signature...>(pFunction);
        }
    };
}
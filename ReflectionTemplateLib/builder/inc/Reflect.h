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
#include "Constants.h"
#include "Builder.h"

namespace rtl {

    namespace builder
    {
        template<class _recordType>
        class RecordBuilder;

        template<class _recordType>
        class MethodBuilder;

    /*  @class: Reflect
        * provides interface to register all kinds of functions (member/non-member).
    */  class Reflect
        {
            //name of the class, struct being registered.
            std::string_view m_record;

            //name of the namespace being registered.
            std::string_view m_namespace;

        public:

            Reflect();
            Reflect(const Reflect&) = delete;
            Reflect& operator=(const Reflect&) = delete;

            Reflect& nameSpace(const std::string_view pNamespace);

            template<class _recordType>
            constexpr const MethodBuilder<_recordType> record();

            template<class _recordType>
            constexpr const RecordBuilder<_recordType> record(const std::string_view pClass);

            template<class ..._signature>
            constexpr const Builder<methodQ::None, _signature...> function(const std::string_view pFunction);
        };
    }
}
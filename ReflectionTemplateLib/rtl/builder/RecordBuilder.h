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

#include <string_view>

#include "Function.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType, class ..._ctorSignature>
        struct ConstructorBuilder;

    /*  @class: RecordBuilder
        @param: <_recordType>, a struct/class type.
        * provides interface to register member-function & constructors of a class/struct.
    */  template<class _recordType>
        class RecordBuilder
        {
            const std::string_view m_record;
            const std::string_view m_namespace;
            const std::size_t m_recordId;

        public:

            RecordBuilder(const std::string_view pNamespace, const std::string_view pRecord, std::size_t pRecordId);

            const Function build() const;
        };


    /*  @class: RecordBuilder
        @param: <_recordType>, a struct/class type.
        * provides interface to register member-function & constructors of a class/struct.
    */  template<class _recordType>
        struct MethodBuilder
        {
            const Builder<detail::methodQ::NonConst> method(const std::string_view pFunction) const;

            const Builder<detail::methodQ::Const> methodConst(const std::string_view pFunction) const;

            const Builder<detail::methodQ::None> methodStatic(const std::string_view pFunction) const;

            template<class ..._signature>
            const Builder<detail::methodQ::NonConst, _signature...> method(const std::string_view pFunction) const;

            template<class ..._signature>
            const Builder<detail::methodQ::Const, _signature...> methodConst(const std::string_view pFunction) const;

            template<class ..._signature>
            const Builder<detail::methodQ::None, _signature...> methodStatic(const std::string_view pFunction) const;

            template<class ..._signature>
            constexpr const ConstructorBuilder<_recordType, traits::remove_cref_t<_signature>...> constructor() const;
        };
    }
}
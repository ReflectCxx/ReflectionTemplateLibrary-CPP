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

#include "Function.h"

namespace rtl {

    namespace builder 
    {
        template<class record_t, class ..._ctorSignature>
        struct ConstructorBuilder;

    /*  @class: RecordBuilder
        @param: <record_t>, a struct/class type.
        * provides interface to register member-function & constructors of a class/struct.
    */  template<class record_t>
        class RecordBuilder
        {
            const std::string m_recordStr;
            const std::string m_namespaceStr;
            const traits::uid_t m_recordId;

        public:

            RecordBuilder(const std::string& pNamespace, const std::string& pRecord, traits::uid_t pRecordId);

            const Function build() const;
        };


    /*  @class: RecordBuilder
        @param: <record_t>, a struct/class type.
        * provides interface to register member-function & constructors of a class/struct.
    */  template<class record_t>
        struct MethodBuilder
        {
            const Builder<detail::member::NonConst> method(const std::string& pFunction) const;

            const Builder<detail::member::Const> methodConst(const std::string& pFunction) const;

            const Builder<detail::member::Static> methodStatic(const std::string& pFunction) const;

            template<class ...signature_t>
            const Builder<detail::member::NonConst, signature_t...> method(const std::string& pFunction) const;

            template<class ...signature_t>
            const Builder<detail::member::Const, signature_t...> methodConst(const std::string& pFunction) const;

            template<class ...signature_t>
            const Builder<detail::member::Static, signature_t...> methodStatic(const std::string& pFunction) const;

            template<class ...signature_t>
            constexpr const ConstructorBuilder<record_t, signature_t...> constructor() const;
        };
    }
}
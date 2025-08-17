/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

#include "Function.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType, class ..._ctorSignature>
        class ConstructorBuilder;

    /*  @class: RecordBuilder
        @param: <_recordType>, a struct/class type.
        * provides interface to register member-function & constructors of a class/struct.
    */  template<class _recordType>
        class RecordBuilder
        {
            const std::string& m_record;
            const std::string& m_namespace;
            const std::size_t m_recordId;

        public:

            RecordBuilder(const std::string& pNamespace, const std::string& pRecord, std::size_t pRecordId);

            template<class ..._signature>
            constexpr const ConstructorBuilder<_recordType, _signature...> constructor() const;

            const Builder<methodQ::NonConst> method(const std::string& pFunction) const;

            const Builder<methodQ::None> methodStatic(const std::string& pFunction) const;

            const Builder<methodQ::Const> methodConst(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<methodQ::NonConst, _signature...> method(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<methodQ::None, _signature...> methodStatic(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<methodQ::Const, _signature...> methodConst(const std::string& pFunction) const;
        };
    }
}
/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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
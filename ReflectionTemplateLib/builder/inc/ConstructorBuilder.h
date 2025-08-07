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

#include "Constants.h"

namespace rtl {

    namespace builder 
    {
    /*  @class: ConstructorBuilder
        @param: _recordType - struct/class type. 
        *       _signature...- constructor args type (none/_record&/const _record& or any combination of parameters) 
        * provides interface to register constructors of a class/struct.
        * when the very first constructor(any- default/parametrized) is registered, copy-constructor gets registered implicitly.
        * all the objects are created via reflection are on heap, using 'new'.
        * the constructed objects are returned wrapped in 'Instance' object, with type erased.
        * lifetime of created objects are managed using 'shared_ptr'.
    */  template<class _recordType, class ..._ctorSignature>
        class ConstructorBuilder
        {
            //given name of the class/struct.
            const std::string& m_record;

            //given name of the namespace.
            const std::string& m_namespace;

            ConstructorBuilder() = delete;

        public:

            ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord)
                : m_record(pRecord)
                , m_namespace(pNamespace)
            { }

        /*  @method: build()
            @param: none
            @return: 'Function' object.
            * constructs temparory object of class Builder<methodQ::NonConst> with given class/struct, namespace name & constructor type.
            * forwards the call to Builder<methodQ::NonConst>::build().
        */  const access::Function build() const
            {
                // Check if the constructor is not deleted and publicly accessible (excluding default constructor).
                const bool isAccessible = (sizeof...(_ctorSignature) == 0 || std::is_constructible_v<_recordType, _ctorSignature...>);
                static_assert(isAccessible, "The specified constructor is either deleted or not publicly accessible.");

                const auto& ctorName = CtorName::ctor(m_record);
                return Builder<methodQ::NonConst>(m_namespace, m_record, ctorName, detail::TypeId<_recordType>::get()).build<_recordType, _ctorSignature...>();
            }
        };
    }
}
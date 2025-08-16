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

#include <string>
#include "Constants.h"
#include "Builder.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType>
        class RecordBuilder;

    /*  @class: Reflect
        * provides interface to register all kinds of functions (member/non-member).
    */  class Reflect
        {
            //name of the class, struct being registered.
            std::string m_record;

            //name of the namespace being registered.
            std::string m_namespace;

        public:

            Reflect();
            Reflect(const Reflect&) = delete;
            Reflect& operator=(const Reflect&) = delete;

            Reflect& nameSpace(const std::string& pNamespace);

            template<class ..._signature>
            constexpr const Builder<methodQ::None, _signature...> function(const std::string& pFunction);

            template<class _recordType>
            constexpr const RecordBuilder<_recordType> record(const std::string& pClass);
        };
    }
}
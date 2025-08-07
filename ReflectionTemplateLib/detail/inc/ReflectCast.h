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

#include <any>
#include <vector>
#include <functional>

#include "rtl_traits.h"

namespace rtl::access {
    class CxxMirror;
}

namespace rtl::detail
{
    class ReflectedConversions
    {
        static void init();
        friend rtl::access::CxxMirror;
    };


    template<class _fromType>
    class ReflectCast
    {
        static std::vector<std::pair<std::size_t, traits::Converter>>& conversions() {
            static std::vector<std::pair<std::size_t, traits::Converter>> converters;
            return converters;
        }

    public:

        template<class _toType> static void pushConversion();

        static const std::vector<std::pair<std::size_t, traits::Converter>>& getConversions() {
            return conversions();
        }
    };
}
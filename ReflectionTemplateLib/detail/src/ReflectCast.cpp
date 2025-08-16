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


#include "ReflectCast.hpp"
#include "ReflectCastUtil.h"

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<char>();

    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<char>();

    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>();
}


namespace rtl::detail
{
    void ReflectedConversions::init()
    {
        static const bool _= []()
        { 
            ReflectCast<std::string>::pushConversion<char>();
            ReflectCast<std::string_view>::pushConversion<char>();

            ReflectCast<std::string>::pushConversion<std::string_view>();
            ReflectCast<std::string_view>::pushConversion<std::string>();

            using _safePODTypes = std::tuple
            <bool, char, signed char, unsigned char, short, unsigned short, int>;

            auto conversions = make_conversion_pairs<_safePODTypes>();
            register_all_conversions<decltype(conversions)>();

            return true;
        }();
    }
}
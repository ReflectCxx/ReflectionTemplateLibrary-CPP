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
#include <typeinfo>
#include <atomic>

namespace rtl {

    namespace detail 
    {
        extern std::atomic<std::size_t> g_typeIdCounter;

        //class to generate unique type-id for a type or combination of types.
        template<class _type = std::nullptr_t, class ..._rest>
        struct TypeId;

        //class to generate unique type-id a type.
        template<class _type>
        struct TypeId<_type>
        {
            //represents '_type' or 'std::nullptr_t' for TypeId<> (empty).
            using HEAD = _type;

            //'0' represents no type.
            static constexpr const std::size_t None = 0;

            static std::size_t get() 
            {
                //statically initialize a unique-id.
                static const std::size_t typeId = g_typeIdCounter.fetch_add(1);
                return typeId;
            }

            //returns the type-list as string.
            static std::string toString()
            {
                if constexpr (std::is_same_v<_type, void>) {
                    return std::string("void");
                }
                if constexpr (std::is_same_v<_type, std::string>) {
                    return std::string("std::string");
                }
                if constexpr (std::is_same_v<_type, const std::string>) {
                    return std::string("const std::string");
                }
                if constexpr (std::is_same_v<_type, std::string&>) {
                    return std::string("std::string&");
                }
                if constexpr (std::is_same_v<_type, const std::string&>) {
                    return std::string("const std::string&");
                }
                if constexpr (std::is_same_v<_type, std::string&&>) {
                    return std::string("const std::string&&");
                }
                if constexpr (!std::is_same_v<_type, std::nullptr_t>) {
                    return std::string(typeid(_type).name());
                }
                if constexpr (std::is_same_v<_type, std::nullptr_t>) {
                    return "std::nullptr_t";
                }
                else return std::string();
            }
        };


        //class to generate unique type-id for a combination of types.
        template<class _first, class ..._rest>
        struct TypeId
        {
            //represents the first type in given list.
            using HEAD = _first;

            //represents a new list created excluding '_first'.
            using TAIL = TypeId<_rest...>;

            //returns the type-list as string.
            static std::string toString() 
            {
                const std::string& tailStr = TAIL::toString();
                if (std::is_same<HEAD, std::string>::value) {
                    return std::string("std::string") + ", " + tailStr;
                }
                return (std::string(typeid(HEAD).name()) + ", " + tailStr);
            }
        };
    }
}
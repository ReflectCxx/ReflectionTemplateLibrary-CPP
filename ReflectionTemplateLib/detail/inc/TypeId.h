/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *                                                               *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


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
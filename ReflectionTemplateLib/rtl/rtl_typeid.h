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

#include <vector>
#include <string>
#include <typeinfo>

#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

namespace rtl {

    namespace detail
    {
        extern std::size_t generate_unique_id();


        //class to generate unique type-id for a type or combination of types.
        template<class _type = std::nullptr_t, class ..._rest>
        struct TypeId;

        //class to generate unique type-id a type.
        template<class _type>
        struct TypeId<_type>
        {
            //represents '_type' or 'std::nullptr_t' for TypeId<> (empty).
            using HEAD = _type;

            using TAIL = std::nullptr_t;

            //'0' represents no type. [Never change, critical.]
            static constexpr const std::size_t None = 0;

            FORCE_INLINE static std::size_t get()
            {
                if constexpr (!std::is_same_v<_type, std::nullptr_t>)
                {
                    //statically initialize a unique-id.
                    static const std::size_t TypeId = detail::generate_unique_id();
                    return TypeId;
                }
                return None;
            }

            static void get(std::vector<std::size_t>& pIds)
            {
                pIds.push_back(get());
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
                if constexpr (std::is_same_v<_type, std::string_view>) {
                    return std::string("std::string_view");
                }
                if constexpr (!std::is_same_v<_type, std::nullptr_t>) {
                    return std::string(typeid(_type).name());
                }
                if constexpr (std::is_same_v<_type, std::nullptr_t>) {
                    return "";
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

            static void get(std::vector<std::size_t>& pIds)
            {
                if constexpr (std::is_same_v<typename TAIL::HEAD, std::nullptr_t>)
                {
                    pIds.push_back(TypeId<HEAD>::get());
                }
                else {
                    pIds.push_back(TypeId<HEAD>::get());
                    TAIL::get(pIds);
                }
            }


            //returns the type-list as string.
            static std::string toString()
            {
                const std::string& tailStr = TAIL::toString();
                if (std::is_same<HEAD, std::nullptr_t>::value) {
                    return "";
                }
                else if constexpr (std::is_same<HEAD, std::string>::value) {
                    return std::string("std::string") + ", " + tailStr;
                }
                else if constexpr (std::is_same<HEAD, std::string_view>::value) {
                    return std::string("std::string_view") + ", " + tailStr;
                }
                return (std::string(typeid(HEAD).name()) + ", " + tailStr);
            }
        };
    }
}
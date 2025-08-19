/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#include "TypeId.h"
#include "ReflectCast.hpp"

#include <iostream>

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<char>()
    {
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            pNewEntityKind = EntityKind::Ref;
            const auto& isPtr = (pSrcEntityKind == EntityKind::Ref);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string*>(pSrc) : std::any_cast<const std::string&>(pSrc));
            return std::any(srcObj.c_str());
        };
        conversions().emplace_back(std::pair(TypeId<char>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<char>()
    {
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            pNewEntityKind = EntityKind::Ref;
            const auto& isPtr = (pSrcEntityKind == EntityKind::Ref);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(srcObj.data());
        };
        conversions().emplace_back(std::pair(TypeId<char>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>()
    {
        using _toType = std::string;
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            pNewEntityKind = EntityKind::Value;
            const auto& isPtr = (pSrcEntityKind == EntityKind::Ref);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(_toType(srcObj));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}
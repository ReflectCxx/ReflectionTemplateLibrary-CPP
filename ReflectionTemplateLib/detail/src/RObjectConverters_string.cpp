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


#include "TypeId.h"
#include "ReflectCast.hpp"

#include <iostream>

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<const char*>()
    {
        using _toType = const char*;
        const auto& conversion = [](const std::any& pSrc, const rtl::IsPointer& pIsPointer, rtl::ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = rtl::ConversionKind::ByValue;
            const auto& isPtr = (pIsPointer == rtl::IsPointer::Yes);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string*>(pSrc) : std::any_cast<const std::string&>(pSrc));
            return std::any(static_cast<const _toType&>(srcObj.c_str()));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<const char*>()
    {
        using _toType = const char*;
        const auto& conversion = [](const std::any& pSrc, const rtl::IsPointer& pIsPointer, rtl::ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = rtl::ConversionKind::ByValue;
            const auto& isPtr = (pIsPointer == rtl::IsPointer::Yes);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(static_cast<const _toType&>(srcObj.data()));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>()
    {
        using _toType = std::string;
        const auto& conversion = [](const std::any& pSrc, const rtl::IsPointer& pIsPointer, rtl::ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = rtl::ConversionKind::ByValue;
            const auto& isPtr = (pIsPointer == rtl::IsPointer::Yes);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(_toType(srcObj));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}
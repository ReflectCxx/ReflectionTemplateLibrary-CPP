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

#include "TypeId.h"
#include "ReflectCast.h"

namespace rtl::detail
{
    template<class _fromType>
    template<class _toType>
    inline void ReflectCast<_fromType>::pushConversion()
    {
        const auto& conversion = [](const std::any& pSrc, const rtl::IsPointer& pIsSrcPointer, rtl::ConversionKind& pConvertKind) -> std::any
        {
            try 
            {
                bool isPointer = (pIsSrcPointer == rtl::IsPointer::Yes);
                const _fromType& srcRef = (isPointer ? *(std::any_cast<const _fromType*>(pSrc)) : std::any_cast<const _fromType&>(pSrc));

                if constexpr (std::is_convertible_v<_fromType*, _toType*>)
                {
                    pConvertKind = rtl::ConversionKind::ByRef;
                    return std::any(std::in_place_type<const _toType&>, static_cast<const _toType&>(srcRef));
                }
                else if constexpr ((std::is_convertible_v<_fromType, _toType> && !std::is_convertible_v<_fromType&, const _toType&>) ||
                                   std::is_constructible_v<_toType, const _fromType&>)
                {
                    pConvertKind = rtl::ConversionKind::ByValue;
                    return std::any(std::in_place_type<_toType>, _toType(srcRef));
                }

                pConvertKind = rtl::ConversionKind::NotDefined;
                return std::any();
            }
            catch (const std::bad_any_cast&) 
            {
                pConvertKind = rtl::ConversionKind::BadAnyCast;
                return std::any();
            }
        };

        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}
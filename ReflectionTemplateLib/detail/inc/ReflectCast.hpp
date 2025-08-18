/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *                                                               *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

#include "TypeId.h"
#include "ReflectCast.h"
#include "ConversionUtils.h"

namespace rtl::detail
{
    template<class _fromType>
    template<class _toType>
    inline void ReflectCast<_fromType>::pushConversion()
    {
//        if constexpr (traits::is_safe_conversion_v<_fromType, _toType>)
        {
            const auto& conversion = [](const std::any& pSrc, const entity& pSrcEntityKind, entity& pNewEntityKind) -> std::any
            {
                try
                {
                    bool isPointer = (pSrcEntityKind == entity::Pointer);
                    const _fromType& srcRef = (isPointer ? *(std::any_cast<const _fromType*>(pSrc)) : std::any_cast<const _fromType&>(pSrc));

                    if constexpr (std::is_convertible_v<_fromType*, _toType*>)
                    {
                        pNewEntityKind = pSrcEntityKind;     
                        return std::any(std::in_place_type<const _toType&>, static_cast<const _toType&>(srcRef));
                    }
                    else if constexpr ((std::is_convertible_v<_fromType, _toType> && 
                                       !std::is_convertible_v<_fromType&, const _toType&>) ||
                                       std::is_constructible_v<_toType, const _fromType&>) {

                        pNewEntityKind = entity::Value;
                        return std::any(std::in_place_type<_toType>, _toType(srcRef));
                    }
                    else {

                        pNewEntityKind = entity::None;
                        return std::any();
                    }
                }
                catch (const std::bad_any_cast&)
                {
                    pNewEntityKind = entity::None;
                    return std::any();
                }
            };
            conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
        }
    }
}
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
            const auto& conversion = [](const std::any& pSrc, const Contains& pContainedAs, ConversionKind& pConvertKind) -> std::any
            {
                try
                {
                    bool isPointer = (pContainedAs == Contains::Pointer);
                    const _fromType& srcRef = (isPointer ? *(std::any_cast<const _fromType*>(pSrc)) : std::any_cast<const _fromType&>(pSrc));

                    if constexpr (std::is_convertible_v<_fromType*, _toType*>)
                    {
                        pConvertKind = ConversionKind::ByRef;
                        return std::any(std::in_place_type<const _toType&>, static_cast<const _toType&>(srcRef));
                    }
                    else if constexpr ((std::is_convertible_v<_fromType, _toType> && 
                                       !std::is_convertible_v<_fromType&, const _toType&>) ||
                                       std::is_constructible_v<_toType, const _fromType&>) {

                        pConvertKind = ConversionKind::ByValue;
                        return std::any(std::in_place_type<_toType>, _toType(srcRef));
                    }
                    else {

                        pConvertKind = ConversionKind::NotDefined;
                        return std::any();
                    }
                }
                catch (const std::bad_any_cast&)
                {
                    pConvertKind = ConversionKind::BadAnyCast;
                    return std::any();
                }
            };
            conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
        }
    }
}
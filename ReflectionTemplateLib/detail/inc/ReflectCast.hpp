#pragma once

#include "TypeId.h"
#include "ReflectCast.h"

namespace rtl::detail
{
    template<class _fromType>
    inline const std::vector<std::pair<std::size_t, Converter>>& ReflectCast<_fromType>::getConversions()
    {
        return conversions();
    }


    template<class _fromType>
    inline std::vector<std::pair<std::size_t, Converter>>& rtl::detail::ReflectCast<_fromType>::conversions()
    {
        static std::vector<std::pair<std::size_t, Converter>> converters;
        return converters;
    }


    template<class _fromType>
    template<class _toType>
    inline void ReflectCast<_fromType>::pushConversion()
    {
        const auto& conversion = [](const std::any& pSrc, const bool& pIsPointer, bool& pConvertedByRef) -> std::any
        {
            try {
                if constexpr (std::is_convertible_v<_fromType*, _toType*>) 
                {
                    pConvertedByRef = true;
                    const _fromType& ref = (pIsPointer ? *(std::any_cast<const _fromType*>(pSrc)) : std::any_cast<const _fromType&>(pSrc));
                    return std::any(std::in_place_type<const _toType&>, static_cast<const _toType&>(ref));
                }
                else 
                {
                    pConvertedByRef = false;
                    if constexpr ((std::is_convertible_v<_fromType, _toType> &&
                                    !std::is_convertible_v<_fromType&, const _toType&>) ||
                                    std::is_constructible_v<_toType, const _fromType&>) {

                        const _fromType& value = pIsPointer ? *std::any_cast<const _fromType*>(pSrc) : std::any_cast<const _fromType&>(pSrc);
                        return std::any(std::in_place_type<_toType>, _toType(value));
                    }
                    return std::any();
                }
            }
            catch (const std::bad_any_cast&) {
                return std::any(); // runtime safety
            }
        };

        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}
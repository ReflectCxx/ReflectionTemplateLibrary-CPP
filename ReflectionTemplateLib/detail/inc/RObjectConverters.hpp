#pragma once

#include "RObjectConverters.h"

namespace rtl::detail
{
    template<class _fromType>
    std::vector<std::pair<std::size_t, Converter>>& rtl::detail::RObjectConverter<_fromType>::conversions()
    {
        static std::atomic_bool initialized = false;
        static std::vector<std::pair<std::size_t, Converter>> converters;
        if (!initialized) {
            initialized = true;
            pushKnownConversions();
        }
        return converters;
    }


    template<class _fromType>
    template<class _toType>
    void RObjectConverter<_fromType>::pushConversion()
    {
        const auto& conversion = [](const std::any& pSrc)-> std::any
        {
            if constexpr (std::is_convertible_v<const _fromType&, const _toType&>)
            {
                const auto& srcObj = std::any_cast<const _fromType&>(pSrc);
                return std::any(static_cast<const _toType&>(srcObj));
            }
            else if constexpr (std::is_constructible_v<_toType, const _fromType&>)
            {
                const auto& srcObj = std::any_cast<const _fromType&>(pSrc);
                return std::any(_toType(srcObj));
            }
            return std::any();
        };
		conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
	}
}
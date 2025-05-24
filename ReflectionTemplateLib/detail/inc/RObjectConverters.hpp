#pragma once

#include "RObjectConverters.h"

namespace rtl::detail
{
    template<class _fromType>
    inline const std::vector<std::pair<std::size_t, Converter>>& RObjectConverter<_fromType>::getConversions()
    {
        return conversions();
    }


    template<class _fromType>
    inline std::vector<std::pair<std::size_t, Converter>>& rtl::detail::RObjectConverter<_fromType>::conversions()
    {
        static std::vector<std::pair<std::size_t, Converter>> converters;
        return converters;
    }


    template<class _fromType>
    template<class _toType>
    inline void RObjectConverter<_fromType>::pushConversion()
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
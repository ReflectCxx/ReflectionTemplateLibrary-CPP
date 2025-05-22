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
			const auto& srcObj = std::any_cast<const _fromType&>(pSrc);
			return std::any(static_cast<_toType>(srcObj));
		};
		conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
	}
}
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
}
#pragma once

#include "RObjectConverters.h"

namespace rtl::detail 
{
	template<class _fromType>
	std::vector<std::pair<std::size_t, Converter>> RObjectConverter<_fromType>::m_converters;

	template<class _fromType>
	template<class _toType>
	inline void RObjectConverter<_fromType>::pushConversion()
	{

	}


	template<class _fromType>
	inline const std::vector<std::pair<std::size_t, Converter>>& RObjectConverter<_fromType>::getConversions()
	{
		return m_converters;
	}
}
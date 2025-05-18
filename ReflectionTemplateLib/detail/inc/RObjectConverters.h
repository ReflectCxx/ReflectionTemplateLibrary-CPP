#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "Constants.h"


namespace rtl::access {
	class RObject;
}


namespace rtl::detail
{
	using Converter = std::function< rtl::access::RObject(const rtl::access::RObject&) >;

	template<class _fromType>
	class RObjectConverter
	{
		static std::vector<std::pair<std::size_t, Converter>> m_converters;

	public:

		template<class _toType>
		static void pushConversion();

		static const std::vector<std::pair<std::size_t, Converter>>& getConversions();
	};
}
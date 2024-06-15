#pragma once

#include <unordered_map>

namespace rtl {

	class Function;

	class Record
	{
		std::unordered_map<std::string, Function> m_functions;

	public:

	};
}
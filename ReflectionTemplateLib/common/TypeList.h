#pragma once

#include <string>

namespace rtl {

	template<class _first = std::nullptr_t, class ..._rest>
	struct TypeList;

	template<> 
	struct TypeList<> 
	{ 
		using HEAD = std::nullptr_t;
		using TAIL = std::nullptr_t;

		static const std::string toString() {
			return "";
		}
	};


	template<class ..._rest>
	struct TypeList<std::string, _rest...>
	{
		using TAIL = TypeList<_rest...>;

		static const std::string toString() {
			const std::string& tailStr = TAIL::toString();
			return "std::string" + (tailStr.empty() ? "" : (", " + tailStr));
		}
	};


	template<class _first, class ..._rest>
	struct TypeList 
	{
		using HEAD = _first;
		using TAIL = TypeList<_rest...>;

		static const std::string toString() {

			const std::string& tailStr = TAIL::toString();
			return std::string(typeid(HEAD).name()) + (tailStr.empty() ? "" : (", " + tailStr));
		}
	};
}
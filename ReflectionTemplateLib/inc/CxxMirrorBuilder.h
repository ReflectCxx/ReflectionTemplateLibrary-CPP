#pragma once

#include "Function.hpp"
#include "Constants.h"

namespace rtl {

	// Builder class to encapsulate all type names, pointers.
	class Reflect
	{
		std::string m_record;
		std::string m_function;
		std::string m_namespace;

	public:

		Reflect();
		Reflect(const Reflect&) = delete;
		Reflect& operator=(const Reflect&) = delete;

		Reflect& record(const std::string& pClass);

		Reflect& nameSpace(const std::string& pNamespace = NS_GLOBAL);

		const Reflect& function(const std::string& pFunction);

		template<class _returnType, class ..._signature>
		inline constexpr const Function build(_returnType(*pFunctor)(_signature...)) const
		{
			return Function::add(m_namespace, m_record, m_function, pFunctor);
		}
	};
}
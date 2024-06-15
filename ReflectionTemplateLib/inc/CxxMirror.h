#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "Function.hpp"
#include "NameSpace.h"
#include "TypeDescriptorList.h"
#include "FunctorContainer.h"

namespace rtl {

	template<class ..._signType>
	using TypeSignature = FunctorContainer<_signType...>;

	template<class ..._signaturesList>
	class CxxMirror
	{
		using TypesDescriptor = TypeDescriptorList<0, _signaturesList...>;

		std::unordered_map<std::string, NameSpace> m_namespaces;

	public:

		CxxMirror() = delete;
		CxxMirror(CxxMirror&) = delete;
		CxxMirror& operator=(CxxMirror&) = delete;
		inline CxxMirror(std::vector<Function> pFunctions);

		inline static const bool init();

		inline auto operator()(const Function& pFunction);

		inline std::optional<Function> getFunction(const std::string& pFunction);

		inline std::optional<Function> getFunction(const std::string& pNameSpace, const std::string& pFunction);
	};
}
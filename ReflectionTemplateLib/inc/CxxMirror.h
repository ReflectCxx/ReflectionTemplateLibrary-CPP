#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "Function.hpp"
#include "SignatureTypeList.h"
#include "FunctorContainer.h"

namespace rtl {

	class NameSpace;

	template<class ..._signType>
	using TypeSignature = FunctorContainer<_signType...>;

	template<class ..._signaturesList>
	class CxxMirror
	{
		using SignatureDescriptor = SignatureTypeList<0, _signaturesList...>;

		std::unordered_map<std::string, NameSpace> m_namespaces;

	public:

		CxxMirror() = delete;
		CxxMirror(CxxMirror&) = delete;
		CxxMirror& operator=(CxxMirror&) = delete;
		inline CxxMirror(std::vector<Function> pFunctions);

		inline static const bool init();

		inline std::optional<Function> getFunction(const std::string& pFunction);

		inline std::optional<Function> getFunction(const std::string& pNameSpace, const std::string& pFunction);

		inline auto operator()(const Function& pFunction);
	};
}
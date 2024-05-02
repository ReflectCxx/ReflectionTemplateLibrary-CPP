#pragma once

#include <map>
#include <vector>
#include <string>

namespace clang_reflect 
{
	class ReflectableInterface
	{
		using FuncSignature = std::multimap<std::string, std::vector<std::string> >;
		using FuncHeaderMap = std::map<std::string, FuncSignature>;
		std::map<std::string, FuncHeaderMap> m_functionSignatureMap;

		ReflectableInterface();
		~ReflectableInterface();

	public:

		ReflectableInterface(const ReflectableInterface&) = delete;
		ReflectableInterface& operator=(const ReflectableInterface&) = delete;

		static ReflectableInterface& Instance();

		void addFunctionSignature(const std::string& pSrcFile, const std::string& pHeaderFile, const std::string& pFunctionName, const std::vector<std::string>& pParmTypes);

		void dump();
	};
}
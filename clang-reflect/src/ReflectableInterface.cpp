#include <iostream>
#include <mutex>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Logger.h"
#include "CommandLineParser.h"
#include "ReflectableInterface.h"

namespace {

	std::mutex g_mutex;
}

namespace clang_reflect 
{
	ReflectableInterface::ReflectableInterface() {

	}


	ReflectableInterface::~ReflectableInterface() {

	}


	ReflectableInterface& ReflectableInterface::Instance()
	{
		static ReflectableInterface instance;
		return instance;
	}


	void ReflectableInterface::addFunctionSignature(const std::string& pSrcFile, const std::string& pHeaderFile, const std::string& pFunctionName, const std::vector<std::string>& pParmTypes)
	{
		std::lock_guard<std::mutex> lock(g_mutex);

		const auto& srcItr = m_functionSignatureMap.find(pSrcFile);
		if (srcItr == m_functionSignatureMap.end()) 
		{
			FuncSignature funcSigMap;
			FuncHeaderMap funcHeaderMap;
			funcSigMap.emplace(pFunctionName, pParmTypes);
			funcHeaderMap.emplace(pHeaderFile, funcSigMap);
			m_functionSignatureMap.emplace(pSrcFile, funcHeaderMap);
		}
		else 
		{
			auto& funcHeaderMap = srcItr->second;
			const auto& headerItr = funcHeaderMap.find(pHeaderFile);
			if (headerItr == funcHeaderMap.end()) {
				FuncSignature signatureMap;
				signatureMap.emplace(pFunctionName, pParmTypes);
				funcHeaderMap.emplace(pHeaderFile, signatureMap);
			}
			else {
				headerItr->second.emplace(pFunctionName, pParmTypes);
			}
		}
	}


	void ReflectableInterface::dump()
	{
		std::string fileStr = (CommandLineParser::getInterfaceDumpDir() + "/" + CL_REFLECT_INTERFACE);
		std::replace(fileStr.begin(), fileStr.end(), '\\', '/');

		std::fstream fout(fileStr, std::ios::out);

		if (!fout.is_open()) {
			Logger::outException("Error opening file for writing!");
			return;
		}
		
		int functionsCount = 0;
		for (const auto& itr : m_functionSignatureMap)
		{
			const FuncHeaderMap& headerMap = itr.second;
			fout << "\n\nReflecatble functions extracted from file: " << itr.first;
			for (const auto& itr : headerMap)
			{
				fout << "\n#include \"" << itr.first << "\"";
				const auto& signatureMap = itr.second;
				for (const auto& parmItr : signatureMap) {
					fout << "\n\t" << parmItr.first << "(";
					int index = 0;
					for (const auto& parmType : parmItr.second) {
						fout << " " << parmType;
						if (++index != parmItr.second.size()) {
							fout << ",";
						}
					}
					fout << " )";
					functionsCount++;
				}
			}
		}

		fout.flush();
		fout.close();
		if (fout.fail() || fout.bad()) {
			Logger::outException("Error closing file:" + std::string(CL_REFLECT_INTERFACE));
			return;
		}

		Logger::out("Number of reflectable functions generated: " + std::to_string(functionsCount));
		Logger::out("Number of headerfiles shortlisted, containing reflectable functions declarations: " + std::to_string(m_functionSignatureMap.size()));
		Logger::out("Reflection interface file generated : " + fileStr);
	}
}

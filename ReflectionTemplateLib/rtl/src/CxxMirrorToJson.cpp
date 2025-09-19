/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#include <fstream>
#include <filesystem>
#include <algorithm>

#include "Method.h"
#include "Record.h"
#include "Function.h"
#include "CxxMirror.h"
#include "CxxMirrorToJson.h"

using namespace rtl;
using namespace rtl::detail;

static const std::string toJson(const FunctorId& pFunctorId)
{
	std::stringstream sout;
	sout << "{\"containerId\": \"" << std::to_string(pFunctorId.getSignatureId()) << "\",";
	sout << "\"lambdaIndex\": \"" << std::to_string(pFunctorId.getLambdaIndex()) << "\",";
	if (pFunctorId.getRecordId() != TypeId<>::None) {
		sout << "\"recordId\": \"" << std::to_string(pFunctorId.getRecordId()) << "\",";
	}
	sout << "\"returnId\": \"" << std::to_string(pFunctorId.getReturnId()) << "\",";
	sout << "\"hash_code\": \"" << std::to_string(pFunctorId.getHashCode()) << "\",";
	sout << "\"signature\": \"" << pFunctorId.getSignatureStr() << "\"}";
	return sout.str();
}


static const std::string toJson(const Function& pFunction)
{
	std::stringstream sout;
	const auto& functors = pFunction.getOverloads();
	const std::string& record = pFunction.getRecordName();
	const std::string& nmspace = pFunction.getNamespace();

	sout << "{" << (record.empty() ? "\"function\"" : "\"method\"") << ": \"" << pFunction.getFunctionName() << "\",";
	if (nmspace != rtl::detail::NAMESPACE_GLOBAL) {
		sout << "\"namespace\": \"" << nmspace << "\",";
	}
	if (!record.empty()) {
		sout << "\"record\": \"" << record << "\",";
	}

	int index = 0;
	sout << "\"functorId\": [";
	for (const auto& funtorId : functors) {
		sout << toJson(funtorId);
		if (++index < functors.size()) {
			sout << ", ";
		}
	}
	sout << "]}";
	return sout.str();
}


namespace rtl 
{
	void CxxMirrorToJson::dump(const CxxMirror& pCxxMirror, const std::string& pFilePathStr)
	{
		std::string fileStr = pFilePathStr;
		std::replace(fileStr.begin(), fileStr.end(), '\\', '/');
		std::fstream fout(fileStr, std::ios::out);
		if (!fout.is_open()) {
			return;
		}
		fout << toJson(pCxxMirror);
		fout.flush();
		fout.close();
		if (fout.fail() || fout.bad()) {
			return;
		}
	}


	const std::string CxxMirrorToJson::toJson(const CxxMirror& pCxxMirror)
	{
		std::stringstream sout;
		sout << "[";
		bool atLeastOne = false;
		const auto& nsfuncMap = pCxxMirror.getNamespaceFunctionsMap();
		for (const auto& itr : nsfuncMap)
		{
			for (const auto& itr0 : itr.second)
			{
				const std::string& functionStr = ::toJson(itr0.second);
				sout << functionStr << ",";
				atLeastOne = true;
			}
		}

		const auto& recfuncMap = pCxxMirror.getNamespaceRecordMap();
		for (const auto& itr : recfuncMap)
		{
			for (const auto& itr0 : itr.second)
			{
				for (const auto& itr1 : itr0.second.get().getMethodMap())
				{
					const std::string& methodStr = ::toJson(itr1.second);
					sout << methodStr << ",";
					atLeastOne = true;
				}
			}
		}

		std::string str = sout.str();
		if (str.back() == ',') str.pop_back();
		str.push_back(']');
		return str;
	}
}

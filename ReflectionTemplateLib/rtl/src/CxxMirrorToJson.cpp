/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <fstream>
#include <filesystem>
#include <algorithm>

#include <inc/Method.h>
#include <inc/Record.h>
#include <inc/Function.h>
#include <inc/CxxMirror.h>
#include <inc/CxxMirrorToJson.h>

using namespace rtl;
using namespace rtl::detail;

static const std::string toJson(const type_meta& pFnMeta)
{
	std::stringstream sout;
	sout << "{\"recordId\": \"" << std::to_string(pFnMeta.get_record_id()) << "\",";
	sout << "\"returnId\": \"" << std::to_string(pFnMeta.get_return_id()) << "\",";
	sout << "\"signatureId\": \"" << std::to_string(pFnMeta.get_strict_args_id()) << "\",";
	if (pFnMeta.get_record_id() != traits::uid<>::none) {
		if (pFnMeta.get_member_kind() == member::Static)
			sout << "\"memberKind\": \"static_function\",";
		else if (pFnMeta.get_member_kind() == member::Const)
			sout << "\"memberKind\": \"const_function\",";
		else if (pFnMeta.get_member_kind() == member::NonConst)
			sout << "\"memberKind\": \"mutable_function\",";
		else if (pFnMeta.get_member_kind() == member::UserCtor)
			sout << "\"memberKind\": \"overloaded_ctor\",";
		else if (pFnMeta.get_member_kind() == member::DefaultCtor)
			sout << "\"memberKind\": \"default_ctor\",";
	}
	sout << "\"signature\": \"" << pFnMeta.get_signature_str() << "\"}";
	return sout.str();
}


static const std::string toJson(const Function& pFunction)
{
	std::stringstream sout;
	const auto& functors = pFunction.getFunctorsMeta();
	const std::string& record = pFunction.getRecordName();

	sout << "{" << (record.empty() ? "\"function\"" : "\"method\"") << ": \"" << pFunction.getFunctionName() << "\",";
	if (!record.empty()) {
		sout << "\"record\": \"" << record << "\",";
	}

	int index = 0;
	sout << "\"functorMeta\": [";
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
		const auto& functionsMap = pCxxMirror.getFunctionsMap();
		for (const auto& itr : functionsMap)
		{
			const std::string& functionStr = ::toJson(itr.second);
			sout << functionStr << ",";
		}

		const auto& recordsMap = pCxxMirror.getRecordsMap();
		for (const auto& itr0 : recordsMap)
		{
			for (const auto& itr1 : itr0.second.get().getMethodMap())
			{
				const std::string& methodStr = ::toJson(itr1.second);
				sout << methodStr << ",";
			}
		}

		std::string str = sout.str();
		if (str.back() == ',') str.pop_back();
		str.push_back(']');
		return str;
	}
}

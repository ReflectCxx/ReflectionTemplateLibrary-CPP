
#include <fstream>
#include <filesystem>
#include <sstream>

#include "Method.h"
#include "Record.h"
#include "Function.h"
#include "CxxMirror.h"
#include "CxxMirrorToJson.h"

using namespace rtl::access;
using namespace rtl::detail;

namespace
{
	const std::string toJson(const FunctorId& pFunctorId)
	{
		std::stringstream sout;
		sout << "{\"hash_code\": \"" << std::to_string(pFunctorId.getHashCode()) << "\",";
		sout << "\"signature\": \"" << pFunctorId.getSignatureStr() << "\"}";
		return sout.str();
	}

	const std::string toJson(const Function& pFunction)
	{
		std::stringstream sout;
		const auto& functors = pFunction.getFunctors();
		const std::string& record = pFunction.getRecordName();
		const std::string& nmspace = pFunction.getNamespace();

		sout << "{" << (record.empty() ? "\"function\"" : "\"method\"") << ": \"" << pFunction.getFunctionName() << "\",";
		if (nmspace != rtl::NAMESPACE_GLOBAL) {
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


	const std::string toJson(CxxMirror& pCxxMirror)
	{
		std::stringstream sout;
		sout << "[";
		bool atLeastOne = false;
		const auto& nsfuncMap = pCxxMirror.getNamespaceFunctionsMap();
		for (const auto& itr : nsfuncMap)
		{
			for (const auto& itr0 : itr.second)
			{
				const std::string& functionStr = toJson(itr0.second);
				sout << functionStr << ",";
				atLeastOne = true;
			}
		}

		const auto& recfuncMap = pCxxMirror.getNamespaceRecordMap();
		for (const auto& itr : recfuncMap)
		{
			for (const auto& itr0 : itr.second)
			{
				for (const auto& itr1 : itr0.second.getMethodMap())
				{
					const std::string& methodStr = toJson(itr1.second);
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


namespace rtl 
{
	void CxxMirrorToJson::dump(CxxMirror& pCxxMirror, const std::string& pFilePathStr)
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
}

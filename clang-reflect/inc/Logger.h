#pragma once

#include "Constants.h"

namespace clang_reflect {

	class Logger
	{
		static std::size_t m_totalCount;
		static std::size_t m_currentCount;
		static std::size_t m_totalDigitCount;

		static std::string formatProgress();

	public:

		static void out(const std::string& pMsg);
		static void outException(const std::string& pMsg);
		static void resetDoneCounter(const int pTotalCount);
		static void outProgress(const std::string& pMsg, bool pUpdate = true);
		static void outReflectError(const std::string& pSrcFile,
									const std::vector<std::string>& pUnreflectedFuncs, 
									const std::vector<ErrorTuple>& pMissingHeaders);
	};
}
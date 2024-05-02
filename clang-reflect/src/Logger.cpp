
#include <iostream>
#include <sstream>
#include <iomanip>
#include <mutex>

#include "Constants.h"
#include "Logger.h"

namespace {
	static  std::mutex g_mutex;
}

namespace clang_reflect {

	std::size_t Logger::m_totalCount = 0;
	std::size_t Logger::m_currentCount = 0;
	std::size_t Logger::m_totalDigitCount = 0;

	void Logger::out(const std::string& pMsg)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		std::cout << BLUE << "\n[cl-reflect]\t" << RESET << pMsg;
	}

	void Logger::outException(const std::string& pMsg)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		std::cout << DARK_RED << "\n\t\t[exception] " << pMsg;
	}

	void Logger::outReflectError(const std::string& pSrcFile, const std::vector<std::string>& pUnreflectedFuncs, const std::vector<ErrorTuple>& pMissingHeaders)
	{
		std::lock_guard<std::mutex> lock(g_mutex);

		if (pMissingHeaders.empty() && pUnreflectedFuncs.empty()){
			return;
		}

		std::cout << DARK_RED << "\n\t\t[error]"<< GREY << " errors while compiling: " << CYAN << pSrcFile << GREY << ",";
		for (const auto& tuple: pMissingHeaders)
		{
			std::string missingMsg = std::get<2>(tuple);
			std::size_t start = missingMsg.find('\'');
			std::size_t end = missingMsg.find('\'', start + 1);
			if (start != std::string::npos && end != std::string::npos && end > start) 
			{
				std::string quotedText = missingMsg.substr(start + 1, end - start - 1);
				std::string restOfMsg = missingMsg.substr(end + 1);
				std::cout << DARK_RED << "\n\t\t[error]\t"
					<< CYAN << std::get<0>(tuple) << GREY << std::get<1>(tuple)
					<< RESET << ": " << RED << "\'" << quotedText << "\'" << GREY << restOfMsg;
			}
			else
			{
				std::cout << DARK_RED << "\n\t\t[error]\t"
					<< CYAN << std::get<0>(tuple) << GREY << std::get<1>(tuple)
					<< RESET << ": " << RED << std::get<2>(tuple);
			}
		}

		for (const auto& func : pUnreflectedFuncs)
		{
			std::cout << DARK_RED << "\n\t\t[error]" << GREY << " unable to reflect: "
				<< YELLOW << func <<"()";
		}
	}

	void Logger::outProgress(const std::string& pMsg, bool pUpdate/* = true*/)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		if (pUpdate) {
			m_currentCount++;
		}
		std::cout << GREEN << "\n[" << formatProgress() << "]\t" << TEAL << pMsg;
	}

	void Logger::resetDoneCounter(const int pTotalCount){
		m_currentCount = 0;
		m_totalCount = pTotalCount;
		m_totalDigitCount = std::to_string(m_totalCount).length();
	}

	std::string Logger::formatProgress()
	{
		std::stringstream doneStream;
		std::stringstream progressStream;
		doneStream << std::setw(m_totalDigitCount) << std::setfill('0') << m_currentCount;
		progressStream << doneStream.str() << "/" << m_totalCount;
		return progressStream.str();
	}
}
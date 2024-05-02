#pragma once

#include <vector>
#include <string>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

namespace clang_reflect
{
	class ASTParser
	{
		const std::vector<std::string>& m_files;
		clang::tooling::CompilationDatabase* m_cdb;

		ASTParser() = delete;

		clang::tooling::ArgumentsAdjuster getArgumentsAdjuster();

		llvm::Expected<clang::tooling::CommonOptionsParser> getCommonOptionsParser(int pArgc, const std::vector<char*>& pArgv);

		const std::string getRelativePath(const std::string& pFileName);

	public:

		ASTParser(	const std::string& pBaseDir,
					const std::vector<std::string>& pFiles,
					clang::tooling::CompilationDatabase* pCdb);

		const int parseFiles(const int pStartIndex, const int pEndIndex);
	};
}
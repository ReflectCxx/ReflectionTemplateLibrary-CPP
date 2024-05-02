#include "ASTParser.h"

#include <mutex>
#include <iostream>
#include <filesystem>

#include "Logger.h"
#include "Constants.h"
#include "IncludesManager.h"
#include "CommandLineParser.h"
#include "clang-tidy/ClangTidyDiagnosticConsumer.h"
#include "ClangReflectDiagnosticConsumer.h"
#include "ClangReflectActionFactory.h"

using namespace llvm;
using namespace clang;
using namespace clang::tidy;
using namespace clang::tooling;

namespace
{
	std::mutex g_mutex;
	static cl::OptionCategory toolCategory(clang_reflect::CLANG_REFLECT);
	static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
	static cl::extrahelp MoreHelp("\nMore help text...\n");
}


namespace clang_reflect
{
	ASTParser::ASTParser(	const std::string& pBaseDir,
							const std::vector<std::string>& pFiles,
							CompilationDatabase* pCdb)
		: m_files(pFiles)
		, m_cdb(pCdb)
	{

	}

	
	Expected<CommonOptionsParser> ASTParser::getCommonOptionsParser(int pArgc, const std::vector<char*>& pArgv)
	{
		std::lock_guard<std::mutex> lock(g_mutex);
		return CommonOptionsParser::create(pArgc, (const char**)(&pArgv[0]), toolCategory);
	}


	const std::string ASTParser::getRelativePath(const std::string& pFileName)
	{
		static std::string baseDir;
		if (baseDir.empty()) {
			baseDir = CommandLineParser::getBaseDirectory();
			std::replace(baseDir.begin(), baseDir.end(), '\\', '/');
		}

		auto fileName = pFileName;
		std::replace(fileName.begin(), fileName.end(), '\\', '/');
		if (fileName.find(baseDir) == 0) {
			fileName.erase(0, baseDir.length() + 1);
		}
		return fileName;
	}


	ArgumentsAdjuster ASTParser::getArgumentsAdjuster()
	{
		return [this](const CommandLineArguments& pArgs, StringRef pFilePath) 
		{
			CommandLineArguments newArgs = pArgs;
			if (this->m_cdb == nullptr)
			{
				const bool isCFile = (pFilePath.endswith(".c") || pFilePath.endswith(".C"));
				newArgs.push_back(isCFile ? "-std=c99" : "-std=c++14");
				newArgs.push_back("-fopenmp");
				newArgs.push_back("-fexceptions");
				newArgs.push_back("-Wno-error");
				newArgs.push_back("-fsyntax-only");
				newArgs.push_back("-ferror-limit=0");
				
				std::unordered_set<std::string> includeDirs;
				IncludesManager::Instance().loadIncludeDirsForSource(pFilePath.str(), includeDirs);
				for (auto& incDir : includeDirs) {
					newArgs.push_back(std::string("-I" + incDir));
				}
			}
			return newArgs;
		};
	}


	const int ASTParser::parseFiles(const int pStartIndex, const int pEndIndex)
	{
		for (size_t index = pStartIndex; index <= pEndIndex; index++)
		{
			int argc = 2;
			std::vector<char*> argv;
			const auto& srcFilePath = m_files.at(index).c_str();

			Logger::outProgress("compiling: " + std::string(srcFilePath));

			if (m_cdb && !std::filesystem::exists(srcFilePath)) {
				Logger::outProgress(srcFilePath + std::string(". File not found..!"), false);
				continue;
			}

			argv.push_back(const_cast<char*>(CLANG_REFLECT));
			argv.push_back(const_cast<char*>(srcFilePath));
			auto commonOptionParser = getCommonOptionsParser(argc, argv);

			if (!commonOptionParser) {
				llvm::errs() << commonOptionParser.takeError();
				Logger::out("\tUnexpected error occured. Aborting..!");
				return 1;
			}

			ClangTidyOptions overrideOpts;
			overrideOpts.HeaderFilterRegex = ".*";
			overrideOpts.ExtraArgs = ClangTidyOptions::ArgList();
			
			auto customOptsProvider = std::make_unique<DefaultOptionsProvider>(ClangTidyGlobalOptions(), overrideOpts);
			if (!customOptsProvider) {
				return -1;
			}

			const auto& compileDb = (m_cdb ? *m_cdb : commonOptionParser.get().getCompilations());

			ClangTool clangTool(compileDb, { srcFilePath });
			ClangTidyContext context(std::move(customOptsProvider));
			ClangReflectDiagnosticConsumer diagConsumer(context);
			DiagnosticsEngine diagEngine(new DiagnosticIDs(), new DiagnosticOptions(), &diagConsumer, false);
			
			context.setDiagnosticsEngine(&diagEngine);
			clangTool.setDiagnosticConsumer(&diagConsumer);
			clangTool.appendArgumentsAdjuster(getArgumentsAdjuster());

			auto actionFactory = std::unique_ptr<ClangReflectActionFactory>(new ClangReflectActionFactory(context));
			clangTool.run(actionFactory.get());

			auto unreflectedFuncs = actionFactory->getUnreflectedFunctions();
			auto missingHeaderErrors = diagConsumer.getMissingHeaderMsgs();
			Logger::outReflectError(getRelativePath(srcFilePath), unreflectedFuncs, missingHeaderErrors);
		}
		return 0;
	}
}
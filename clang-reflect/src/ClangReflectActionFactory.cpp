
#include <iostream>
#include <unordered_set>

#include "ClangReflectActionFactory.h"
#include "FindRecordDeclsVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "ASTParser.h"
#include "Logger.h"
#include "clang/StaticAnalyzer/Frontend/AnalysisConsumer.h"

namespace {

	class FindRecordDeclsConsumer : public clang::ASTConsumer
	{
		const std::string& m_currentSrcFile;
		std::vector<std::string>& m_unreflectedFunctions;

	public:

		explicit FindRecordDeclsConsumer(const std::string& pContext, std::vector<std::string>& pUnreflectedFunctions)
		: m_currentSrcFile(pContext)
		, m_unreflectedFunctions(pUnreflectedFunctions)
		{

		}

		virtual void HandleTranslationUnit(clang::ASTContext& Context)
		{
			clang_reflect::FindRecordDeclsVisitor visitor(m_currentSrcFile, m_unreflectedFunctions);
			visitor.TraverseDecl(Context.getTranslationUnitDecl());
		}
	};


	class FindRecordDeclsAction : public clang::ASTFrontendAction
	{
		std::string m_targetSrcFile;
		std::vector<std::string>& m_unreflectedFunctions;

	public:

		explicit FindRecordDeclsAction(std::vector<std::string>& pUnreflectedFunctions) 
		: m_unreflectedFunctions(pUnreflectedFunctions)
		{

		}

		std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler, llvm::StringRef InFile) override
		{
			/*insignificant LOC. 
			  just to force linker to link with dependent libs.*/
#if !defined(_WIN32) && !defined(_WIN64)
			clang::ento::CreateAnalysisConsumer(Compiler);
#endif		//--ends--!

			Compiler.getDiagnosticOpts().ShowCarets = false;
			return std::make_unique<FindRecordDeclsConsumer>(m_targetSrcFile, m_unreflectedFunctions);
		}

		bool BeginSourceFileAction(clang::CompilerInstance& CI) override {
			const auto& inputs = CI.getInvocation().getFrontendOpts().Inputs;
			m_targetSrcFile = inputs[0].getFile().str();
			return true;
		}
	};
}


namespace clang_reflect {

	ClangReflectActionFactory::ClangReflectActionFactory(clang::tidy::ClangTidyContext& pContext)
	{

	}

	std::unique_ptr<clang::FrontendAction> ClangReflectActionFactory::create()
	{
		return std::make_unique<FindRecordDeclsAction>(m_unreflectedFunctions);
	}

	const std::vector<std::string>& ClangReflectActionFactory::getUnreflectedFunctions()
	{
		return m_unreflectedFunctions;
	}
}
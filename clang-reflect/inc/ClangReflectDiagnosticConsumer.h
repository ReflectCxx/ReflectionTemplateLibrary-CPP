#pragma once

#include "Constants.h"
#include "clang/Basic/Diagnostic.h"
#include "clang-tidy/ClangTidy.h"

namespace clang_reflect {

	class ClangReflectDiagnosticConsumer : public clang::tidy::ClangTidyDiagnosticConsumer
	{
		std::vector<ErrorTuple> m_errors;

		const std::string getFormattedFileName(const std::string& pFileName);

	public:

		ClangReflectDiagnosticConsumer(clang::tidy::ClangTidyContext& pContext);

		void HandleDiagnostic(clang::DiagnosticsEngine::Level pDiagLevel,const clang::Diagnostic& pInfo) override;

		const std::vector<ErrorTuple>& getMissingHeaderMsgs();
	};
}
#pragma once

#include <memory>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang-tidy/ClangTidyDiagnosticConsumer.h"

namespace clang_reflect 
{
	class ClangReflectActionFactory : public clang::tooling::FrontendActionFactory
	{
		std::vector<std::string> m_unreflectedFunctions;

	public:

		ClangReflectActionFactory(clang::tidy::ClangTidyContext& pContext);

		std::unique_ptr<clang::FrontendAction> create() override;

		const std::vector<std::string>& getUnreflectedFunctions();
	};
}
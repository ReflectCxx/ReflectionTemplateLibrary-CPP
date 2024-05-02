#pragma once

#include <map>
#include "clang/AST/RecursiveASTVisitor.h"

namespace clang_reflect {

    class FindRecordDeclsVisitor : public clang::RecursiveASTVisitor<FindRecordDeclsVisitor>
    {
        std::string m_baseDir;
        const std::string& m_currentSrcFile;
        std::vector<std::string>& m_unreflectedFunctions;

        void removeSubStrings(std::string& pSrcStr, const std::vector<std::string>& pKeyStrs);
        void replaceSubString(std::string& pSrcStr, const std::string& pSubstr, const std::string& pReplacestr);
        
        const bool isInUserCode(const clang::NamedDecl* pNameDecl);
        const bool isDeclFrmCurrentSource(clang::Decl* pDecl);

        const bool isMemberFunctionOrInNamespace(clang::FunctionDecl* pFuncDecl);
        const std::string extractParameterType(clang::ParmVarDecl* pParmVarDecl);
        
        const std::optional<std::string>
        getTypeDefAliasForType(const clang::QualType& pQType, std::unordered_map<std::string, std::string>& pTemplateTypeDefs);

    public:

        bool VisitFunctionDecl(clang::FunctionDecl* pFuncDecl);
        explicit FindRecordDeclsVisitor(const std::string& pCurrentSrcFile, std::vector<std::string>& pUnreflectedFunctions);
    };
}
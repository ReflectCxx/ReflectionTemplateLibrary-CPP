
#include <iostream>
#include <algorithm>

#include "Constants.h"
#include "FindRecordDeclsVisitor.h"
#include "ParamVarDeclsVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "ReflectableInterface.h"
#include "CommandLineParser.h"
#include "clang/Lex/Lexer.h"


namespace clang_reflect
{
	using namespace clang;

	FindRecordDeclsVisitor::FindRecordDeclsVisitor(const std::string& pCurrentSrcFile, std::vector<std::string>& pUnreflectedFunctions)
	: m_currentSrcFile(pCurrentSrcFile)
	, m_unreflectedFunctions(pUnreflectedFunctions)
	{

	}


	const bool FindRecordDeclsVisitor::isInUserCode(const NamedDecl* pNameDecl)
	{
		if (pNameDecl->getSourceRange().isValid()) {
			const SourceManager& SM = pNameDecl->getASTContext().getSourceManager();
			return !(SM.isInSystemHeader(pNameDecl->getLocation()) || SM.isInSystemMacro(pNameDecl->getLocation()));
		}
		return false;
	}


	const bool FindRecordDeclsVisitor::isMemberFunctionOrInNamespace(clang::FunctionDecl* pFuncDecl)
	{
		if (llvm::isa<clang::CXXRecordDecl>(pFuncDecl->getParent())) {
			return true;
		}
		auto currentDecl = pFuncDecl->getParent();
		while (currentDecl) {
			if (const clang::NamespaceDecl* namespaceDecl = llvm::dyn_cast<clang::NamespaceDecl>(currentDecl)) {
				return true;
			}
			currentDecl = currentDecl->getParent();
		}
		return false;
	}


	void FindRecordDeclsVisitor::replaceSubString(std::string& pSrcStr, const std::string& pSubstr, const std::string& pReplacestr)
	{
		if (pReplacestr.find(pSubstr) != std::string::npos) {
			return;
		}

		size_t pos = std::string::npos;
		do {
			pos = pSrcStr.find(pSubstr);
			if (pos != std::string::npos) {
				pSrcStr.replace(pos, pSubstr.length(), pReplacestr);
			}
		} while (pos != std::string::npos);
	}


	const bool FindRecordDeclsVisitor::isDeclFrmCurrentSource(clang::Decl* pDecl)
	{
		std::string currentSrcFile = m_currentSrcFile;
		std::transform(currentSrcFile.begin(), currentSrcFile.end(), currentSrcFile.begin(),
		[](unsigned char c)->char {
			return (c == '\\') ? '/' : std::tolower(c);
		});

		const auto& srcManager = pDecl->getASTContext().getSourceManager();
		auto fileLoc = srcManager.getFileLoc(pDecl->getBeginLoc());
		auto declSrcFile = srcManager.getFilename(fileLoc).str();
		std::transform(declSrcFile.begin(), declSrcFile.end(), declSrcFile.begin(),
		[](unsigned char c)->char {
			return (c == '\\') ? '/' : std::tolower(c);
		});
		return (currentSrcFile == declSrcFile);
	}

	
	void FindRecordDeclsVisitor::removeSubStrings(std::string& pSrcStr, const std::vector<std::string>& pKeyStrs)
	{
		for (const std::string& keyStr : pKeyStrs)
		{
			if (!keyStr.empty()) 
			{
				size_t pos = pSrcStr.find(keyStr);
				while (pos != std::string::npos)
				{
					size_t charCount = keyStr.size();
					const size_t& endPos = (pos + charCount);
					if (endPos < pSrcStr.size() && pSrcStr.at(endPos) == ' ') {
						charCount++;
					}
					pSrcStr.erase(pos, charCount);
					pos = pSrcStr.find(keyStr, pos);
				}
			}
		}
	}


	const std::string FindRecordDeclsVisitor::extractParameterType(clang::ParmVarDecl* pParmVarDecl)
	{
		std::unordered_map<std::string, std::string> templateArgsTypeDefs;
		auto typedefStrValue = getTypeDefAliasForType(pParmVarDecl->getOriginalType(), templateArgsTypeDefs);
		if (typedefStrValue.has_value()) 
		{
			std::string typedefOrgTypeKey;
			const auto& qt = pParmVarDecl->getOriginalType().getCanonicalType().getNonReferenceType();
			if (qt->isFunctionPointerType()) {
				typedefOrgTypeKey = qt.getAsString();
				if (qt.getQualifiers().hasConst()) {
					typedefStrValue.emplace("const " + (typedefStrValue.value()));
				}
			}
			else if (qt->isPointerType()) {
				typedefOrgTypeKey = qt->getPointeeType().getUnqualifiedType().getAsString();
				removeSubStrings(typedefOrgTypeKey, { CONST, ENUM, CLASS, STRUCT });
			}
			else {
				typedefOrgTypeKey = qt.getUnqualifiedType().getAsString();
				removeSubStrings(typedefOrgTypeKey, { CONST, ENUM, CLASS, STRUCT });
			}
			templateArgsTypeDefs.insert(make_pair(typedefOrgTypeKey, typedefStrValue.value()));
		}
		auto typeStr = pParmVarDecl->getOriginalType().getCanonicalType().getAsString();
		removeSubStrings(typeStr, { ENUM, CLASS, STRUCT });
		for (auto itr : templateArgsTypeDefs)
		{
			const auto& tmpTypeStr = itr.first;
			const auto& tmpTypeDefStr = itr.second;
			replaceSubString(typeStr, tmpTypeStr, tmpTypeDefStr);
		}
		replaceSubString(typeStr, "_Bool", "bool");
		return typeStr;
	}


	const std::optional<std::string> FindRecordDeclsVisitor::getTypeDefAliasForType(const QualType& pQType, std::unordered_map<std::string, std::string>& pTemplateTypeDefs)
	{
		const Type* type = pQType.getTypePtrOrNull();
		if (!type) {
			return std::nullopt;
		}

		switch (pQType->getTypeClass())
		{
			case Type::TypeClass::Typedef: {
				return pQType.getAsString();
			}
			case Type::TypeClass::Elaborated: {
				const ElaboratedType* nxtType = dyn_cast<ElaboratedType>(type);
				return getTypeDefAliasForType(nxtType->getNamedType(), pTemplateTypeDefs);
			}
			case Type::TypeClass::LValueReference: {
				const LValueReferenceType* nxtType = dyn_cast<LValueReferenceType>(type);
				return getTypeDefAliasForType(nxtType->getPointeeType(), pTemplateTypeDefs);
			}
			case Type::TypeClass::Pointer: {
				const PointerType* nxtType = dyn_cast<PointerType>(type);
				return getTypeDefAliasForType(nxtType->getPointeeType(), pTemplateTypeDefs);
			}
			case Type::TypeClass::TemplateSpecialization: {
				const TemplateSpecializationType* templateSpclType = dyn_cast<TemplateSpecializationType>(type);
				for (const auto& templateArg : templateSpclType->template_arguments())
				{
					if (templateArg.getKind() == TemplateArgument::ArgKind::Type) 
					{
						std::unordered_map<std::string, std::string> tempTypeDefs;
						auto typeDefStr = getTypeDefAliasForType(templateArg.getAsType(), tempTypeDefs);
						if (typeDefStr.has_value())
						{
							const auto& qt = templateArg.getAsType().getUnqualifiedType().getNonReferenceType().getCanonicalType();
							std::string typeStr = (qt->isPointerType() ? qt->getPointeeType().getUnqualifiedType() : qt).getAsString();
							removeSubStrings(typeStr, { ENUM, CLASS, STRUCT });
							for (auto itr : pTemplateTypeDefs){
								const auto& tmpTypeStr = itr.first;
								const auto& tmpTypeDefStr = itr.second;
								replaceSubString(typeStr, tmpTypeStr, tmpTypeDefStr);
							}
							pTemplateTypeDefs.insert(std::make_pair(typeStr, typeDefStr.value()));
						}
					}
				}
				return std::nullopt;
			}
			default: return std::nullopt;
		}
	}


	bool FindRecordDeclsVisitor::VisitFunctionDecl(FunctionDecl* pFuncDecl)
	{
		if (!isInUserCode(pFuncDecl) || pFuncDecl->isDeleted() || pFuncDecl->isInAnonymousNamespace() ||
			(pFuncDecl->isGlobal() && pFuncDecl->isStatic()) ||
			pFuncDecl->isOverloadedOperator() || !isDeclFrmCurrentSource(pFuncDecl) ||
			pFuncDecl->getKind() == Decl::Kind::CXXDestructor ||
			pFuncDecl->getAccess() == AccessSpecifier::AS_private ||
			pFuncDecl->getAccess() == AccessSpecifier::AS_protected ||
			pFuncDecl->getLinkageInternal() != Linkage::ExternalLinkage) {
			return true;
		}

		const auto& functionName = pFuncDecl->getQualifiedNameAsString();
		if (pFuncDecl->isThisDeclarationADefinition() && isMemberFunctionOrInNamespace(pFuncDecl))
		{
			if (pFuncDecl->isInvalidDecl()) {
				m_unreflectedFunctions.push_back(functionName);
				return true;
			}

			std::string declSrcFile;
			for (auto funcAsDeclared : pFuncDecl->redecls()) {
				const auto& srcManager = funcAsDeclared->getASTContext().getSourceManager();
				const auto& fileLoc = srcManager.getFileLoc(funcAsDeclared->getBeginLoc());
				const auto& fileName = srcManager.getFilename(fileLoc).str();
				if (fileName.rfind(".h") != std::string::npos){
					declSrcFile = fileName;
					std::replace(declSrcFile.begin(), declSrcFile.end(), '\\', '/');
					break;
				}
			}

			if (!declSrcFile.empty()) {
				std::vector<std::string> parmTypes;
				const auto& params = pFuncDecl->parameters();
				for (unsigned index = 0; index < params.size(); index++)
				{
					if (params[index]->isInAnonymousNamespace()) {
						return true;
					}
					if (params[index]->isInvalidDecl()) {
						m_unreflectedFunctions.push_back(functionName);
						return true;
					}
					parmTypes.push_back(extractParameterType(params[index]));
				}
				ReflectableInterface::Instance().addFunctionSignature(m_currentSrcFile, declSrcFile, functionName, parmTypes);
			}
		}
		return true;
	}
}
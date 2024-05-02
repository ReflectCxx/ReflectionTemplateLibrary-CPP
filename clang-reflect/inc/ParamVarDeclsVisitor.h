#include "clang/AST/RecursiveASTVisitor.h"


namespace clang_reflect {

    class ParmVarDeclsVisitor : public clang::RecursiveASTVisitor<ParmVarDeclsVisitor>
    {
    public:

        bool VisitTypedefType(clang::TypedefType* pTypeDefType);
    };
}
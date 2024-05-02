#pragma once

#include <vector>
#include <string>
#include "clang/Tooling/Tooling.h"

namespace clang_reflect
{
    class ClangDriver
    {
        static std::unique_ptr<clang::tooling::CompilationDatabase> loadSourceFiles(const std::string& pRootDir);

        static void runClangParser(const std::string& pRootDir, const std::vector<std::string>& pSrcFiles, 
                                   std::unique_ptr<clang::tooling::CompilationDatabase> pCdb);

    public:

        static void compileSourceFiles(const std::string& pRootDir);
    };
}
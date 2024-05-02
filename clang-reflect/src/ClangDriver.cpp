#include <thread>
#include <set>

#include "ClangDriver.h"
#include "ASTParser.h"
#include "FileManager.h"
#include "Logger.h"
#include "IncludesManager.h"
#include "clang/Tooling/CompilationDatabase.h"


namespace clang_reflect
{
    std::unique_ptr<clang::tooling::CompilationDatabase> ClangDriver::loadSourceFiles(const std::string& pRootDir)
    {
        std::string errMsg;
        Logger::out("Loading source/header files.");
        auto cdb = clang::tooling::CompilationDatabase::loadFromDirectory(pRootDir, errMsg);
        if (!cdb)
        {
            Logger::out("CDB not found.");
            Logger::out("Iterating directory: " + pRootDir);
            FileManager::Instance().loadProjectFilePaths(pRootDir);
        }
        else {
            Logger::out("CDB loaded from directory: " + pRootDir);
        }
        return cdb;
    }


    void ClangDriver::compileSourceFiles(const std::string& pRootDir)
    {
        auto cdb = loadSourceFiles(pRootDir);
        if (cdb)
        {
            const auto& srcFiles = cdb->getAllFiles();
            Logger::out("Number of source files in CDB: " + std::to_string(srcFiles.size()));
            std::unordered_set<std::string> distinctSrcFiles(srcFiles.begin(), srcFiles.end());
            Logger::out("Number of distinct source files in CDB: " + std::to_string(distinctSrcFiles.size()));
            const auto& finalSrcFiles = std::vector<std::string>(distinctSrcFiles.begin(), distinctSrcFiles.end());
            runClangParser(pRootDir, finalSrcFiles, std::move(cdb));
        }
        else
        {
            auto& fileManager = FileManager::Instance();
            auto& srcFiles = fileManager.getSourceFilePaths();
            auto& headerFiles = fileManager.getHeaderFilePaths();
            IncludesManager::Instance().initSourceHeaderDependencyGraph(headerFiles, srcFiles);

            runClangParser(pRootDir, srcFiles, std::move(cdb));
        }
    }


    void ClangDriver::runClangParser(const std::string& pRootDir, const std::vector<std::string>& pSrcFiles, 
                                     std::unique_ptr<clang::tooling::CompilationDatabase> pCdb)
    {
        const int fileCount = pSrcFiles.size();

        Logger::resetDoneCounter(fileCount);

        //TODO: get the number of threads from command line
        const int numCores = /*0; //*/std::thread::hardware_concurrency() - 2;
        const int numThreads = (numCores <= 0 ? 1 : numCores);

        int endIndex = 0;
        int startIndex = 0;
        int indexOffset = fileCount / numThreads;
        int restOffset = fileCount % numThreads;
        std::vector<std::thread> threadPool;

        while (endIndex < fileCount - 1)
        {
            endIndex = startIndex + (indexOffset + (--restOffset >= 0 ? 1 : 0)) - 1;
            endIndex = (endIndex > fileCount - 1) ? (fileCount - 1) : endIndex;

            auto thread = std::thread(
                [&](const int pStartIndex, const int pEndIndex) {

                    ASTParser cxxParser(pRootDir, pSrcFiles, pCdb.get());
                    cxxParser.parseFiles(pStartIndex, pEndIndex);
                },
                startIndex, endIndex);
            threadPool.push_back(std::move(thread));
            startIndex = endIndex + 1;
        }

        Logger::out("Running with number of threads: " + std::to_string(threadPool.size()));

        for (auto& thread : threadPool) {
            thread.join();
        }
    }
}

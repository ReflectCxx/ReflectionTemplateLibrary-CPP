#pragma once

#include <string>
#include <vector>

namespace clang_reflect {

    class FileManager
    {
        std::vector<std::string> m_headerFiles;
        std::vector<std::string> m_sourceFiles;

        FileManager();
        ~FileManager();

    public:

        FileManager(const FileManager&) = delete;
        FileManager& operator=(const FileManager&) = delete;

        static FileManager& Instance();

        void loadProjectFilePaths(const std::string& pDir);

        const std::vector<std::string>& getHeaderFilePaths();

        const std::vector<std::string>& getSourceFilePaths();
    };
}
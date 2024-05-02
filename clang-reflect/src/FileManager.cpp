
#include "FileManager.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>

#include "Logger.h"

namespace {

    namespace fs = std::filesystem;

    void scanDirectory(const fs::path& pDirPath, std::vector<std::string>& pHeaderFiles, std::vector<std::string>& pSourceFiles)
    {
        try
        {
            auto flags = fs::directory_options::skip_permission_denied;
            for (auto itr = fs::recursive_directory_iterator(pDirPath, flags); itr != fs::recursive_directory_iterator(); ++itr) 
            {
                auto entry = *itr;
                try
                {
                    const auto& dirName = entry.path().filename().string();
                    //TODO: get these exclusions from user.
                    if (fs::is_directory(entry) && (dirName[0] == '.' || dirName.find("bin") != std::string::npos || dirName.find("pugixml") != std::string::npos)) {
                        itr.disable_recursion_pending();
                    }

                    if (fs::is_regular_file(entry))
                    {
                        std::string nativePath = entry.path().string();
                        std::string extension = entry.path().extension().string();
                        if (nativePath.find("build") == std::string::npos && nativePath.find("ThirdParty") == std::string::npos &&
                           (extension == ".c" || extension == ".cc" || extension == ".cxx" || extension == ".cpp")) {
                            std::replace(nativePath.begin(), nativePath.end(), '\\', '/');
                            pSourceFiles.push_back(nativePath);
                        }
                        if (extension == ".h" || extension == ".hxx" || extension == ".hpp" || extension == ".cfg" || extension == ".ini") {
                            std::replace(nativePath.begin(), nativePath.end(), '\\', '/');
                            pHeaderFiles.push_back(nativePath);
                        }
                    }
                }
                catch (const std::exception& e)
                {
                    clang_reflect::Logger::out("exception accessing file: " + entry.path().generic_string() + "\n\t" + e.what());
                }
            }
        }
        catch (const std::exception& e)
        {
            clang_reflect::Logger::out("exception iterating directory: " + pDirPath.generic_string() + "\n\t" + e.what());
        }
    }
}


namespace clang_reflect {

    FileManager::FileManager()
    {
    }

    FileManager::~FileManager()
    {
    }

    FileManager& FileManager::Instance()
    {
        static FileManager instance;
        return instance;
    }


    const std::vector<std::string>& FileManager::getHeaderFilePaths()
    {
        return m_headerFiles;
    }


    const std::vector<std::string>& FileManager::getSourceFilePaths()
    {
        return m_sourceFiles;
    }


    void FileManager::loadProjectFilePaths(const std::string& pDir)
    {
        fs::path directoryPath(pDir);
        if (fs::exists(directoryPath) && fs::is_directory(directoryPath))
        {
            scanDirectory(directoryPath, m_headerFiles, m_sourceFiles);
        }
        else
        {
            clang_reflect::Logger::out("invalid directory path.");
        }
    }
}
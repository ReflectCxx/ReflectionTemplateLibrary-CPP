
#include <filesystem>

#include "CommandLineParser.h"

namespace clang_reflect {

    const std::string CommandLineParser::m_interfaceDumpDir = std::filesystem::current_path().string();

    std::vector<std::string> CommandLineParser::m_arguments;

    const std::string& CommandLineParser::getBaseDirectory()
    {
        return m_arguments.at(1);
    }


    void CommandLineParser::parse(int argc, char* argv[])
    {
        m_arguments.clear();
        for (int i = 0; i < argc; ++i)
        {
            m_arguments.push_back(argv[i]);
        }
    }


    const std::string& CommandLineParser::getInterfaceDumpDir() {
        return m_interfaceDumpDir;
    }
}
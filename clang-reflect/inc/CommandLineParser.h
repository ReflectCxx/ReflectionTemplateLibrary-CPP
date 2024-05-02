#pragma once

#include <vector>
#include <string>

namespace clang_reflect {

    class CommandLineParser
    {
        static const std::string m_interfaceDumpDir;

        static std::vector<std::string> m_arguments;

        CommandLineParser();

    public:

        static void parse(int argc, char* argv[]);

        static const std::string& getBaseDirectory();

        static const std::string& getInterfaceDumpDir();
    };


}
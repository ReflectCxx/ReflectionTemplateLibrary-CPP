
#include <fstream>
#include <filesystem>

#include "Constants.h"
#include "Logger.h"
#include "ClangDriver.h"
#include "FileManager.h"
#include "CommandLineParser.h"
#include "ReflectableInterface.h"

int main(int argc, char* argv[])
{
    const auto& tsBegin = clang_reflect::Clock::now();

    clang_reflect::CommandLineParser::parse(argc, argv);

    const std::string& baseDir = clang_reflect::CommandLineParser::getBaseDirectory();

    clang_reflect::ClangDriver::compileSourceFiles(baseDir);

    clang_reflect::ReflectableInterface::Instance().dump();

    const auto& tsEnd = std::chrono::duration_cast<clang_reflect::Second> (clang_reflect::Clock::now() - tsBegin).count();

    clang_reflect::Logger::out("Total time elapsed: " + std::to_string(tsEnd) + "\n");

    return 0;
}
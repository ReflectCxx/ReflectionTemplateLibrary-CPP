#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <chrono>

namespace clang_reflect {

	static const char* const RESET = "\033[0m";
	static const char* const DARK_RED = "\033[31m";
	static const char* const RED = "\033[38;2;231;72;86m";
	static const char* const GREEN = "\033[32m";
	static const char* const YELLOW = "\033[33m";
	static const char* const BLUE = "\033[34m";
	static const char* const MAGENTA = "\033[35m";
	static const char* const CYAN = "\033[38;2;97;214;214m";
	static const char* const WHITE = "\033[37m";
	static const char* const TEAL = "\033[38;2;0;128;128m";
	static const char* const GREY = "\033[38;2;118;118;118m";

	static const char* const CLANG_REFLECT = "clang-reflect";

	static const char* const CONST = "const";
	static const char* const ENUM = "enum";
	static const char* const CLASS = "class";
	static const char* const STRUCT = "struct";

	static const char* const INC_MANAGERS_DATA = "incManagersData.txt";
	static const char* const CL_REFLECT_INTERFACE = "clReflectInterface.txt";

	using ErrorTuple = std::tuple<std::string, std::string, std::string>;

	using Clock = std::chrono::high_resolution_clock;

	using Second = std::chrono::duration<double, std::ratio<1> >;
}
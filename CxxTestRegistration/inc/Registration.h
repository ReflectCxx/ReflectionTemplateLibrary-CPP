#pragma once

#include <vector>

namespace rtl {
	class Function;
}

namespace test_mirror
{
	static void registerPodStdTypes(std::vector<rtl::Function>&);

	static void registerTypeComplex(std::vector<rtl::Function>&);

	static void registerTypeDate(std::vector<rtl::Function>&);

	static void registerTypeEvent(std::vector<rtl::Function>&);

	static void registerTypeCalender(std::vector<rtl::Function>&);

	static void registerTypePerson(std::vector<rtl::Function>&);

	static void registerTypeBook(std::vector<rtl::Function>&);

	static void registerTypeLibrary(std::vector<rtl::Function>&);

	static void registerTypeAnimal(std::vector<rtl::Function>&);
}
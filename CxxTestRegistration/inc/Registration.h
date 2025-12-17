#pragma once

#include <vector>

namespace rtl {
	class Function;
}

namespace test_mirror
{
	extern void registerPodStdTypes(std::vector<rtl::Function>&);

	extern void registerTypeComplex(std::vector<rtl::Function>&);

	extern void registerTypeDate(std::vector<rtl::Function>&);

	extern void registerTypeEvent(std::vector<rtl::Function>&);

	extern void registerTypeCalender(std::vector<rtl::Function>&);

	extern void registerTypePerson(std::vector<rtl::Function>&);

	extern void registerTypeBook(std::vector<rtl::Function>&);

	extern void registerTypeLibrary(std::vector<rtl::Function>&);

	extern void registerTypeAnimal(std::vector<rtl::Function>&);

	extern void registerTypeStringFuncs(std::vector<rtl::Function>&);

	extern void registerTypeStringWrap(std::vector<rtl::Function>&);
	
	extern void registerTypeStringMute(std::vector<rtl::Function>&);

	extern void registerTypeStringConst(std::vector<rtl::Function>&);
	
	extern void registerTypeStringStatic(std::vector<rtl::Function>&);

//---------------------------------------------------------------------------------
	extern void addTypeIdPodStd(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdDate(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdEvent(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdCalender(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdPerson(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdBook(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdLibrary(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdAnimal(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdStringWrap(std::unordered_map<std::string, std::size_t>&); 
	
	extern void addTypeIdStringMute(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdStringConst(std::unordered_map<std::string, std::size_t>&);

	extern void addTypeIdStringStatic(std::unordered_map<std::string, std::size_t>&);
}
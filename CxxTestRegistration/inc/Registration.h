#pragma once

#include <vector>
#include <rtl_traits.h>

namespace rtl {
	class Function;
}

namespace test_mirror
{
    struct Register 
    {
        static void stdTypes(std::vector<rtl::Function>&);

        static void typeComplex(std::vector<rtl::Function>&);

        static void typeDate(std::vector<rtl::Function>&);

        static void typeEvent(std::vector<rtl::Function>&);

        static void typeCalender(std::vector<rtl::Function>&);

        static void typePerson(std::vector<rtl::Function>&);

        static void typeBook(std::vector<rtl::Function>&);

        static void typeLibrary(std::vector<rtl::Function>&);

        static void typeAnimal(std::vector<rtl::Function>&);

        static void typeStringFuncs(std::vector<rtl::Function>&);

        static void typeStringWrap(std::vector<rtl::Function>&);
	
        static void typeStringMute(std::vector<rtl::Function>&);

        static void typeStringConst(std::vector<rtl::Function>&);
	
        static void typeStringStatic(std::vector<rtl::Function>&);

        static void typeStringConstOverload(std::vector<rtl::Function>&);

        //---------------------------------------------------------------------------------
        static void typeIdPodStd(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdDate(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdEvent(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdCalender(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdPerson(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdBook(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdLibrary(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdAnimal(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdStringWrap(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdStringMute(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdStringConst(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdStringStatic(std::unordered_map<std::string, rtl::traits::uid_t>&);

        static void typeIdStringConstOverload(std::unordered_map<std::string, rtl::traits::uid_t>& id);
    };
}
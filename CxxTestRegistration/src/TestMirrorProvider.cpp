
#include <iostream>
#include <filesystem>
#include <CxxMirror.hpp>

#include "Registration.h"
#include "CxxMirrorToJson.h"
#include "TestMirrorProvider.h"

namespace test_mirror
{
    const rtl::CxxMirror& cxx::mirror()
    {
        static auto cxx_mirror = rtl::CxxMirror(
            []() {

                std::vector<rtl::Function> metaFns;

                Register::stdTypes(metaFns);
                Register::typeBook(metaFns);
                Register::typeDate(metaFns);
                Register::typeEvent(metaFns);
                Register::typePerson(metaFns);
                Register::typeAnimal(metaFns);
                Register::typeLibrary(metaFns);
                Register::typeComplex(metaFns);
                Register::typeCalender(metaFns);

                Register::typeStringWrap(metaFns);
                Register::typeStringMute(metaFns);
                Register::typeStringConst(metaFns);
                Register::typeStringFuncs(metaFns);
                Register::typeStringStatic(metaFns);

                return metaFns;
            }()
        );

        static const auto _= [&]()
        {
            const std::string pathStr = std::filesystem::current_path().string() + "/MyReflection.json";
            std::cout << "\n[ OUTPUT] test_mirror::cxx::mirror() ==> dumping 'CxxMirror' as JSON."
                      << "\n          file path: " << pathStr << "\n" << std::endl;
            rtl::CxxMirrorToJson::dump(cxx_mirror, pathStr);
            return 0;
        }();

        return cxx_mirror;
    }

    const rtl::traits::uid_t cxx::reflected_id(const std::string& pRecordName)
    {
        static std::unordered_map<std::string, rtl::traits::uid_t> nameIdMap = []()
        {
            std::unordered_map<std::string, rtl::traits::uid_t> idMap;
            
            Register::typeIdBook(idMap);
            Register::typeIdDate(idMap);
            Register::typeIdEvent(idMap);
            Register::typeIdPerson(idMap);
            Register::typeIdPodStd(idMap);
            Register::typeIdAnimal(idMap);
            Register::typeIdLibrary(idMap);
            Register::typeIdCalender(idMap);
            Register::typeIdStringWrap(idMap);
            Register::typeIdStringMute(idMap);
            Register::typeIdStringConst(idMap);
            Register::typeIdStringStatic(idMap);

            return idMap;
        }();

        const auto& itr = nameIdMap.find(pRecordName);
        return (itr == nameIdMap.end() ? rtl::index_none : itr->second);
    }
}
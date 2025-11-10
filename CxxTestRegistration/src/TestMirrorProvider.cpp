
#include <iostream>
#include <filesystem>

#include <CxxMirror.hpp>

#include "TestMirrorProvider.h"
#include "Registration.h"
#include "CxxMirrorToJson.h"

namespace test_mirror
{
    const rtl::CxxMirror& cxx::mirror()
    {
        static auto cxx_mirror = rtl::CxxMirror(
            []() {

                std::vector<rtl::Function> metaFns;

                registerPodStdTypes(metaFns);

                registerTypeBook(metaFns);
                registerTypeDate(metaFns);
                registerTypeEvent(metaFns);
                registerTypePerson(metaFns);
                registerTypeAnimal(metaFns);
                registerTypeLibrary(metaFns);
                registerTypeComplex(metaFns);
                registerTypeCalender(metaFns);

                registerTypeStringMute(metaFns);
                registerTypeStringConst(metaFns);
                registerTypeStringFuncs(metaFns);
                registerTypeStringStatic(metaFns);

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

    const std::size_t cxx::reflected_id(const std::string& pRecordName)
    {
        static std::unordered_map<std::string, std::size_t> nameIdMap = []()
        {
            std::unordered_map<std::string, std::size_t> idMap;
            
            addTypeIdBook(idMap);
            addTypeIdDate(idMap);
            addTypeIdEvent(idMap);
            addTypeIdPerson(idMap);
            addTypeIdPodStd(idMap);
            addTypeIdAnimal(idMap);
            addTypeIdLibrary(idMap);
            addTypeIdCalender(idMap);
            addTypeIdStringMute(idMap);
            addTypeIdStringConst(idMap);
            addTypeIdStringStatic(idMap);

            return idMap;
        }();

        const auto& itr = nameIdMap.find(pRecordName);
        return (itr == nameIdMap.end() ? rtl::index_none : itr->second);
    }
}
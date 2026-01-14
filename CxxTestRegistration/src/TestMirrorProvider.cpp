
#include <iostream>
#include <filesystem>

#include <rtl_builder.h>
#include <inc/CxxMirrorToJson.h>

#include "Registration.h"
#include "TestMirrorProvider.h"

namespace test_mirror
{
    const rtl::CxxMirror& cxx::mirror()
    {
        static auto cxx_mirror = rtl::CxxMirror(
            []() {

                std::vector<rtl::Function> fns;

                Register::stdTypes(fns);
                Register::typeBook(fns);
                Register::typeDate(fns);
                Register::typeEvent(fns);
                Register::typePerson(fns);
                Register::typeAnimal(fns);
                Register::typeLibrary(fns);
                Register::typeComplex(fns);
                Register::typeCalender(fns);
                
                Register::typeStringWrap(fns);
                Register::typeStringMute(fns);
                Register::typeStringConst(fns);
                Register::typeStringFuncs(fns);
                Register::typeStringStatic(fns);
                Register::typeStringConstOverload(fns);

                return fns;
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
            std::unordered_map<std::string, rtl::traits::uid_t> ids;
            
            Register::typeIdBook(ids);
            Register::typeIdDate(ids);
            Register::typeIdEvent(ids);
            Register::typeIdPerson(ids);
            Register::typeIdPodStd(ids);
            Register::typeIdAnimal(ids);
            Register::typeIdLibrary(ids);
            Register::typeIdCalender(ids);
            Register::typeIdStringWrap(ids);
            Register::typeIdStringMute(ids);
            Register::typeIdStringConst(ids);
            Register::typeIdStringStatic(ids);
            Register::typeIdStringConstOverload(ids);

            return ids;
        }();

        const auto& itr = nameIdMap.find(pRecordName);
        return (itr == nameIdMap.end() ? rtl::index_none : itr->second);
    }
}
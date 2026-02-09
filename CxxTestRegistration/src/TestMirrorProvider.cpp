
#include <iostream>
#include <filesystem>

#include <rtl_builder.h>
#include <inc/CxxMirrorToJson.h>

#include "reg_decls.h"
#include "TestMirrorProvider.h"

#include "Book.h"
#include "Person.h"
#include "Animal.h"
#include "Library.h"
#include "Complex.h"
#include "StringWrap.h"
#include "StringOps.h"
#include "StringMute.h"
#include "StringConst.h"
#include "StringStatic.h"
#include "StringConstOverload.h"

namespace {

    void registerStdTypes(std::vector<rtl::Function>& fns)
	{
        //  Registering int.
        fns.push_back(rtl::type().record<int>("int")
                                 .build());

        //  Registering type 'int' again, ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
        fns.push_back(rtl::type().record<int>("int")
                                 .build());

        //  Registering type 'int' again, but with different name. ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
        fns.push_back(rtl::type().record<int>("ccint")
                                 .build());

        //  Registering pod, reflecting- constructor, copy-constructor & destructor.
        fns.push_back(rtl::type().record<char>("char")
                                 .build());

        fns.push_back(rtl::type().record<std::string_view>("std::string_view")
                                 .build());

        //  Registers std::string class
        fns.push_back(rtl::type().member<std::string>()
                                 .methodConst("empty")
                                 .build(&std::string::empty));

    /*  Attempting to register the same type(`std::string`) again under a different name.
    *   RTL will ignore this duplicate registration and retain the first one. Emits a warning on the console:
    *   "[WARNING] Multiple registrations of the same type with different names detected."
    */  fns.push_back(rtl::type().member<std::string>()
                                 .methodConst<void>("empty")
                                 .build(&std::string::empty));

        fns.push_back(rtl::type().record<std::string>("std::string")
                                 .build());

        fns.push_back(rtl::type().member<std::string>()
                                 .constructor<const char*>()
                                 .build());

    /*  Attempting to register std::string_view, but the provided member function pointer belongs to std::string.
    *   RTL will ignore this registration. Emits a warning on the console:
    *   "[WARNING] Member function pointer does not belong to the class being registered!"
    */  fns.push_back(rtl::type().member<std::string_view>()
                                 .methodConst("empty")
                                 .build(&std::string::empty));

        //  Finally, register std::string_view with correct member-function-pointer
        fns.push_back(rtl::type().member<std::string_view>()
                                 .methodConst("empty")
                                 .build(&std::string_view::empty));
	}
}


const rtl::CxxMirror& cxx::mirror()
{
    static auto cxx_mirror = rtl::CxxMirror(
        []() {

            std::vector<rtl::Function> fns;

            registerStdTypes(fns);

            regs7::fn::init(fns);
            regs10::fn::init(fns);
            regs1::type0::init(fns);
            regs1::type1::init(fns);
            regs1::type2::init(fns);
            regs0::type0::init(fns);
            regs3::type0::init(fns);
            regs2::type0::init(fns);
            regs4::type0::init(fns);
            regs5::type0::init(fns);
            regs6::type0::init(fns);
            regs8::type0::init(fns);
            regs8::type1::init(fns);
            regs8::type2::init(fns);
            regs8::type3::init(fns);
            regs8::type4::init(fns);
            regs9::type0::init(fns);
            regs11::type0::init(fns);

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
    static std::unordered_map<std::string_view, rtl::traits::uid_t> nameIdMap = {

        {cxx::type::Book::id, rtl::traits::uid<Book>::value},
        {cxx::type::Person::id, rtl::traits::uid<Person>::value},
        {cxx::type::Animal::id, rtl::traits::uid<Animal>::value},
        {cxx::type::Library::id, rtl::traits::uid<Library>::value},
        {cxx::type::nsdate::Date::id, rtl::traits::uid<nsdate::Date>::value},
        {cxx::type::nsdate::Event::id, rtl::traits::uid<nsdate::Event>::value},
        {cxx::type::nsdate::Calender::id, rtl::traits::uid<nsdate::Calender>::value},

        {cxx::type::StrWrap::id, rtl::traits::uid<StrWrap>::value},
        {cxx::type::StrWrapA::id, rtl::traits::uid<StrWrapA>::value},
        {cxx::type::StrWrapB::id, rtl::traits::uid<StrWrapB>::value},
        {cxx::type::StrWrapC::id, rtl::traits::uid<StrWrapC>::value},
        {cxx::type::StrWrapD::id, rtl::traits::uid<StrWrapD>::value},

        {cxx::type::StrMute::id, rtl::traits::uid<StrMute>::value},
        {cxx::type::StrConst::id, rtl::traits::uid<StrConst>::value},
        {cxx::type::StrStatic::id, rtl::traits::uid<StrStatic>::value},
        {cxx::type::StrConstOverload::id, rtl::traits::uid<StrConstOverload>::value},

        { "int", rtl::traits::uid<int>::value },
        { "char", rtl::traits::uid<char>::value },
        { "std::string", rtl::traits::uid<std::string>::value },
        { "std::string_view", rtl::traits::uid<std::string_view>::value }
    };

    const auto& itr = nameIdMap.find(pRecordName);
    return (itr == nameIdMap.end() ? rtl::index_none : itr->second);
}
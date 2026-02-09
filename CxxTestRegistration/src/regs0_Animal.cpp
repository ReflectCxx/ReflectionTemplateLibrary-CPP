

#include "reg_ids.h"
#include "reg_decls.h"

#include "Animal.h"

namespace regs0::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<Animal>(cxx::type::Animal::id)
                                 .build());

        fns.push_back(rtl::type().member<Animal>()
                                 .constructor<const std::string &>().build());

        fns.push_back(rtl::type().member<Animal>()
                                 .methodConst(cxx::type::Animal::fn::getFamilyName::id)
                                 .build(&Animal::getFamilyName));

        fns.push_back(rtl::type().member<Animal>()
                                 .method<std::string &>(cxx::type::Animal::fn::setAnimalName::id)
                                 .build(&Animal::setAnimalName));

        fns.push_back(rtl::type().member<Animal>()
                                 .method<std::string &&>(cxx::type::Animal::fn::setAnimalName::id)
                                 .build(&Animal::setAnimalName));

        fns.push_back(rtl::type().member<Animal>()
                                 .method<const std::string &>(cxx::type::Animal::fn::setAnimalName::id)
                                 .build(&Animal::setAnimalName));

        fns.push_back(rtl::type().member<Animal>()
                                 .methodConst<const std::string &>(cxx::type::Animal::fn::setAnimalName::id)
                                 .build(&Animal::setAnimalName));

        fns.push_back(rtl::type().member<Animal>()
                                 .method(cxx::type::Animal::fn::setFamilyName::id)
                                 .build(&Animal::setFamilyName));

        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic(cxx::type::Animal::fn::getInstanceCount::id)
                                 .build(&Animal::getInstanceCount));

        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<std::string &>(cxx::type::Animal::fn::updateZooKeeper::id)
                                 .build(&Animal::updateZooKeeper));

        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<std::string &&>(cxx::type::Animal::fn::updateZooKeeper::id)
                                 .build(&Animal::updateZooKeeper));

        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<const std::string &>(cxx::type::Animal::fn::updateZooKeeper::id)
                                 .build(&Animal::updateZooKeeper));
    }
}



#include <rtl_builder.h>

#include "Animal.h"
#include "Registration.h"
#include "TestUtilsAnimal.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdAnimal(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(animal::class_, rtl::traits::uid<Animal>::value));
    }

	void Register::typeAnimal(std::vector<rtl::Function>& fns)
	{
		//  class 'Animal', methods & constructors.
        fns.push_back(rtl::type().record<Animal>(animal::class_)
                                 .build());

        fns.push_back(rtl::type().member<Animal>()
                                 .constructor<std::string>()
                                 .build());  //overloaded constructor.

        fns.push_back(rtl::type().member<Animal>()
                                 .method(animal::str_setFamilyName)
                                 .build(&Animal::setFamilyName));  //unique method, no overloads.
            
        //  Unique const-method, no overloads.
        fns.push_back(rtl::type().member<Animal>()
                                 .methodConst(animal::str_getFamilyName)
                                 .build(&Animal::getFamilyName));
        
        //  Overloaded method, taking const-ref as argument.
        fns.push_back(rtl::type().member<Animal>()
                                 .method<const std::string&>(animal::str_setAnimalName)
                                 .build(&Animal::setAnimalName));

        //  Overloaded const-method, taking const-ref as argument.
        fns.push_back(rtl::type().member<Animal>()
                                 .methodConst<const std::string&>(animal::str_setAnimalName)
                                 .build(&Animal::setAnimalName));

        //  Static method, taking const-ref as argument.
        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<const std::string&>(animal::str_updateZooKeeper)
                                 .build(&Animal::updateZooKeeper));
/*
    GCC here fails to automatically resolve the correct overloaded functor
    when both a lvalue reference and an rvalue overload exist.
    To disambiguate, explicitly cast the member function pointer, e.g.:

        static_cast<void (Animal::*)(std::string&)>(&Animal::setAnimalName)
*/
        fns.push_back(rtl::type().member<Animal>()
                                 .method<std::string&>(animal::str_setAnimalName)
                                 .build(static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName)));  //overloaded method, taking non-const lvalue reference as argument.
                
        fns.push_back(rtl::type().member<Animal>()
                                 .method<std::string&&>(animal::str_setAnimalName)
                                 .build(static_cast<void(Animal::*)(std::string&&)>(&Animal::setAnimalName)));  //overloaded method, taking rvalue reference as argument.
                
        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<std::string&>(animal::str_updateZooKeeper)
                                 .build(static_cast<std::string(*)(std::string&)>(&Animal::updateZooKeeper)));  //static method, taking non-const lvalue reference as argument.
                
        fns.push_back(rtl::type().member<Animal>()
                                 .methodStatic<std::string&&>(animal::str_updateZooKeeper)
                                 .build(static_cast<std::string(*)(std::string&&)>(&Animal::updateZooKeeper))); //static method, taking rvalue reference as argument.
	}
}
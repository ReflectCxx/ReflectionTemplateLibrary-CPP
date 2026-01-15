
#include <iostream>
#include <rtl_access.h>    // Reflection access interface.

#include "Person/Person.h"
#include "MyReflection/MyReflection.h"

int main()
{
    // Query reflected record for class `Person` (dynamic lookup).
    std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
    if (!classPerson) {
        std::cerr << "\n[error]     Class \"Person\" not found.";
        return 0; 
    }

    {   // Materialize default constructor.
        rtl::constructor<> personCtor = classPerson->ctor();
        if (!personCtor) {
            std::cerr << "\n[error]     Constructor with expected signature not found.";
            return 0;
        }

        // Construct a stack-allocated instance.
        // This will call the default constructor and since 
        // its placed in std::any, move(or copy) constructor will also be called.
        auto [err, person] = personCtor(rtl::alloc::Stack);
        if (err != rtl::error::None) { // Construction failed.
            std::cerr << "\n[error]     " << rtl::to_string(err);
            return 0;
        }
    }   // 'person' will get destroyed automatically.

    std::cout << std::endl;

    // Materialize constructor: Person(std::string, int).
    rtl::constructor<std::string, int> personCtor = classPerson->ctor<std::string, int>();
    if (!personCtor) {
        std::cerr << "\n[error]     " << rtl::to_string(personCtor.get_init_error());
        return 0;
    }

    // Construct a heap-allocated instance, constructor will be called only once.
    auto [err, robj] = personCtor(rtl::alloc::Heap, "Bernard Reflection", 42);
    if (err != rtl::error::None) { // Construction failed.
        std::cerr << "\n[error]     " << rtl::to_string(err);
        return 0;
    }

    // Lookup reflected method `getName`.
    std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
    if (!oGetName) { // Method not found.
        std::cerr << "\n[error]     Method \"getName\" not found.";
        return 0;
    }

    {   // Materialize complete type-aware caller.
        rtl::method<Person, std::string()> getName = oGetName->targetT<Person>().argsT().returnT<std::string>();

        if (getName) {
            Person alice("Alex Non-Reflected", 10);
            std::cout << std::endl;
            std::string nameStr = getName(alice)();
            std::cout << "\n[rtl-call]  complete type-aware, getName(), returns: " << nameStr;
        }
        else {
            std::cerr << "\n[error]     " << rtl::to_string(getName.get_init_error());
            return 0;
        }
    }
    std::cout << std::endl;
    {   // Materialize erased-target caller.
        rtl::method<rtl::RObject, std::string()> getName = oGetName->targetT().argsT().returnT<std::string>();

        if (getName) {
            auto [err, opt_ret] = getName(robj)();	// Invoke and receive erased return value.
            
            if (err != rtl::error::None) {
                std::cerr << "\n[error]     " << rtl::to_string(err);
                return 0;
            }
            if (opt_ret.has_value()) {
                std::cout << "\n[rtl-call]  return type-aware, erased-type 'Person', getName(), returns: " << opt_ret.value();	// Safely view the returned std::string.
            }
        }
    }
    std::cout << std::endl;
    {
        // Materialize erased-target & return caller.
        rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT().argsT().returnT();

        if (getName)
        {
            auto [err, ret] = getName(robj)();	// Invoke and receive erased return value.

            if (err != rtl::error::None) {
                std::cerr << "\n[error]     " << rtl::to_string(err);
                return 0;
            }
            if (ret.canViewAs<std::string>()) {
                const std::string& name = ret.view<std::string>()->get();
                std::cout << "\n[rtl-call]  complete type-erased, getName(), returns: " << name;	// Safely view the returned std::string.
            }
        }
    }
    return 0;
}
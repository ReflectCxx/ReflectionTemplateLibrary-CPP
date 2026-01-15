
#include <rtl_builder.h>

#include "MyReflection.h"
#include "../Person/Person.h"

const rtl::CxxMirror& cxx::mirror()
{
    static auto cxx_mirror = rtl::CxxMirror({

        // Register class 'Person' ('record' is general term used for 'struct/class') -
        rtl::type().record<Person>("Person").build(), // Registers default/copy ctor as well.

        // Register user defined ctor -
        rtl::type().member<Person>().constructor<std::string, int>().build(),

        // Register method
        rtl::type().member<Person>().method("getName").build(&Person::getName)
    });

    return cxx_mirror;
}

#include <iostream>
#include <rtl_access.h>    // Reflection access interface.

#include "Person/Person.h"
#include "MyReflection/MyReflection.h"

int main()
{
    // Query reflected record for class `Person` (dynamic lookup).
    std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
    if (!classPerson) { return 0; } // Class not registered.

    // Get constructor overload: Person(const char*, int).
    rtl::constructor<const char*, int> personCtor = classPerson->ctor<const char*, int>();
    if (!personCtor) { return 0; } // Constructor with expected signature not found.

    // Construct a stack-allocated instance; returns {error, RObject}.
    auto [err, robj] = personCtor(rtl::alloc::Stack, "John", 42);

    if (err != rtl::error::None) { return 0; } // Construction failed.

    // Lookup reflected method `setAge`.
    std::optional<rtl::Method> oSetAge = classPerson->getMethod("setAge");
    if (!oSetAge) { return 0; } // Method not found.

    // When target/return types are known (fastest path).
    {
        // Materialize typed method: Person::setAge(int) -> void.
        rtl::method<Person, void(int)> setAge = oSetAge->targetT<Person>()
                                                       .argsT<int>().returnT<void>();
        if (setAge) {
            Person person("Alex", 24);
            setAge(person)(25); // Near-zero-overhead dispatch (pointer-level cost).
        }
    }

    // When target/return types are erased (more flexible).
    {
        // Materialize erased method: RObject target, erased return.
        rtl::method<rtl::RObject, rtl::Return(int)> setAge = oSetAge->targetT()
                                                                    .argsT<int>().returnT();
        if (setAge) {
            // Slightly slower than typed path; comparable to std::function.
            auto [err, ret] = setAge(robj)(47);
            if (err == rtl::error::None) { /* call succeeded; return is void ('ret' empty)*/ }
        }
    }

    // Lookup reflected method `getName`.
    std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
    if (!oGetName) { return 0; } // Method not found.

    // Materialize erased method: getName() -> std::string.
    rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT()
                                                               .argsT().returnT();
    if (getName)
	{
        auto [err, ret] = getName(robj)();	// Invoke and receive erased return value.
        if (err == rtl::error::None && ret.canViewAs<std::string>()) {
            const std::string& name = ret.view<std::string>()->get();
            std::cout << name;	// Safely view the returned std::string.
        }
    }
    return 0;
}
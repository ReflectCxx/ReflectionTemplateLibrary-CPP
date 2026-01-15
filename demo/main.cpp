
#include <iostream>
#include <rtl_access.h>    // Reflection access interface.

#include "Person/Person.h"
#include "MyReflection/MyReflection.h"

namespace
{
    [[noreturn]] void die(rtl::error err)
    {
        std::cerr << "\n[error] " << rtl::to_string(err) << "\n";
        std::exit(0);
    }

    [[noreturn]] void die(const char* msg)
    {
        std::cerr << "\n[error] " << msg << "\n";
        std::exit(0);
    }
}

int main()
{
    {
        std::cout << "\n=== RTL Reflection Demo ===\n";

        // ------------------------------------------------------------
        // 1. Lookup reflected type
        // ------------------------------------------------------------
        std::cout << "\n[step] Looking up reflected class: Person";

        std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
        if (!classPerson) {
            die("Class \"Person\" not found.");
        }

        // ------------------------------------------------------------
        // 2. Default constructor (stack allocation)
        // ------------------------------------------------------------
        std::cout << "\n[step] Constructing Person() on stack";

        {
            rtl::constructor<> personCtor = classPerson->ctor();
            if (!personCtor) {
                die("Default constructor not found.");
            }

            auto [err, person] = personCtor(rtl::alloc::Stack);
            if (err != rtl::error::None) {
                die(err);
            }
        }
        std::cout << "  [ok]";
        std::cout << "\n    (stack instance destroyed automatically)";

        // ------------------------------------------------------------
        // 3. Parameterized constructor (heap allocation)
        // ------------------------------------------------------------
        std::cout << "\n\n[step] Constructing Person(\"Bernard Reflection\", 42) on heap";

        rtl::constructor<std::string, int> personCtor = classPerson->ctor<std::string, int>();

        if (!personCtor) {
            die(personCtor.get_init_error());
        }

        auto [err, robj] = personCtor(rtl::alloc::Heap, "Bernard Reflection", 42);
        if (err != rtl::error::None) {
            die(err);
        }
        std::cout << "  [ok]";

        // ------------------------------------------------------------
        // 4. Lookup reflected method
        // ------------------------------------------------------------
        std::cout << "\n\n[step] Looking up reflected method: getName";

        std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
        if (!oGetName) {
            die("Method \"getName\" not found.");
        }
        std::cout << "  [ok]";

        // ------------------------------------------------------------
        // 5. Full type-aware call
        // ------------------------------------------------------------
        std::cout << "\n\n[step] Calling getName() with full type awareness";

        {
            // Compile-time target + return type
            rtl::method<Person, std::string()> getName = oGetName->targetT<Person>()
                                                                 .argsT().returnT<std::string>();
            if (!getName) {
                die(getName.get_init_error());
            }

            Person alice("Alex Non-Reflected", 10);

            std::string nameStr = getName(alice)();
            std::cout << "\n[rtl-call]  getName() -> " << nameStr;
        }

        // ------------------------------------------------------------
        // 6. Erased-target, typed-return call
        // ------------------------------------------------------------
        std::cout << "\n\n[step] Calling getName() with erased target";

        {
            // Runtime object, compile-time return type
            rtl::method<rtl::RObject, std::string()> getName = oGetName->targetT()
                                                                       .argsT().returnT<std::string>();
            if (!getName) {
                die(getName.get_init_error());
            }

            auto [err, opt_ret] = getName(robj)();
            if (err != rtl::error::None) {
                die(err);
            }

            if (opt_ret.has_value()) {
                std::cout << "\n[rtl-call]  getName() -> " << opt_ret.value();
            }
        }

        // ------------------------------------------------------------
        // 7. Fully type-erased call
        // ------------------------------------------------------------
        std::cout << "\n\n[step] Calling getName() with erased target and return";

        {
            // Runtime object + runtime return type
            rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT()
                                                                       .argsT().returnT();
            if (!getName) {
                die(getName.get_init_error());
            }

            auto [err, ret] = getName(robj)();
            if (err != rtl::error::None) {
                die(err);
            }

            if (ret.canViewAs<std::string>())
            {
                const std::string& name = ret.view<std::string>()->get();
                std::cout << "\n[rtl-call]  getName() -> " << name;
            }

            // --------------------------------------------------------
            // 8. Clone + re-invoke
            // --------------------------------------------------------
            std::cout << "\n\n[step] Cloning reflected object and re-invoking";

            auto [err0, robj_cp] = robj.clone<rtl::alloc::Heap>();
            if (err0 != rtl::error::None) {
                die(err0);
            }

            auto [err1, ret2] = getName(robj_cp)();
            if (err1 != rtl::error::None) {
                die(err1);
            }

            if (ret2.canViewAs<std::string>())
            {
                const std::string& name = ret2.view<std::string>()->get();
                std::cout << "\n[rtl-call]  cloned getName() -> " << name;
            }
        }
    }
    std::cout << "\n\n=== Demo Complete ===\n";
    return 0;
}
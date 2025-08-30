
#include "RTLibInterface.h"
#include "MyReflectingType.h"

using namespace rtl;

namespace my_type
{
    const CxxMirror<0>& MyReflection()
    {
        static auto& cxx_mirror = CxxMirror<0>::reflect(
        {
        /*  Register a free(C - style) function within a namespace.
            If registered with a namespace, it must also be specified when querying:
                cxx_mirror().getFunction("ext", "sendString")
            Note: when registering free functions, the '&' operator is not required
            when passing the function pointer to build().
        */  type().nameSpace("ext").function("sendString").build(ext::sendString),


        /*  Another free (C-style) function inside a namespace.
            This example demonstrates overloaded function registration.
            Available overloads are:
                void sendAsString(Person)
                void sendAsString(Person&&)
                void sendAsString(const char*)

            Since multiple overloads exist, the compiler cannot automatically deduce
            the correct function pointer. Therefore, the parameter type must be explicitly
            specified with `.function<>()`.

            This guides `.build()` to correctly resolve the intended overload.
            Omitting the template type will result in a compile-time error.
        */  type().nameSpace("ext").function<const char*>("sendAsString").build(ext::sendAsString),


        /*  Next overload registration:
                void sendAsString(Person)
            As with other overloads, the signature must be explicitly specified
            so that `.build()` can select the correct function pointer.
        */  type().nameSpace("ext").function<Person>("sendAsString").build(ext::sendAsString),


        /*  And finally, the overload with an rvalue parameter:
                void sendAsString(Person&&)
            Again, the signature must be explicitly specified
            to ensure `.build()` resolves to the correct function pointer.
        */  type().nameSpace("ext").function<Person&&>("sendAsString").build(ext::sendAsString),


        /*  Register a class/struct type without a namespace.
            Since no namespace is provided, it will be queried directly by name, e.g.:
                cxx_mirror().getRecord("Person");
         
            This registration implicitly adds the default constructor, copy constructor,
            and destructor. Explicitly registering these members is not allowed and
            will result in a compile-time error.
         
            The order of registration does not matter- the type can be registered before
            or after its members. However, the type itself must be registered; otherwise,
            any attempted member registrations will be ignored and a warning will be
            displayed on the console.
        */  type().nameSpace().record<Person>("Person").build(),

        //  type().member<Person>().constructor().build(), // Default constructor, will not compile.
        //  type().member<Person>().constructor<Person&>().build(),  // Copy constructor, will not compile.
        //  type().member<Person>().constructor<Person&&>().build(), // Move constructor, will not compile.


        /*  Legal registration of an overloaded constructor.
            In this case, there are two possible overloads: `std::string&` and `const std::string&`.
         
            Note that we do not specify `&` in the template parameter. When calling this constructor  
            reflectively with a `std::string`, the argument is forwarded as a universal reference (&&).  
            By C++ rules, this binds naturally to `const std::string&`, without requiring any special  
            handling in RTL.  
         
            If the class provides only a `std::string&` constructor (and no `const std::string&`),  
            then this registration will fail to compile. Similarly, if three overloads exist-  
            `std::string`, `std::string&`, and `const std::string&`- the compiler itself will report  
            an ambiguity error.  
         
            You may explicitly register with `std::string&` or `const std::string&`, but RTL will  
            normalize types by stripping `const` and reference qualifiers during registration.  
        */  type().member<Person>().constructor<std::string>().build(),


        /*  Registers a regular non-const member-function.
            This function can only be called on a non-const `Person` object.
            Attempting to call it on a true-const `Person` object will result in `error::ConstCallViolation`.
            See test case: `non_const_method_semantics__on_true_const_target`.
                           `non_const_method_semantics__on_logical_const_target`
        */  type().member<Person>().method("getName").build(&Person::getName),


        /*  Registering a static member-function.
            Must be registered via `.methodStatic()`, otherwise it is a compile-time error.
            `.methodStatic()` restricts `build()` to only accept static member-function pointers.

            Runtime semantics:
            Static methods are independent of object state, so they can always be invoked
            regardless of whether the reflected context is const or non-const.
        */ type().member<Person>().methodStatic("getDefaults").build(&Person::getDefaults),


        /*  Registering a non-const member-function.
            Must be registered via `.method()`, otherwise it is a compile-time error.
            The non-const overload of `updateAddress` is automatically selected here, because
            `.method()` restricts `build()` to only accept non-const member-function pointers.

            If multiple overloads are available, the correct one is resolved at runtime.
            See test case: `const_based_overload_resolution_semantics__on_true_const_target` &
                           `const_based_overload_resolution_semantics__on_logical_const_target`
        */ type().member<Person>().method("updateAddress").build(&Person::updateAddress),


        /*  Registering a const member-function.
            Must be registered via `.methodConst()`, otherwise it is a compile-time error.
            The const overload of `updateAddress` is automatically selected here, because
            `.methodConst()` restricts `build()` to only accept const member-function pointers.

            If multiple overloads are available, the correct one is resolved at runtime.
            See test case: `const_based_overload_resolution_semantics__on_true_const_target` &
                           `const_based_overload_resolution_semantics__on_logical_const_target`
        */ type().member<Person>().methodConst("updateAddress").build(&Person::updateAddress),



        /*  Registers the member function `setTitle`, which only accepts an rvalue reference (`std::string&&`).
            To invoke this method reflectively, the argument type `std::string&&` must be explicitly specified.
            See test case: `perfect_forwarding_seamantics__rvalue_ref`.
        */  type().member<Person>().method("setTitle").build(&Person::setTitle),


        /*  Registers the overloaded member function `setOccupation` that accepts an rvalue-reference (`std::string&&`).
            Since this method has multiple overloads, RTL cannot automatically deduce the correct one (unlike `setTitle`,
            which had no overloads). Therefore, we must explicitly specify the rvalue-ref type in the `method` template parameter.
            For overload resolution, see test case: `perfect_forwarding_semantics__overload_resolution`.
        */  type().member<Person>().method<std::string&&>("setOccupation").build(&Person::setOccupation),


        /*  Registers the other overloaded version of `setOccupation` that accepts a const-lvalue-reference (`const std::string&`).
            Similar to the rvalue-ref case, this overload cannot be picked automatically, so we explicitly specify the
            `const std::string&` type in the `method` template parameter.
            For overload resolution, see test case: `perfect_forwarding_semantics__overload_resolution`.
        */  type().member<Person>().method<const std::string&>("setOccupation").build(&Person::setOccupation),


        /*  The method `setProfile` has two overloads.
            To register one, you must explicitly specify the parameter type in the template argument.  
            For example: `method<std::string>(...)`. Without this, compilation will fail.  
            Note: overload resolution happens at runtime (see test cases `overload_resolution_semantics__*`).  
        */  type().member<Person>().method<std::string>("setProfile").build(&Person::setProfile),


        /*  Example to illustrate overload behavior:

            Person person("Tim");
            person.setProfile(std::string("Tim's prof"));
                - This compiles fine, as it binds to `setProfile(std::string)`
                    (the version taking the argument by value).

            std::string profStr = "Tim's profile";
            person.setProfile(profStr);
                - This does not compile, because `profStr` is an lvalue.
                    It could bind to either `setProfile(std::string)` or
                    `setProfile(std::string&)`, creating ambiguity.

            However, RTL can successfully register both overloads by explicitly specifying
            the reference type in `method()`s template parameter, e.g. `method<std::string&>(...)`.
            Overload resolution still occurs at runtime. See test case `overload_resolution__setProfile`,
            which shows that even when explicitly registering the `std::string&` overload, a reflective call
            with an rvalue will still resolve to the `std::string` (by value) version, because that is the
            only syntactically valid match.
        */  type().member<Person>().method<std::string&>("setProfile").build(&Person::setProfile),


        /*  The method `getProfile` has only 'const' version, No non-const overload.
            Must be registered via `.methodConst()`, otherwise it is a compile-time error.
            Note: overload resolution happens at runtime (see test case `overload_resolution__setProfile`).  
        */  type().member<Person>().methodConst("getProfile").build(&Person::getProfile),
        });

        return cxx_mirror;
    }
}
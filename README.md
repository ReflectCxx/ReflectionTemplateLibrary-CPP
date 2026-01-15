# Reflection Template Library (RTL) – A Run-Time Reflection System for C++.

[![CMake](https://img.shields.io/badge/CMake-Enabled-064F8C?logo=cmake&logoColor=white)](https://cmake.org)
&nbsp;
[![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org)
&nbsp;
[![Build](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml/badge.svg?branch=develop)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml?query=branch%3Adevelop)
&nbsp;
[![Codecov](https://codecov.io/gh/ReflectCxx/ReflectionTemplateLibrary-CPP/branch/develop/graph/badge.svg)](https://codecov.io/gh/ReflectCxx/ReflectionTemplateLibrary-CPP)
&nbsp;
[![License: MIT](https://img.shields.io/badge/License-MIT-2EA44F?logo=open-source-initiative&logoColor=white)](LICENSE)

▶ **Try RTL Online**  [Open in GitHub Codespaces](https://github.com/codespaces/new?repo=ReflectCxx/ReflectionTemplateLibrary-CPP&quickstart=1)

**RTL** provides type-safe run-time reflection for modern C++ – combining compile-time guarantees with controlled run-time flexibility.

It enables name-based discovery and invocation of functions, constructors, and objects through a non-intrusive, type-safe reflection system that remains close to native execution.

For example, imagine you’ve written a simple function,
```c++
std::string complexToStr(float real, float img);
```
Using **RTL**, discover it by name and call dynamically:
```c++
rtl::function<std::string(float, float)> cToStr = cxx::mirror().getFunction("complexToStr")
                                                               ->argsT<float, float>()
                                                               .returnT<std::string>();
if(cToStr) {   // Function materialized?
    std::string result = cToStr(61, 35);  // Works!
}
// cxx::mirror() returns an instance of 'rtl::CxxMirror' (explained in Quick-Preview section)
```
> *No compile-time coupling to target symbols. No unsafe casting. No guesswork. Just run-time lookup and type-safe invocation.*

### ⚡ Performance

**RTL**’s reflective calls are comparable to `std::function` for fully type-erased dispatch, and achieve lower call overhead *(just a function-pointer hop)* when argument and return types are known.

## Design Highlights

* ***Single Source of Truth*** – All reflection metadata can be centralized in a single immutable `rtl::CxxMirror`, providing a consistent, thread-safe, duplication-free, and deterministic view of reflected state.

* ***Non-Intrusive & Macro-Free*** – Reflection metadata is registered externally via a builder-style API, with no macros, base classes, or intrusive annotations required on user types.

* ***Zero-Overhead by Design*** – Metadata is registered and resolved lazily. Reflection introduces no runtime cost beyond the features explicitly exercised by the user.

* ***Deterministic Lifetimes*** – Automatic ownership tracking of `Heap` and `Stack` instances with zero hidden deep copies.

* ***Cross-Compiler Consistency*** – Implemented entirely in standard C++20, with no compiler extensions or compiler-specific conditional behavior.

* ***Tooling-Friendly Architecture*** – Reflection data is encapsulated in a single immutable, lazily-initialized structure that can be shared with external tools and frameworks without compile-time type knowledge – suitable for serializers, debuggers, test frameworks, scripting engines, and editors.


[![Design Features](https://img.shields.io/badge/Doc-Design%20Features-blue)](./text-design-docs/DESIGN_PRINCIPLES_AND_FEATURES.md)
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-Syntax_&_Semantics-blueviolet)](./text-design-docs/RTL_SYNTAX_AND_SEMANTICS.md)

## A Quick Preview: Reflection That Looks and Feels Like C++

First, create an instance of `CxxMirror` –
```c++
auto cxx_mirror = rtl::CxxMirror({ /* ...register all types here... */ });
```
The `cxx_mirror` object provides access to the runtime reflection system. It enables querying, introspection, and instantiation of registered types without requiring compile-time type knowledge at the call site.
It can reside in any translation unit and is initialized on first use. To make it globally accessible in a controlled manner, a singleton interface can be used –
*`(MyReflection.h)`*
```c++
namespace rtl { class CxxMirror; }	// Forward declaration, no includes here!
struct cxx { static rtl::CxxMirror& mirror(); };	// The Singleton.
```
define and register everything in an isolated translation unit,
*`(MyReflection.cpp)`*
```c++
#include <rtl_builder.h> 	// Reflection builder interface.

rtl::CxxMirror& cxx::mirror() {
    static auto cxx_mirror = rtl::CxxMirror({   // Inherently thread safe.
        // Register free(C-Style) function -
	    rtl::type().function("complexToStr").build(complexToStr),
	    // Register class 'Person' ('record' is general term used for 'struct/class') -
	    rtl::type().record<Person>("Person").build(), // Registers default/copy ctor as well.
	    // Register user defined ctor -
	    rtl::type().member<Person>().constructor<std::string, int>().build(),
        // Register method -
	    rtl::type().member<Person>().method("getName").build(&Person::getName)
    });
    return cxx_mirror;
}
```
### RTL in action:

Lookup class `Person` by name (given at registration time).
```c++ 
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
if (!classPerson) { /* Class not registered. */ }
```
`rtl::CxxMirror` provides two lookup APIs that return reflection metadata objects: `rtl::Record` for class/struct, and `rtl::Function` for non-member functions.

From `rtl::Record`, registered member functions can be queried as `rtl::Method`. These are metadata descriptors (not callables) and are returned as `std::optional`, which will be empty if the requested entity is not found.

Callables are materialized by explicitly providing the argument types we intend to pass. If the signature is valid, the resulting callable can be invoked safely.
For example, the overloaded constructor `Person(std::string, int)` -
```c++
rtl::constructor<std::string, int> personCtor = classPerson->ctor<std::string, int>();
if (!personCtor) { /* Constructor with expected signature not found. */ }
```
Or the default constructor -
```c++
rtl::constructor<> personCtor = classPerson->ctor();
```
Instances can be created on the `Heap` or `Stack` with automatic lifetime management:
```c++
auto [err, robj] = personCtor(rtl::alloc::Stack, "John", 42);
if (err != rtl::error::None) { std::cerr << rtl::to_string(err); } // Construction failed.
```
The constructed object is returned wrapped in `rtl::RObject`. Heap-allocated objects are internally managed via `std::unique_ptr`, while stack-allocated objects are stored directly in `std::any`.

Now, Lookup a member-function by name -
```c++
std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
if (!oGetName) { /* Member function not registered */ }
```
And materialize a complete type-aware caller -
```c++
rtl::method<Person, std::string()> getName = oGetName->targetT<Person>()
                                                     .argsT().returnT<std::string>();
if (!getName) { 
    std::cerr << rtl::to_string(getName.get_init_err()); 
}
else {
    Person person("Alex", 23);
    std::string nameStr = getName(person)(); // Returns string 'Alex'.
}
```
The above `getName` invocation is effectively a native function-pointer hop, since all types are known at compile time.

If the concrete type `Person` is not accessible at the call site, its member functions can still be invoked by erasing the target type and using `rtl::RObject` instead. The previously constructed instance (`robj`) is passed as the target.
```c++
rtl::method<rtl::RObject, std::string()> getName = oGetName->targetT()
                                                            .argsT().returnT<std::string>();
auto [err, ret] = getName(robj)();	// Invoke and receive return as std::optional<std::string>.
if (err == rtl::error::None && ret.has_value()) {
    std::cout << ret.value();
}
```
If the return type is also not known at compile time,`rtl::Return` can be used:
```c++
rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT()
                                                            .argsT().returnT();
auto [err, ret] = getName(robj)();	// Invoke and receive return value std::string wrapped in rtl::RObject.
if (err == rtl::error::None && ret.canViewAs<std::string>()) {
    const std::string& name = ret.view<std::string>()->get();
    std::cout << name;	// Safely view the returned std::string.
}
```
### How RTL Fits Together

At a high level, every registered C++ type is encapsulated as an `rtl::Record`. Callable entities (constructors, free functions, and member functions) are materialized through `rtl::Function` and `rtl::Method`, all of which are discoverable via `rtl::CxxMirror`.

RTL provides the following callable wrappers, designed to be as lightweight and performant as `std::function` (and in many micro-benchmarks, faster when fully type-aware):

`rtl::function<...>` – Free (non-member) functions

`rtl::constructor<...>` – Constructors

`rtl::method<...>` – Non-const member functions

`rtl::const_method<...>` – Const-qualified member functions

`rtl::static_method<...>` – Static member functions

These callable types are regular value types: they can be copied, moved, stored in standard containers, and passed around like any other lightweight object.

When invoked, only type-erased callables return an `rtl::error`, with results provided as `rtl::RObject` when both the return and target types are erased or as `std::optional<T>` when only the target type is erased, while fully type-aware callables return `T` directly with no error wrapper.

### Allocation and Lifetime Management

* Heap (`alloc::Heap`) – objects are owned by an internal `std::unique_ptr` and destroyed when their `rtl::RObject` wrapper goes out of scope.

* Stack (`alloc::Stack`) – independent copies behave like normal stack values and clean up at scope exit.

* Move semantics – `Heap` objects follow `std::unique_ptr` rules (move transfers ownership, copy/assign disabled). `Stack` objects move like regular values.

* Return values – All returns are propagated back wrapped in `rtl::RObject`, cleaned up automatically at scope exit.

RTL doesn’t invent a new paradigm – it extends C++ itself. You create objects, call methods, and work with types as usual, but now safely at run-time.

## Reflection Features

* ✅ **Function Reflection** – Register and invoke C-style functions, supporting all kinds of overloads.
* ✅ **Class and Struct Reflection** – Register and dynamically reflect their methods, constructors, and destructors.
* ✅ **Complete Constructor Support** :
  * Default construction.
  * Copy/Move construction.
  * Any overloaded constructor.

* ✅ **Allocation Strategies & Ownership** :
  * Choose between `Heap` or `Stack` allocation.
  * Automatic move semantics for ownership transfers.
  * Scope-based destruction for `Heap` allocated instances.

* ✅ **Member Function Invocation** :
  * Static methods.
  * Const/Non-const methods.
  * Any overloaded method, Const/Non-Const based as well.

* ✅ **Perfect Forwarding**  – Binds LValue/RValue to correct overload.
* ✅ **Zero Overhead Forwarding** – No temporaries or copies during method forwarding.
* ✅ **Failure Semantics** – Explicit `rtl::error` diagnostics for all reflection operations (no exceptions, no silent failures).
* ✅ **Smart Pointer Reflection** – Reflect `std::shared_ptr` and `std::unique_ptr`, transparently access the underlying type, with full sharing and cloning semantics.
* 🟨 **Conservative Conversions** – Safely reinterpret reflected values without hidden costs. For example: treat an `int` as a `char`, or a `std::string` as a `std::string_view` / `const char*` — with no hidden copies and only safe, non-widening POD conversions. *(In Progress)*
* 🟨 **Materialize New Types** – Convert a reflected type `A` into type `B` if they are implicitly convertible. Define custom conversions at registration to make them available automatically. *(In Progress)*
* 🚧 **STL Wrapper Support** – Extended support for wrappers like `std::optional` and `std::reference_wrapper`. Return them, forward them as parameters, and access wrapped entities transparently. *(In Progress)*
* 🚧 **Relaxed Argument Matching** – Flexible parameter matching for reflective calls, enabling intuitive conversions and overload resolution. *(In Progress)*
* ❌ **Property Reflection**: Planned.
* ❌ **Enum Reflection**: Planned.
* ❌ **Composite Type Reflection**: Planned.
* ❌ **Inheritance Support**: Planned.

## How To build (Windows/Linux)

Create a build directory in the project root folder:

```sh
mkdir build && cd build
```

Generate a build system using **Unix Makefiles** or **Visual Studio** in CMake (use a compiler with C++20):

```sh
cmake -G "<Generator>"
```

To build, use any IDE applicable to the generator, or build straight from CMake:

```sh
cmake --build .
```

Run the `RTLTestRunApp` or `RTLBenchmarkApp` binaries generated in the `bin/` directory. (Tested with MSVC 19, GCC 14, and Clang 19)
* See `CxxTestRegistration/src/MyReflectionTests/` for introductory examples of type registration and reflective programming.
* See `RTLTestRunApp/src` for detailed test cases.
* See `RTLBenchmarkApp/src` for benchmarking implementations.
* Run `run_benchmarks.sh` to perform automated benchmarking, from micro-level tests to scaled workloads.
  
## Contributions

Contributions welcome! Report bugs, request features, or submit PRs on GitHub.

## Contact

GitHub issues or email at `reflectcxx@outlook.com`.

##

***C++ joins the reflection party! — why should Java & .NET have all the fun?***

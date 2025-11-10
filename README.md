# Reflection Template Library (RTL) — A Modern C++ Run-Time Reflection Framework

**RTL** brings rich, type-safe run-time reflection to modern C++ — combining compile-time safety with run-time flexibility.

[![CMake](https://img.shields.io/badge/CMake-Enabled-brightgreen)](https://cmake.org)&nbsp;[![C++20](https://img.shields.io/badge/C++-20-blue)](https://isocpp.org)&nbsp;[![RTL Build](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml/badge.svg?branch=release)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml?query=branch%3Arelease)&nbsp;[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

### 🪞 What’s “Reflection”?
Reflection lets you interact with code by `name` instead of by `type`. Imagine you’ve written a simple function,
```c++
std::string complexToStr(float real, float img);
```
**RTL** lets you call it dynamically:
```c++
rtl::function<std::string(float, float)> cToStr = cxx::mirror().getFunction("complexToStr")  // cxx::mirror?? see quick preview!
                                                               ->argsT<float, float>()
                                                               .returnT<std::string>();
if(cToStr) {   // Function materialized?
    std::string result = cToStr(61, 35);  // Works! (int → float? No problem.)
}
```
> *No includes. No compile-time linking. No argument type-casting. No guesswork. Just run-time lookup and type-safe invocation.*
### ⚡ Performance

Overhead? Practically none. **RTL**’s reflective calls — when return and argument types are known — are just a native function-pointer hop, often faster than `std::function`.

Yes — `rtl::function`’s dispatch is faster than `std::function`.

> *Microbenchmarks show reflective invocations through `rtl::function` have lower call overhead — a single, native pointer jump with no extra indirection. Once the functions start doing real work, both perform identically.*

### 💡 In One Line

*"RTL is a lightweight, static library that enables a robust, type-safe run-time reflection system for C++ — as flexible as in managed languages, yet as close as possible to native performance."*

## What’s more?

* ***Single Source of Truth*** – All metadata lives in one immutable `rtl::CxxMirror`, ensuring a consistent, thread-safe, duplication-free, and deterministic view of reflection data.

* ***Non-Intrusive & Macro-Free*** – Register reflection metadata externally via a clean builder pattern; no macros, base classes, or global registries.

* ***Zero-Overhead by Design*** – Metadata is registered and resolved only when used. Reflection introduces no cost beyond the features you explicitly employ.

* ***Exception-Free Surface*** – All predictable failures return error codes; no hidden throws.

* ***Cross-Compiler Consistency*** – Pure standard C++20, with no compiler extensions or conditional branching on compiler differences.

* ***Tooling-Friendly Architecture*** – Reflection data is encapsulated in a single immutable, lazily-initialized object that can be shared with tools and frameworks without compile-time type knowledge — ideal for serializers, debuggers, test frameworks, scripting engines, and editors.


[![Design Features](https://img.shields.io/badge/Doc-Design%20Features-blue)](./text-design-docs/DESIGN_PRINCIPLES_AND_FEATURES.md)
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-Syntax_&_Semantics-blueviolet)](./text-design-docs/RTL_SYNTAX_AND_SEMANTICS.md)

## A Quick Preview: Reflection That Looks and Feels Like C++

Create an instance of `CxxMirror`, passing all type information directly to its constructor — and you’re done!
```c++
auto cxx_mirror = rtl::CxxMirror({
	// Register free(C-Style) function -
	rtl::type().function("complexToStr").build(complexToStr),
	// Register class 'Person' ('record' is general term used for 'struct/class') -
	rtl::type().record<Person>("Person").build(), // Registers default/copy ctor as well.
	// Register user defined ctor -
	rtl::type().member<Person>().constructor<std::string, int>().build(),
    // Register methods -
	rtl::type().member<Person>().method("setAge").build(&Person::setAge),
	rtl::type().member<Person>().method("getName").build(&Person::getName)
});
```
The `cxx_mirror` object is your gateway to runtime reflection — it lets you query, introspect, and even instantiate types without any compile-time knowledge. It can live anywhere — in any translation unit, quietly resting in a corner of your codebase, remaining dormant until first access. All you need is to expose the `cxx_mirror` wherever reflection is required.

And what better way to do that than a **Singleton**: *`(MyReflection.h)`*
```c++
namespace rtl { class CxxMirror; }	// Forward declaration, no includes here!
struct cxx { static rtl::CxxMirror& mirror(); };	// The Singleton.
```
define and register everything in an isolated translation unit. *`(MyReflection.cpp)`*
```c++
#include <rtl/builder.h> 	// Reflection builder interface.

rtl::CxxMirror& cxx::mirror() {
    static auto cxx_mirror = rtl::CxxMirror({
        /* ...register all types here... */
    });
    return cxx_mirror;
}
```
> Singleton ensures one central registry, initialized once, accessible everywhere. No static coupling, no multiple instances, just clean runtime reflection.

**Without reflection:**

```c++
Person p("John", 42);
p.setAge(43);
std::cout << p.getName();
```

**With reflection:**

```c++

#include <rtl/access.h>    // Reflection access interface.
#include "MyReflection.h"

main()	// THESE API'S WORKS BUT DEPRECATED.
{
    // Look up the class by name
    std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");

    if (classPerson)  // Check has_value() before use.
    {
        // Create a stack-allocated instance. Returns- std::pair<rtl::error, rtl::RObject>
        auto [err, robj] = classPerson->create<alloc::Stack>("John", 42);
        if (err == rtl::error::None)  //Construction successful.
        {
            // Call setAge(43) on the reflected object
            std::optional<rtl::Method> setAge = classPerson->getMethod("setAge");
            if (setAge) {
                // Binds rtl::RObject & rtl::Method, calls with args.
                auto [err, ret] = setAge->bind(robj).call(43);  //'setAge' is void ('ret' empty).
                if (err == rtl::error::None) { /* Operation succeeded. */ }
            }

            // Call getName(), which returns std::string
            std::optional<rtl::Method> getName = classPerson->getMethod("getName");
            if (getName) {
                //Returns- std::pair<rtl::error, rtl::RObject>
                auto [err, ret] = getName->bind(robj).call();
                if (err == rtl::error::None && ret.canViewAs<std::string>())
                {
                    std::optional<rtl::view<std::string>> viewStr = ret.view<std::string>();
                    std::cout << viewStr->get();  // safe. validated above.
                }
            }
        }
    }
}

```
### `Heap` vs `Stack` Allocation and Lifetime Management

RTL lets you create reflected objects on the `Heap` or `Stack` with automatic lifetime management:

* Heap (`alloc::Heap`) — objects are owned by an internal `std::unique_ptr` and destroyed when their `rtl::RObject` wrapper goes out of scope.

* Stack (`alloc::Stack`) — independent copies behave like normal stack values and clean up at scope exit.

* Move semantics — `Heap` objects follow `std::unique_ptr` rules (move transfers ownership, copy/assign disabled). `Stack` objects move like regular values.

* Return values — All returns are propagated back wrapped in `rtl::RObject`, cleaned up automatically at scope exit.

RTL doesn’t invent a new paradigm — it extends C++ itself. You create objects, call methods, and work with types as usual, but now safely at run-time.

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

* ✅ **Perfect Forwarding** 🚀 – Binds LValue/RValue to correct overload.
* ✅ **Zero Overhead Forwarding** ⚡ – No temporaries or copies during method forwarding.
* ✅ **Namespace Support** 🗂️ – Group and reflect under namespaces.
* ✅ **Reflected Returns** 🔍 – Access return values whose types are unknown at compile-time. Validate against the expected type and use them as if the type was known all along.
* ✅ **Smart Pointer Reflection** 🔗 – Reflect `std::shared_ptr` and `std::unique_ptr`, transparently access the underlying type, and benefit from automatic lifetime management with full sharing and cloning semantics.
* 🟨 **Conservative Conversions** 🛡️ – Safely reinterpret reflected values without hidden costs. For example: treat an `int` as a `char`, or a `std::string` as a `std::string_view` / `const char*` — with no hidden copies and only safe, non-widening POD conversions. *(In Progress)*
* 🟨 **Materialize New Types** 🔄 – Convert a reflected type `A` into type `B` if they are implicitly convertible. Define custom conversions at registration to make them available automatically. *(In Progress)*
* 🚧 **STL Wrapper Support** 📦 – Extended support for wrappers like `std::optional` and `std::reference_wrapper`. Return them, forward them as parameters, and handle them seamlessly. *(In Progress)*
* 🚧 **Relaxed Argument Matching** ⚙️ – Flexible parameter matching for reflective calls, enabling intuitive conversions and overload resolution. *(In Progress)*
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

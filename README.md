# Reflection Template Library (RTL) – A Run-Time Reflection System for C++.

[![CMake](https://img.shields.io/badge/CMake-Enabled-brightgreen)](https://cmake.org)&nbsp;[![C++20](https://img.shields.io/badge/C++-20-blue)](https://isocpp.org)&nbsp;[![RTL Build](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml/badge.svg?branch=release)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml?query=branch%3Arelease)&nbsp;[![RTL Coverage](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/coverage.yml/badge.svg?branch=release)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/coverage.yml?query=branch%3Arelease)&nbsp;[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

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
/* cxx::mirror() returns an instance of 'rtl::CxxMirror', the reflection access interface
   for querying types and invoking function, method and constructors registered with RTL. */
```
> *No includes. No compile-time linking. No argument type-casting. No guesswork. Just run-time lookup and type-safe invocation.*

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

First, Create an instance of `CxxMirror`, passing all type information directly to its constructor –
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
The `cxx_mirror` object is your gateway to runtime reflection – it lets you query, introspect, and even instantiate types without any compile-time knowledge. It can live anywhere – in any translation unit, quietly resting in a corner of your codebase, remaining dormant until first access. All you need is to expose the `cxx_mirror` wherever reflection is required.

And what better way to do that than a **Singleton**,
*`(MyReflection.h)`*
```c++
namespace rtl { class CxxMirror; }	// Forward declaration, no includes here!
struct cxx { static rtl::CxxMirror& mirror(); };	// The Singleton.
```
define and register everything in an isolated translation unit,
*`(MyReflection.cpp)`*
```c++
#include <rtl/builder.h> 	// Reflection builder interface.

rtl::CxxMirror& cxx::mirror() {
    // Inherently thread safe.
    static auto cxx_mirror = rtl::CxxMirror({
        /* ...register all types here... */
    });
    return cxx_mirror;
}
```
Singleton ensures one central registry, initialized once, accessible everywhere. No static coupling, no multiple instances, just clean runtime reflection.

**RTL in action:**

```c++
#include <rtl/access.h>    // Reflection access interface.
#include "MyReflection.h"

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
            // View the underlying Person instance.
            const Person& person = robj.view<Person>()->get();

            // Near-zero-overhead dispatch (pointer-level cost).
            setAge(person)(47);
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
```
### Performance Model (Benchmarking Results)

* Non-erased RTL calls are equivalent to direct calls (≤ ~1 ns overhead).

* Erased calls incur a bounded overhead (worst case ~15–16 ns on trivial functions).

* For real workloads, erased calls typically add 3–10%, often less.

> RTL exposes performance tradeoffs directly in its API, delivering near-zero-overhead calls with full type information and a small, bounded cost with erased dispatch.

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

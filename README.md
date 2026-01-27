# Reflection Template Library (RTL) – A Run-Time Reflection System for C++.

[![License: MIT](https://img.shields.io/badge/License-MIT-2EA44F?logo=open-source-initiative&logoColor=white)](LICENSE)
&nbsp;
[![CMake](https://img.shields.io/badge/CMake-Enabled-064F8C?logo=cmake&logoColor=white)](https://cmake.org)
&nbsp;
[![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org)
&nbsp;
[![Build](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml/badge.svg?branch=release)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml?query=branch%3Arelease)
&nbsp;
[![Codecov](https://codecov.io/gh/ReflectCxx/ReflectionTemplateLibrary-CPP/branch/release/graph/badge.svg)](https://codecov.io/gh/ReflectCxx/ReflectionTemplateLibrary-CPP)
&nbsp;
[![Try RTL Online](https://img.shields.io/badge/Try-RTL%20Online-f48024?logo=github&logoColor=white)](https://github.com/codespaces/new?repo=ReflectCxx/RTL-Demo&quickstart=1)

RTL provides type-safe run-time reflection for C++, combining compile-time guarantees with run-time flexibility.

It enables name-based discovery and invocation of functions, constructors, and object members through a non-intrusive, type-safe reflection system that follows modern C++ idioms. For example, consider the following function:
```c++
std::string complexToStr(float real, float img);
```
Using RTL, you can discover this function by name and call it dynamically:
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

⚡ **Performance**

RTL’s reflective calls are comparable to `std::function`, and achieve lower overhead when argument and return types are fully specified.

## Design Highlights

* ***Single Source of Truth*** – All reflection metadata can be centralized in a single immutable `rtl::CxxMirror`, providing a consistent, thread-safe, duplication-free, and deterministic view of reflected state.

* ***Non-Intrusive & Macro-Free*** – Reflection metadata is registered externally via a builder-style API, with no macros, base classes, or intrusive annotations required on user types.

* ***Zero-Overhead by Design*** – Metadata can be registered and resolved lazily. Reflection introduces no runtime cost beyond the features explicitly exercised by the user.

* ***Hot-Loop Ready*** – Typed reflection calls exhibit near-zero overhead and scale like direct calls, making RTL suitable for performance-critical and tight-loop workloads. *([Performance Summary](docs/benchmark_summary.md))*

* ***Tooling-Friendly Architecture*** – Reflection metadata is encapsulated in a single immutable, lazily-initialized structure that can be shared with external tools and frameworks without compile-time type knowledge – suitable for serializers, debuggers, test frameworks, scripting engines, and editors.

## A Quick Preview: Reflection That Looks and Feels Like C++

First, create an instance of `rtl::CxxMirror`:
```c++
auto cxx_mirror = rtl::CxxMirror({ /* ...register all types here... */ });
```
The `cxx_mirror` object provides access to the runtime reflection system. It references metadata for all registered entities and supports name-based lookup. The object may reside in any translation unit. To make it globally accessible while ensuring lazy initialization, a singleton access interface can be used:
```c++
// MyReflection.h
namespace rtl { class CxxMirror; }	// Forward declaration, no includes here.
struct cxx { static rtl::CxxMirror& mirror(); };	// The singleton interface.
```
define and register everything in an isolated translation unit:
```c++
// MyReflection.cpp
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

Lookup the `Person` class by its registered name:
```c++ 
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
if (!classPerson) { /* Class not registered. */ }
```
`rtl::CxxMirror` returns two reflection metadata objects: `rtl::Record` for any registered type (class, struct, or POD) and `rtl::Function` for non-member functions.

From `rtl::Record`, registered member functions can be obtained as `rtl::Method`. These are metadata descriptors (not callables). Callable entities are materialized by explicitly providing the argument types we intend to pass.

For example, the overloaded constructor `Person(std::string, int)`:
```c++
rtl::constructor<std::string, int> personCtor = classPerson->ctorT<std::string, int>();
```
Or the default constructor:
```c++
rtl::constructor<> personCtor = classPerson->ctorT<>();
```
Instances can be created on the `Heap` or `Stack` with automatic lifetime management:
```c++
auto [err, robj] = personCtor(rtl::alloc::Stack, "John", 42);
if (err != rtl::error::None) { std::cerr << rtl::to_string(err); } // Construction failed.
```
The constructed object is returned as an `rtl::RObject` in the variable `robj`.

Looking up a member function by name:
```c++
std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
if (!oGetName) { /* Member function not registered */ }
```
And materialize a complete type-aware caller:
```c++
rtl::method<Person, std::string()> getName = oGetName->targetT<Person>().argsT()
                                                     .returnT<std::string>();
if (!getName) { // Member function with expected signature not found.
    std::cerr << rtl::to_string(getName.get_init_err()); 
}
else {
    Person person("Alex", 23);
    std::string nameStr = getName(person)(); // Returns string 'Alex'.
}
```
The above `getName` invocation is effectively a **native function-pointer hop**, since all types are known at compile time.

If the concrete type `Person` is not accessible at the call site, its member functions can still be invoked by erasing the target type and using `rtl::RObject` instead. The previously constructed instance (`robj`) is passed as the target:
```c++
rtl::method<rtl::RObject, std::string()> getName = oGetName->targetT().argsT()
                                                           .returnT<std::string>();
auto [err, ret] = getName(robj)();	// Invoke and receive return as std::optional<std::string>.
if (err == rtl::error::None && ret.has_value()) {
    std::string nameStr = ret.value();
}
```
If the return type is also not known at compile time,`rtl::Return` can be used:
```c++
rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT().argsT().returnT();

auto [err, ret] = getName(robj)();	// Invoke and receive rtl::RObject as return, wrapping std::string underneath.
if (err == rtl::error::None && ret.canViewAs<std::string>()) {
    std::string nameStr = ret.view<std::string>()->get(); // Safely view the returned std::string.
}
```
**[Explore the demo code here](https://github.com/ReflectCxx/RTL-Demo)**

### How RTL Fits Together

At a high level, every registered C++ type is encapsulated as an `rtl::Record`. Callable entities (functions, member functions and constructors) are materialized through `rtl::Function`, `rtl::Method` and `rtl::Record`, all of which are discoverable via `rtl::CxxMirror`.

👉 Deep Dive

[![Design Traits](https://img.shields.io/badge/Doc-Design%20Traits-blue)](./docs/DESIGN_PRINCIPLES_AND_FEATURES.md)
&nbsp;
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-Syntax_&_Semantics-blueviolet)](./docs/RTL_SYNTAX_AND_SEMANTICS.md)
&nbsp;
[![Benchmark Summary](https://img.shields.io/badge/Doc-Benchmark%20Summary-teal)](./docs/benchmark_summary.md)

### How to Build (Windows / Linux)
```sh
mkdir build && cd build
cmake ../ -G "<Generator>"    # Use a C++20-compatible compiler
cmake --build .
```
Run the generated binaries from `bin/`:

* `RTLTestRunApp` – Reflection tests and examples
* `RTLBenchmarkApp` – Performance benchmarks

Additional resources:

* `RTLTestRunApp/src` – Detailed test cases
* `RTLTestRunApp/src/MyReflectionTests/` – Tutorial example
* `RTLBenchmarkApp/src` – Benchmark implementations
* `run_benchmarks.sh` – Automated benchmark runs

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
* ✅ **Zero Overhead Forwarding** – No temporaries or copies during dispatch and arguments forwarding.
* ✅ **Failure Semantics** – Explicit `rtl::error` diagnostics for all reflection operations (no exceptions, no silent failures).
* ✅ **Smart Pointer Reflection** – Reflect `std::shared_ptr` and `std::unique_ptr`, transparently access the underlying type, with full sharing and cloning semantics.
* 🟨 **Conservative Conversions** – Safely reinterpret reflected values. For example: treat an `int` as a `char`, or a `std::string` as a `std::string_view` / `const char*` *(In Progress)*
* 🚧 **STL Wrapper Support** – support for wrappers like `std::optional` and `std::reference_wrapper`. Return them, forward them as parameters, and access wrapped entities transparently. *(In Progress)*
* 🚧 **Relaxed Argument Matching** – Flexible parameter matching for reflective calls, enabling safe conversions (ex- base/derived) and overload resolution. *(In Progress)*
* ❌ **Inheritance Support**: Next in line.
* ❌ **Composition Support**: Planned.
* ❌ **Property Reflection**: Planned.
* ❌ **Enum Reflection**: Planned.
* ❌ **Metadata iterators**: Planned.

## 💚 Support RTL’s Development

RTL is an actively maintained, production-oriented C++ runtime reflection system focused on performance, type safety, and real-world usability.

Sponsorship supports continued improvement of RTL’s core reflection capabilities, along with:

* Production-ready examples
* Tooling and documentation
* Cross-platform CI and testing

If you’re interested in advancing practical runtime reflection in C++ and supporting the continued evolution of RTL’s core capabilities, consider sponsoring the project.

[![Sponsor RTL](https://img.shields.io/badge/Sponsor-RTL_Development-ea4aaa?logo=github)](https://github.com/sponsors/ReflectCxx)

##

***C++ joins the reflection party! – why should Java have all the fun?***

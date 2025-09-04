# Reflection Template Library - Modern C++ Reflection Framework

*Reflection Template Library (RTL)* is a lightweight C++ runtime reflection library that enables introspection and dynamic manipulation of ***Types*** — allowing you to access, modify, and invoke objects at runtime without compile-time type knowledge.

RTL is implemented as a *static library* that organizes function pointers into `std::vector` tables, with each functor wrapped in a lambda. This design enables constant-time `O(1)` lookups while ensuring type-safe and efficient runtime access.

[![CMake](https://img.shields.io/badge/CMake-Enabled-brightgreen)](https://cmake.org)&nbsp;[![C++20](https://img.shields.io/badge/C++-20-blue)](https://isocpp.org)&nbsp;[![RTL Build](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml/badge.svg?branch=release)](https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP/actions/workflows/build.yml?query=branch%3Arelease)&nbsp;[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)


## What RTL Brings to Your Code

* ***Runtime Reflection for C++*** – Introspect and manipulate objects dynamically, similar to Java or .NET, but with modern C++ idioms.

* ***Single Source of Truth*** – All metadata lives in one immutable `rtl::CxxMirror`, ensuring a consistent, thread-safe, duplication-free, and deterministic view of reflection data.

* ***Non-Intrusive & Macro-Free*** – Register reflection metadata externally via a clean builder pattern; no macros, base classes, or global registries.

* ***Zero-Overhead by Design*** – Metadata is registered and resolved only when used. Reflection introduces no cost beyond the features you explicitly employ.

* ***Exception-Free Surface*** – All predictable failures return error codes; no hidden throws.

* ***Deterministic Lifetimes*** – Automatic ownership tracking of `Heap` and `Stack` instances with zero hidden deep copies.

* ***Cross-Compiler Consistency*** – Pure standard C++20, with no compiler extensions or conditional branching on compiler differences.

* ***Tooling-Friendly Architecture*** – Reflection data is encapsulated in a single immutable, lazily-initialized object that can be shared with tools and frameworks without compile-time type knowledge — ideal for serializers, debuggers, test frameworks, scripting engines, and editors.


[![Design Features](https://img.shields.io/badge/Doc-Design%20Features-blue)](./Design-Docs/DESIGN_PRINCIPLES_AND_FEATURES.md)
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-Syntax_&_Semantics-blueviolet)](./Design-Docs/RTL_SYNTAX_AND_SEMANTICS.md)

## A Quick Preview: Reflection That Looks and Feels Like C++

```c++
#include "RTLibInterface.h" // Reflection access interface.
```
Create an instance of `CxxMirror`, passing all type information directly to its constructor — and you're done!
```c++
auto cxx_mirror = rtl::CxxMirror({
	/* ...register all types here... */
	rtl::type().record<Person>("Person").build(),
	rtl::type().member<Person>().constructor<std::string, int>().build(),
	rtl::type().member<Person>().method("setAge").build(Person::setAge),
	rtl::type().member<Person>().method("getName").build(Person::getName)
});
```

With just this much, you’ve registered your types and unlocked full runtime reflection. The `cxx_mirror` object is your gateway to query, introspect, and instantiate types at runtime — all without compile-time knowledge of those types, without strict static coupling.

***Without reflection:***

```c++
Person p("John", 42);
p.setAge(43);
std::cout << p.getName();
```

***With reflection:***

```c++
// Look up the class by name
std::optional<rtl::Record> classPerson = cxx_mirror.getRecord("Person");

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
```
### `Heap` vs `Stack` Allocation and Lifetime Management

RTL lets you create reflected objects on the `Heap` or `Stack` with automatic lifetime management:

* Heap (`alloc::Heap`) — objects are owned by an internal `std::unique_ptr` and destroyed when their `rtl::RObject` wrapper goes out of scope.

* Stack (`alloc::Stack`) — independent copies behave like normal stack values and clean up at scope exit.

* Move semantics — `Heap` objects follow `std::unique_ptr` rules (move transfers ownership, copy/assign disabled). `Stack` objects move like regular values.

* Return values — All returns are propagated back wrapped in `rtl::RObject`, with temporaries (e.g. smart pointers) cleaned up automatically at scope exit.

RTL doesn’t invent a new paradigm — it extends C++ itself. You create objects, call methods, and work with types as usual, but now safely at runtime.

## Reflection Features

* ✅ **Function Reflection** 🔧 – Register and invoke C-style functions, supporting all kinds of overloads.
* ✅ **Class and Struct Reflection** 🏗️ – Register and dynamically reflect their methods, constructors, and destructors.
* ✅ **Complete Constructor Support** 🏗️:
  * Default construction.
  * Copy/Move construction.
  * Any overloaded constructor.

* ✅ **Allocation Strategies & Ownership** 📂:
  * Choose between `Heap` or `Stack` allocation.
  * Automatic move semantics for ownership transfers.
  * Scope-based destruction for `Heap` allocated instances.

* ✅ **Member Function Invocation** 🎯:
  * Static methods.
  * Const/Non-const methods.
  * Any overloaded method, Const/Non-Const based as well.

* ✅ **Perfect Forwarding** 🚀 – Binds LValue/RValue to correct overload.
* ✅ **Zero Overhead Forwarding** ⚡ – No temporaries or copies during method forwarding.
* ✅ **Namespace Support** 🗂️ – Group and reflect under namespaces.
* ✅ **Reflected Returns** 🔍 – Access return values whose types are unknown at compile time. Validate against the expected type and extract the content safely.
* ✅ **Smart Pointer Reflection** 🔗 – Reflect `std::shared_ptr` and `std::unique_ptr`, transparently access the underlying type, and benefit from automatic lifetime management with full sharing and cloning semantics.
* 🟨 **Conservative Conversions** 🛡️ – Safely reinterpret reflected values without hidden costs. For example: treat an `int` as a `char`, or a `std::string` as a `std::string_view` / `const char*` — with no hidden copies and only safe, non-widening POD conversions. *(In Progress)*
* 🟨 **Materialize New Types** 🔄 – Convert a reflected type `A` into type `B` if they are implicitly convertible. Define custom conversions at registration to make them available automatically. *(In Progress)*
* 🚧 **STL Wrapper Support** 📦 – Extended support for wrappers like `std::optional` and `std::reference_wrapper`. Return them, forward them as parameters, and access wrapped entities transparently. *(In Progress)*
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

Run the **CxxRTLTestApplication** binary generated in the `../bin` folder. *(Tested MSVC-19, GCC-14 & Clang-19)*
* See `CxxRTLTypeRegistration/src/MyReflectionTests/` for introductory type registration & reflective programming examples.
* See `CxxRTLTestApplication/src` for detailed test cases.

## Contributions

Contributions welcome! Report bugs, request features, or submit PRs on GitHub.

## Contact

GitHub issues or email at `reflectcxx@outlook.com`.

##

***C++ joins the reflection party! — why should Java & .NET have all the fun?***

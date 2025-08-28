# Reflection Template Library (RTL) - Modern C++ Reflection Framework

**Reflection Template Library (RTL)** is a lightweight C++ runtime reflection library that enables introspection and dynamic manipulation of user-defined types — allowing you to access, modify, and invoke objects at runtime without compile-time type knowledge.

RTL is implemented as a static library that organizes type-safe function pointers into tables `(std::vector)`, with each pointer wrapped in a lambda. This design enables constant-time `O(1)` lookup and efficient runtime access.

[![CMake](https://img.shields.io/badge/CMake-Enabled-brightgreen)](https://cmake.org) 
[![C++20](https://img.shields.io/badge/C++-20-blue)](https://isocpp.org) 
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE) 
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-RTL_at_a_Glance:_Syntax_&_Semantics-blueviolet)](./Design-Docs/RTL_SYNTAX_AND_SEMANTICS.md)

## What RTL Brings to Your Code

* **Runtime Reflection for C++** – Introspect and manipulate objects dynamically, just like in Java or .NET, but in modern C++.

* **Single Source of Truth** – All metadata lives in one immutable `rtl::CxxMirror`, giving plugins and tools a consistent, thread-safe, duplication-free, and deterministic view of reflection data.

* **Non-Intrusive & Macro-Free** – Register reflection data externally with a clean builder pattern; no macros, no base classes, no global registries.

* **Const-By-Default Safety** – Everything is immutable unless explicitly mutable, preventing unintended side-effects in reflective code.

* **Exception-Free Surface** – All predictable failures return error codes; no hidden throws.

* **Deterministic Lifetimes** – Automatic ownership tracking of `Heap` and `Stack` instances with zero hidden deep copies.

* **Cross-Compiler Consistency** – Built entirely on standard C++20, no reliance on compiler extensions.

* **Tooling-Friendly** – Architecture designed to power serializers, debuggers, test frameworks, scripting, and editor integrations without compiler context.

* **Path to Higher-Level Abstractions** – Lays the foundation for ORMs, plugin systems, game editors, and live scripting directly in C++.

[![Design Philosophy & Vision](https://img.shields.io/badge/Doc-Philosophy%20%26%20Vision-blue)](./Design-Docs/DESIGN_PHILOSOPHY_AND_VISION.md)
[![Why RTL Matters](https://img.shields.io/badge/Doc-Why%20RTL%20Matters-blue)](./Design-Docs/WHY_CPP_REFLECTION_MATTERS.md)

## A Quick Preview: Reflection That Looks and Feels Like C++

Create an instance of `CxxMirror`, passing all type information directly to its constructor — and you're done!

```c++
rtl::CxxMirror cxx_mirror({
	/* register all types here */
	rtl::Reflect().record<Person>("Person").build(),
	rtl::Reflect().member<Person>().constructor<std::string, int>().build(),
	rtl::Reflect().member<Person>().method("setAge").build(&Person::setAge).build(),
	rtl::Reflect().member<Person>().method("getName").build(&Person::getName).build()
});
```

With just this much, you’ve registered your types and unlocked full runtime reflection. The cxx_mirror object is your gateway to query, introspect, and instantiate types at runtime — all without compile-time knowledge of those types, without strict static coupling, and even when direct type access isn’t available at runtime.

RTL’s API is designed to be small and intuitive. Its syntax mirrors familiar C++ patterns — but with strong safety guarantees. Every reflective operation checks types, ownership, and errors explicitly, so moving forward with reflection feels just as safe and predictable as writing normal C++ code.

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
if (classPerson)
{
    // Create a stack-allocated instance. Returns- std::pair<rtl::error, rtl::RObject>.
    auto [err, robj] = classPerson->create<alloc::Stack>("John", 42);
    if (err == rtl::error::None)
    {
        // Call setAge(43) on the reflected object
        std::optional<rtl::Method> setAge = classPerson->getMethod("setAge");
        if (setAge) {
			// Binds rtl::RObject & rtl::Method, calls with args; 'setAge' is void ('ret' empty).
            auto [err, ret] = setAge->bind(robj).call(43);	//Returns- std::pair<rtl::error, rtl::RObject>.
        }

        // Call getName(), which returns std::string
        std::optional<rtl::Method> getName = classPerson->getMethod("getName");
        if (getName) {
			//Returns- std::pair<rtl::error, rtl::RObject>.
            auto [err, ret] = getName->bind(robj).call();
            if (err == rtl::error::None && ret.canViewAs<std::string>())
            {
                std::optional<rtl::view<std::string>> viewStr = ret.view<std::string>();
                std::cout << viewStr->get();
            }
        }
    }
}
```

Reflection in RTL doesn’t force a new paradigm — it extends the one you already know. You create objects, call methods, and work with types exactly as you would in C++ — only now, you can do it at runtime, with the same level of type safety and clarity.

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
* ✅ **Reflected Returns** 🔍 – Access return values whose types are unknown at compile time. Validate against the expected type and use them as if the type was known all along.
* ✅ **Smart Pointer Reflection** 🔗 – Reflect `std::shared_ptr` and `std::unique_ptr`, transparently access the underlying type, and benefit from automatic lifetime management with full sharing and cloning semantics.
* ✅ **Conservative Conversions** 🛡️ – Safely reinterpret reflected values without hidden costs. For example: treat an `int` as a `char`, or a `std::string` as a `std::string_view` / `const char*` — with no hidden copies and only safe, non-widening POD conversions.
* ✅ **Materialize New Types** 🔄 – Convert a reflected type `A` into type `B` if they are implicitly convertible. Define custom conversions at registration to make them available automatically. *(In Progress)*
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

Run the **CxxRTLTestApplication** binary generated in the `../bin` folder. *(Tested MSVC-19, GCC-14 & Clang-19)*
* See `CxxRTLTypeRegistration/src/MyReflectionTests/` for more type registration & reflective programming examples.
* See `CxxRTLTestApplication/src` for test cases.

## Contributions

Contributions welcome! Report bugs, request features, or submit PRs on GitHub.

## Contact

GitHub issues or email at `reflectcxx@outlook.com`.

***C++ joins the reflection party! — why should Java & .NET have all the fun?***

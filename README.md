# Reflection Template Library (RTL) - Modern C++ Reflection Framework

**Reflection Template Library (RTL)** is a lightweight C++ runtime reflection library that enables introspection and dynamic manipulation of user-defined types — allowing you to access, modify, and invoke objects at runtime without compile-time type knowledge.

RTL is implemented as a static library that organizes type-safe function pointers into tables `(std::vector)`, with each pointer wrapped in a lambda. This design enables constant-time `O(1)` lookup and efficient runtime access.

[![CMake](https://img.shields.io/badge/CMake-Enabled-brightgreen)](https://cmake.org)
[![C++20](https://img.shields.io/badge/C++-20-blue)](https://isocpp.org)
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![Design Philosophy & Vision](https://img.shields.io/badge/Doc-Philosophy%20%26%20Vision-blueviolet)](./Design-Docs/DESIGN_PHILOSOPHY_AND_VISION.md)
[![Why RTL Matters](https://img.shields.io/badge/Doc-Why%20RTL%20Matters-blueviolet)](./Design-Docs/WHY_CPP_REFLECTION_MATTERS.md)
[![RTL Syntax & Semantics](https://img.shields.io/badge/Doc-RTL_at_a_Glance:_Syntax_&_Semantics-blueviolet)](./Design-Docs/RTL_SYNTAX_AND_SEMANTICS.md)

## What RTL Brings to Your Code

* **Runtime Reflection for C++** – Introspect and manipulate objects dynamically, just like in Java or .NET, but in modern C++.

* **Single Source of Truth** – All metadata lives in one immutable `rtl::CxxMirror`, giving plugins and tools a consistent, thread-safe, duplication-free, and deterministic view of reflection data.

* **Non-Intrusive & Macro-Free** – Register reflection data externally with a clean builder pattern; no macros, no base classes, no global registries.

* **Tooling-Friendly** – The same `rtl::CxxMirror` powers serializers, debuggers, test frameworks, scripting layers, and editor integrations without needing compiler context.

* **Const-By-Default Safety** – Everything is immutable unless explicitly mutable, preventing unintended side-effects in reflective code.

* **Exception-Free Surface** – All predictable failures return error codes; no hidden throws.

* **Deterministic Lifetimes** – Automatic ownership tracking of `Heap` and `Stack` instances with zero hidden deep copies.

* **Cross-Compiler Consistency** – Built entirely on standard C++20, no reliance on compiler extensions.

* **Path to Higher-Level Abstractions** – The architecture unlocks the same extensibility as Java/.NET reflection, enabling ORMs, serializers, plugin systems, game editors, and live scripting directly in C++.

## A Quick Preview: Reflection That Feels Like C++

Create an instance of `CxxMirror`, passing all type information directly to its constructor — and you're done!

  ```c++
  rtl::CxxMirror cxx_mirror({/* register all types here */});
  ```

  The `cxx_mirror` object acts as your gateway to query, introspect, and instantiate all registered types at runtime.

RTL’s API is designed to be small and intuitive. The syntax follows familiar C++ patterns, so working with reflection feels natural.

```c++
// Without reflection
Person p("John", 42);
p.setAge(43);
std::cout << p.getName();

// With reflection
auto classPerson = cxx_mirror.getRecord("Person");      // Get the class as 'rtl::Record'.

auto [err, robj] = classPerson->create<alloc::Stack>("John", 42);   // Get the instance (robj) as 'rtl::RObject'.

auto setAge = classPerson->getMethod("setAge");     // Get the method as 'rtl::Method'.

setAge->bind(robj).call(43);    // Bind the rtl::RObject with rtl::Method and make the call with arguments.

auto getName = classPerson->getMethod("getName");

auto [err2, ret] = getName->bind(robj).call();      // Get return value as rtl::RObject.

std::cout << ret.view<std::string>()->get();    // access return value as std::string.
```

The semantics don’t feel foreign: creating, binding, and calling are the same ideas you already use in C++ — just expressed through reflection.

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

Run the **CxxRTLTestApplication** binary generated in the `../bin` folder. *(Tested with Visual Studio 2022, GNU 14 & Clang 19)*

## How To Use

In this example, we'll reflect a simple Person class. `Person.h`:

```c++
class Person {
    int age;
    std::string name;
	
public:
    Person();
    Person(const std::string, int);

    void setAge(int);
    void setName(const std::string, const std::string&);

    int getAge() const;
    std::string getName() const;
};
```

### Step 1: Register the Class with `CxxMirror`

Manually register the class and its members when creating a **`CxxMirror`** object.

```c++
#include "RTLibInterface.h" // Single header: provides all registration & access interfaces.
#include "Person.h"         // User-defined types to be reflected.

using namespace rtl::access;
using namespace rtl::builder;

const CxxMirror& MyReflection()
{
    static const CxxMirror cxxReflection({
        // Register member functions
        Reflect().record<Person>("Person").method("setAge").build(&Person::setAge),
        Reflect().record<Person>("Person").method("getAge").build(&Person::getAge),
        Reflect().record<Person>("Person").method("setName").build(&Person::setName),
        Reflect().record<Person>("Person").method("getName").build(&Person::getName),

        // Registering any method (including but not limited to constructors) will  
        // automatically reflect the copy-constructor & destructor (if accessible).
        Reflect().record<Person>("Person").constructor().build(),  // Default constructor
        Reflect().record<Person>("Person").constructor<std::string, int>().build() // Parameterized constructor
    });

    return cxxReflection;
}
```

Registration syntax:

```c++
Reflect().nameSpace("..")   // Optional: specify namespace if the type is enclosed in one.
         .record<..>("..")  // Register class/struct type (template parameter) and its name (string).
         .method("..")      // Register function by name.
         .build(*);         // Pass function pointer.

Reflect().nameSpace("..")
         .record<..>("..")
         .constructor<..>() // Register constructor with template parameters as signature.
         .build();          // No function pointer needed for constructors.
```

### Step 2: Use the `Person` Class via Reflection

In `main.cpp`, use the **`Person`** class without directly exposing its type:

```c++
#include "RTLibInterface.h" // Reflection access interface.

// True runtime reflection – no compile-time access to types.
// Works without even knowing what it's reflecting.
extern const rtl::CxxMirror& MyReflection();

using namespace rtl::access;

int main()
{
//  Lazily-initialized reflection system (singleton-style, pay-only-when-you-use).
//  Get 'class Person' — returns a 'Record' representing the reflected class.
    std::optional<Record> classPerson = MyReflection().getClass("Person");

/*  Create an instance of 'class Person' using the default constructor.
    Choose between heap or stack allocation with 'alloc::Heap' or 'alloc::Stack'.
    Returns: std::pair<error, RObject>. RObject is empty if:
       * error != error::None (creation or reflection call failure).
       * OR the reflected function is 'void'.
    'RObject' wraps a type-erased object, which can be:
        * An instance created via reflection (constructor).
        * OR a value returned from any reflection-based call.
     Internally:
        * Uses std::unique_ptr for heap-allocated reflection-created instances.
        * Return values are unmanaged.
        * Copy/move behave as value-type copies:
            - Heap: follows semantics of unique_ptr.
            - Stack: creates distinct object copies.
*/  auto [err0, person0] = classPerson->create<alloc::Heap>();

//  Ensure object was created successfully.
    if (err0 != error::None)
        return -1;

//  Create instance via parameterized constructor.
    auto [err1, person1] = classPerson->create<alloc::Stack>(std::string("John Doe"), int(42));

//  Fetch a reflected method — returns optional 'Method'.
    std::optional<Method> setAge = classPerson->getMethod("setAge");
    if(!setAge)
        return -1;

//  Call method: returns [error code, return value].
    auto [err2, ret2] = setAge->bind(person0).call(42);

//  Alternative syntax (without bind, slightly slower).
    auto [err3, ret3] = (*setAge)(person1)(42);

//  Fetch and invoke another reflected method.
    std::optional<Method> setName = classPerson->getMethod("setName");
    const char* name = "Todd";  // will get converted to std::string due to strict-binding.
    std::string surname = "Packer";
//  use bind to specify strict-argument types explicitly. (enables Perfect-Forwarding.)
    auto [err4, ret4] = setName->bind<string, const string&>(personObj).call(name, surname);

//  Fetch method returning a value.
    std::optional<Method> getName = classPerson->getMethod("getName");

//  Call and retrieve return value.
    auto [err5, retName] = getName->bind(personObj).call();

    if (err5 == error::None && retName.canViewAs<std::string>())
    {
        const std::string& nameStr = retName.view<std::string>()->get();
        std::cout << nameStr << std::endl;
    }
    return 0; // Heap/Stack instances cleaned up via scope-based lifetime.
}
```

* See `CxxRTLTypeRegistration/src/MyReflection.cpp` for more type registration examples.
* See `CxxRTLTestApplication/src` for test cases.

## Contributions

Contributions welcome! Report bugs, request features, or submit PRs on GitHub.

## Contact

GitHub issues or email at `reflectcxx@outlook.com`.

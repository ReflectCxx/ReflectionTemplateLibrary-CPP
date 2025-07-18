# Reflection Template Library C++

The **Reflection Template Library for C++** enables introspection of user-defined types, allowing modification of objects at runtime without needing to know their actual types at compile time.

Static library, the core design maintains several tables of function pointers(registered by the user) wrapped in lambdas and providing a mechanism to access at runtime.

## Key Features

- **Builder Pattern**: Manual registration of types is simple and intuitive, with no mysterious macros involved.
- **Clean Code**: No reflection-related code needs to be added to class, struct, or function declarations or implementations— keeping your codebase clean and free of clutter.
- **Centralized Registration**: Manage all manual registrations in a single implementation unit, separate from the rest of your project code.
- **Simple Integration**: Just create an instance of `CxxMirror`, pass all type information to reflect as a constructor parameter, and you’re done!
  ```c++
  rtl::CxxMirror cxxReflection({/*.. Pass all type information to register..*/});
  ```
  The *cxxReflection* object (of type rtl::CxxMirror) provides interface to query and instantiate registered types.
- **Thread-Safe & Exception-Safe**: The library is designed to be thread-safe and exception-safe, providing error codes on possible failures to ensure robust operation.
- **Automatic Code Generation**: To generate manual registration code automatically, `clang-reflect` can be used. It is a work-in-progress tool available here: *https://github.com/ReflectCxx/clang-reflect*. This tool will generate registration code for any large project without requiring changes to your project’s code.

## How To build (Windows/Linux),

Create a build directory in project root folder.
```sh
    mkdir build && cd build
```
Generate a build system using **Unix Makefiles** or **Visual Studio**, in CMake. (Use compiler with C++20)
```sh
    cmake -G "<Generator>"
```   
to build, any IDE applicable to the generator can be used or you can also just build straight from CMake.
```sh
    cmake --build .
```
Run **CxxReflectionTests** binary, generated in ../bin folder. *(tested with Visual Studio(2022), gnu(14) & clang(19))*
## How To Use,
In this example, we'll reflect a simple Person class. `Person.h`,
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
### Step 1: Register the Class with 'CxxMirror'
Manually register the class and its members when creating a **`CxxMirror`** object.
```c++
#include "RTLibInterface.h"	// Single header, provides all registration & access interfaces.
#include "Person.h"	// User-defined types to be reflected.

using namespace rtl::access;
using namespace rtl::builder;

const CxxMirror& MyReflection() 
{
    static const CxxMirror cxxMirror({
        // Register member functions
        Reflect().record<Person>("Person").method("setAge").build(&Person::setAge),
        Reflect().record<Person>("Person").method("getAge").build(&Person::getAge),
        Reflect().record<Person>("Person").method("setName").build(&Person::setName),
        Reflect().record<Person>("Person").method("getName").build(&Person::getName),
	
        // Registering a constructor (default or overload) also implicitly registers the copy constructor (if accessible) and the destructor.
        Reflect().record<Person>("Person").constructor<Person>().build(),  // Default constructor
        Reflect().record<Person>("Person").constructor<Person>().build<std::string, int>()  // Constructor with parameters
    });

    return cxxMirror;
}
```
Registration syntax,
```c++
Reflect().nameSpace("..")   // Optional: specify namespace if the type is enclosed in one.
         .record<..>("..")  // Register class/struct type (template parameter) and its name (string).
         .method("..")      // Register function by name.
         .build(*);         // Pass function pointer.

Reflect().nameSpace("..")
         .record<..>("..")
         .constructor<..>() // Register constructor with template parameters as signature.
         .build<..>();      // No function pointer needed for constructors.
```
### Step 2: Use the 'Person' Class via Reflection
In main.cpp, use the **`Person`** class without directly exposing its type.
```c++
#include "RTLibInterface.h"  // Single header including reflection access interface.
extern const rtl::CxxMirror& MyReflection();
using namespace rtl::access;

int main()
{
//  Get 'class Person' — returns 'Record' representing reflected class.
    std::optional<Record> classPerson = MyReflection().getClass("Person");

/*  Create an instance of 'class Person' using the default constructor.
    You can choose between heap or stack allocation using 'alloc::Heap' or 'alloc::Stack'.
    Returns a tuple of: [error code, RObject]. RObject returned is empty if:
       * error != error::None (creation or reflection call failure).
       * OR if the reflected function is 'void' (doesn't return any value).
    'RObject' wraps a type-erased object, which can be:
        * An instance created via reflection (constructor).
        * OR a value returned from any reflection-based method/function call.
     Internally:
        * Uses shared_ptr for lifetime management (only for explicitly heap-allocated instances).
        * Copy and move constructors behave as standard value-type copies:
            - For heap-allocated objects: sharing underlying instance via shared_ptr.
            - For stack-allocated objects: distinct object copies are created.
*/  auto [err0, personObj] = classPerson->create<alloc::Heap>();

//  Ensure object was created successfully.
    if (err0 != error::None)
        return -1;

/*  Create instance via parameterized constructor.
    Arguments must match in type and order.
*/  auto [err1, personObj2] = classPerson->create<alloc::Heap>(std::string("John Doe"), int(42));

//  Fetch a reflected method — returns optional 'Method'.
    std::optional<Method> setAge = classPerson->getMethod("setAge");

//  Call method: returns [error code, return value].
    auto [err2, ret1] = setAge->bind(personObj).call(42);

//  Alternative syntax (without bind).
    auto [err3, ret2] = (*setAge)(personObj)(42);

//  Fetch and invoke another reflected method.
    std::optional<Method> setName = classPerson->getMethod("setName");

    std::string name = "Todd";
    std::string surname = "Packer";

//  Example: using bind to specify argument types explicitly.
    auto [err4, ret3] = setName->bind<string, const string&>(personObj).call(name, surname);

//  Fetch method returning a value.
    std::optional<Method> getName = classPerson->getMethod("getName");

//  Call and retrieve return value.
    auto [err5, nameReturn] = getName->bind(personObj).call();

    if (err5 == error::None && nameReturn.canViewAs<std::string>())
    {
        const std::string& nameStr = nameReturn.view<std::string>()->get();
        std::cout << nameStr << std::endl;
    }

/*  Object lifetime:
    * Heap-allocated instance will be destroyed automatically when the last RObject sharing it goes out of scope.
    * Stack-allocated instance is cleaned up via scope-based lifetime (tracked internally but not reference-counted).
*/  return 0;
}
```
- Check, `CxxTypeRegistration/src/MyReflection.cpp` for all sort of type registrations.
- Check, `CxxReflectionTests/src` for test cases.

## Reflection Features

- ✅ **Function Reflection**: Register and invoke functions, including support for all overloads.
- ✅ **Class and Struct Reflection**: Register classes/structs and dynamically reflect their methods, constructors, and destructors.
- ✅ **Constructor Invocation**:
  - Invoke the default constructor.
  - Invoke copy constructors.
  - Invoke any overloaded constructor.
  - Allocate object on Heap or Stack.
- ✅ **Member Function Invocation**:
  - Dynamically invoke non-const member functions.
  - Dynamically invoke const member functions.
  - Dynamically invoke static member functions.
- ✅ **Supports Move Semantics**: `(powered by std::any)`
  - Implicitly invokes the move constructor when necessary.
  - Implicitly invokes the move assignment operator when necessary.
- ✅ **Automatic Resource Management**: Automatically invokes destructors for objects created on the heap via reflection.
- ✅ **Perfect Forwarding**: Precisely binds lvalues and rvalues to the correct method overload during invocation.
- ✅ **Zero Overhead Forwarding**: doesn't create any temporary variables/copies while forwarding arguments to methods.
- ✅ **Namespace Support**: Group and reflect classes, structs, and global functions under namespaces for better organization.
- 🚧 **Reflected Returns**: Access return values with types unknown at compile time but registered in the reflection system. `//In progress.`
- ❌ **Property Reflection**: Reflect properties of classes/structs, providing getter/setter methods.
- ❌ **Enum Reflection**: Add support for reflecting enums.
- ❌ **Composite Type Reflection**: Reflect classes with composite types that are also reflected.
- ❌ **Inheritance Support**: Add support for single, multiple, multilevel, and virtual inheritance.
  
## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributions
Contributions are welcome! If you find a bug, have a feature request, or want to contribute to the project, feel free to open an issue or submit a pull request on GitHub.

## Contact
For any questions, suggestions, or feedback, you can reach out via GitHub or email at `reflectcxx@outlook.com`.

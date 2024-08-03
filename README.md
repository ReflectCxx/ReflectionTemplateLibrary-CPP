# Reflection Template Library C++

The **Reflection Template Library for C++** enables introspection of user-defined types, allowing modification of objects at runtime without needing to know their actual types at compile time.

Static library, the core design maintains several tables of function pointers(registered by the user) wrapped in lambdas and providing a mechanism to access at runtime.

## Key Features

- **Builder Pattern**: Manual registration of types is simple and intuitive, with no mysterious macros involved.
- **Clean Code**: No reflection-related code needs to be added to class, struct, or function declarations or implementations— keeping your codebase clean and free of clutter.
- **Centralized Registration**: Manage all manual registrations in a single implementation unit, separate from the rest of your project code.
- **Simple Integration**: Just create an instance of `CxxMirror`, pass all type information to reflect as a constructor parameter, and you’re done!
  ```c++
  rtl::CxxMirror cxxReflection({/*.. Pass all type information ..*/});
  ```
  The *cxxReflection* object provides interface to query and instantiate registered types.
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
Run **CxxReflectionTests** binary, generated in ../bin folder. *(tested on windows and Ubuntu-20)*
## How To Use,
In this example, we'll reflect a simple Person class. `Person.h`,
```c++
class Person {
    int age;
    std::string name;
	
public:
    Person();
    Person(std::string, int);

    void setAge(int);
    void setName(std::string);

    int getAge() const;
    std::string getName() const;
};
```
### Step 1: Register the Class with 'CxxMirror'
Manually register the class and its members when creating a **`CxxMirror`** object.
```c++
#include "CxxMirrorBuilder.h"    // Provides registration interface.
#include "Person.h"              // User-defined types to be reflected.

using namespace rtl;

const CxxMirror& MyReflection() 
{
    static const CxxMirror cxxMirror({
        // Register member functions
        Reflect().record<Person>("Person").method("setAge").build(&Person::setAge),
        Reflect().record<Person>("Person").method("getAge").build(&Person::getAge),
        Reflect().record<Person>("Person").method("setName").build(&Person::setName),
        Reflect().record<Person>("Person").method("getName").build(&Person::getName),
	
        // Register constructors
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

int main() 
{
 // Get 'class Person', Returns 'Record' object associated with 'class Person'
    std::optional<Record> classPerson = MyReflection().getClass("Person");

 /* Create an instance of 'class Person' via reflection using the default constructor.
    Returns 'RStatus' and 'Instance' objects.
 */ auto [status, personObj] = classPerson->instance();
	
```
- `RStatus` provides an error code `(rtl::Error)` that indicates the success or failure of the reflection call, and it also contains the return value (if any) wrapped in `std::any`.
- `Instance` holds the created object (with its type erased), managed on the heap using `std::shared_ptr`.
```c++

 /* Create an instance via reflection using a parameterized constructor. 
    Argument types/order must match else call will fail, returning error-code in 'status'.
 */ auto [status, personObj] = classPerson->instance(std::string("John Doe"), int(42));

 // Get method of 'class Person'. Returns a callable 'Method' object.
    std::optional<Method> setAge = classPerson->getMethod("setAge");

 // Call methods on the 'Person' object. returns 'RStatus'.
    RStatus rst = setAge->on(personObj).call(int(42));
 // or with different syntax,
    RStatus rst = (*setAge)(personObj)(int(42));

 // Get method of 'class Person' that returns a value.
    std::optional<Method> getName = classPerson->getMethod("getName");

 // Call method, returns 'RStatus' containing return value.
    RStatus retName = getName->on(personObj).call();
 // or with different syntax,
    RStatus retName = (*getName)(personObj)();
  
 // Extract the return value.
    std::string nameStr = std::any_cast<std::string>(retName.getReturn());
}
```
- `std::any_cast` will throw an exception if correct type is not specified.
- Check, `CxxTypeRegistration/src/MyReflection.cpp` for all sort of type registrations.
- Check, `CxxReflectionTests/src` for test cases.

## Reflection Features,
-[x] Register and invoke functions, supporting all overloads.
-[x] Register classes/structs and reflect their methods, constructors, and destructors.
[x] Invoke the default constructor.
[x] Invoke the copy constructor with a non-const reference argument.
[x] Invoke the copy constructor with a const reference argument.
[x] Invoke any overloaded constructor.
[x] Invoke non-const member functions.
[x] Invoke const member functions.
[x] Invoke static member functions.
[x] Automatically invoke destructors for objects created on the heap.
[ ] Reflect properties of classes/structs, providing getter/setter methods.
[ ] Invoke functions with perfect forwarding.
[ ] Reflect enums.
[ ] Reflect classes with composite types that are also reflected.
[ ] Support single, multiple, multilevel, and virtual inheritance.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributions
Contributions are welcome! If you find a bug, have a feature request, or want to contribute to the project, feel free to open an issue or submit a pull request on GitHub.

## Contact
For any questions, suggestions, or feedback, you can reach out via GitHub or email at `neeraj.singh31285@outlook.com`.
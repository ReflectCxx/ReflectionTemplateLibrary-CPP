# Reflection Template Library C++

The **Reflection Template Library for C++** enables introspection of user-defined types, allowing modification of objects at runtime without needing to know their actual types at compile time.

Static library, the core design maintains several tables of function pointers(registered by the user) wrapped in lambdas and providing a mechanism to access at runtime.

## Key Features

- **Builder Pattern**: Manual registration of types is simple and intuitive, with no mysterious macros involved.
- **Clean Code**: No reflection-related code needs to be added to class, struct, or function declarations or implementations— keeping your codebase clean and free of clutter.
- **Centralized Registration**: Manage all manual registrations in a single implementation unit, separate from the rest of your project code.
- **Simple Integration**: Just create an instance of **`CxxMirror`**, pass all type information to reflect as a constructor parameter, and you’re done!
  ```c++
  rtl::CxxMirror cxxReflection({/*.. Pass all type information ..*/});
  ```
  The *cxxReflection* object provides an interface to query and instantiate registered types.
- **Thread-Safe & Exception-Safe**: The library is designed to be thread-safe and exception-safe, providing error codes on possible failures to ensure robust operation.
- **Automatic Code Generation**: To generate manual registration code automatically, *clang-reflect* can be used. It is a work-in-progress tool available here: *https://github.com/ReflectCxx/clang-reflect*. This tool will generate registration code for any large project without requiring changes to your project’s code.

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
- Class to reflect - **Person.h**
```c++
class Person
{
    int age;
    std::string name;
	
public:

    Person();
    Person(std::string, int);

    void setAge(int);
    void setName(std::string);
	
    int getAge();
    std::string getName();
};
```
- Do manual registration while creating **CxxMirror** object.
```c++

#include "CxxMirrorBuilder.h"    //provides registration interface.
#include "Person.h"    //User defined types, to be reflected.

using namespace rtl;

const CxxMirror& MyReflection() 
{
    static const CxxMirror cxxMirror({
	
        //Member functions registration
        Reflect().record("Person").method("setAge").build(&Person::setAge),
        Reflect().record("Person").method("getAge").build(&Person::getAge),
        Reflect().record("Person").method("setName").build(&Person::setName),
        Reflect().record("Person").method("getName").build(&Person::getName),
	
        //Constructor registration
        Reflect().record("Person").constructor<Person>().build(),	//ctor taking zero arguments
        Reflect().record("Person").constructor<Person>().build<string, int>()	//ctor with arguments, Person(string, int)
    });

    return cxxMirror;
}
```
Registration syntax,
```c++

Reflect().nameSpace("..")   //use if type is enclosed in a namespace, pass namespace as string.
         .record<..>("..")  //pass class/struct type as template parameter and name as string.
         .function("..")    //pass function name as string.
         .build(*);         //pass function pointer.

Reflect().nameSpace("..")
         .record<..>("..")
         .constructor<..>()	//constructor signature as template params.
         .build<..>();		//no function-pointer to pass for constructors.
```
- In main.cpp, Use **Person** class via Reflection without exposing the **Person Type**.
```c++
#include "RTLibInterface.h"		//single header that includes reflection-access-interface.
extern const rtl::CxxMirror& MyReflection();

int main()
{
  //get Class object,
  std::optional<Record> classPerson = MyReflection().getClass("Person");   //returns 'Record' object associated with 'class Person'

  //create instance of class 'Person' via reflection using default constructor,
  auto [status, personObj] = classPerson->instance();	//returns 'RStatus' and 'Instance' type objects respectively.
```
- **RStatus** contains error-code *(rtl::Error)* indicating reflection call success/failure and return value*(wrapped in std::any)* of call, if any.
- **Instance** contains the object created (with type erased) on heap, managed with *std::shared_ptr*.
```c++
  //create instance via reflection using parametrized constructor,
  auto [status, personObj] = classPerson->instance(std::string("John Doe"), int(42));	//argument types/order must match else call will fail.

  //calling methods of 'Person',
  std::optional<Method> setAge = classPerson.getMethod("setAge");	//(returns a callable 'Method' object)

  RStatus rst = setAge->on(personObj).call(int(42));	//returns 'RStatus', with no return value since 'setAge' is void.
  //or
  RStatus rst = (*setAge)(personObj)(int(42));

  //calling method that returns,
  std::optional<Method> getName = classPerson.getMethod("getName");
  
  RStatus retName = getName->on(personObj).call();	//returns 'RStatus', with value of type 'std::string'.
  //or
  RStatus retName = (*getName)(personObj)();
  
  //extract the return value,
  std::string nameStr = any_cast<string>(retName.getReturn());
}
```
- *std::any_cast* will throw exception if correct type is not specified.
- Check, *CxxTypeRegistration/src/MyReflection.cpp* for all sort of type registrations.
- Check, *CxxReflectionTests/src* for test cases.

## Reflection Features List (status),
- Create instances & call methods in complete absence of its type.
- Supports default & copy constructor along with all kinds of overloads.
- Supports all kinds of member function overloading, including constant function overloads(WIP) for *const objects*.
- Supports single, multiple, multilevel & virtual inheritance (WIP).
- Query a class for its super classes & for all its derived classes (vice-versa) (WIP).
- Resolves *Inheritance- Diamond Problem* (WIP).
- Supports *virtual methods - Overriding*.
- No need of any 3rd party dependencies.
- Manual registration with **NO MACROS**.

## TODO,
- Unit test cases (WIP)
- Class/Struct's Field reflection (Currently only methods are supported).
- Enum Class reflection.
- Access specifiers for reflection *(presently any Method/Field registerd is considered as public)*

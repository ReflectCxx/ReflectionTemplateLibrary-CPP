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
- The 'cxxReflection' object provides an interface to query and instantiate registered types.
- Automatic Code Generation: To generate manual registration code automatically, clang-reflect can be used. It is a work-in-progress tool available here: https://github.com/ReflectCxx/clang-reflect. This tool will generate registration code for any large project without requiring changes to your project’s code.

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
Run **CxxReflectionTests** binary, generated in ../bin folder. *(currently tested on windows and Ubuntu-20 only)*
## How To Use,
- Class to reflect - **Person.h** *(Independent of any code related to reflection)*
```c++
#pragma once
#include <string>

class Person
{
    int age;
    std::string name;
public:
    Person() :name("NULLSTR"), age(-1) {}
    Person(std::string pName, int pAge) : name(pName), age(pAge) {}

    int getAge() { return age; }
    void setAge(int pAge) { age = pAge; }
    std::string getName() { return name; }
    void setName(std::string pName) { name = pName; }
};
```
- Do manual registration while creating **CxxMirror** object.   *(..somwhere in some far far away .cpp file..)*
```c++

#include "CxxMirrorBuilder.h"	//Provides interface to RTL

//User defined types, to be reflected.
#include "Person.h"

using namespace rtl;

const CxxMirror& MyReflection() 
{
    static const CxxMirror cxxMirror(
    {
	//Function registration
	Reflect().record("Person").function("setAge").build(&Person::setAge),
	Reflect().record("Person").function("getAge").build(&Person::getAge),
	Reflect().record("Person").function("setName").build(&Person::setName),
	Reflect().record("Person").function("getName").build(&Person::getName),
	
	//Constructor registration
	Reflect().record("Person").constructor<Person>().build(),		//ctor taking zero arguments
	Reflect().record("Person").constructor<Person>().build<string, int>()		//ctor with arguments, Person(string, int)
    });
    return cxxMirror;
}
```
Registration syntax is simple **Builder Pattern**,
```c++
  
Reflect().nameSpace("..")	//use if type is enclosed in a namespace, pass namespace as string.
	 .record("..")		//pass class/struct name as string.
	 .function("..")	//pass function name as string.
	 .build(*);		//pass function pointer.

Reflect().nameSpace("..")		
	 .record("..")			
	 .constructor<..>()	//pass struct/class type as template parameter.
	 .build<..>();		//zero args for constructors, register constructor signature as template params.
```
- In main.cpp, Use **Person** class via Reflection without exposing the **Person Type**.
(*New underlying access-mechanism is in progress. These will not work currenty but final design will stay the same as below.*)
```c++
#include <iostream>
#include "CxxMirror.h"

using namespace std;
extern const rtl::CxxMirror& MyReflection();

int main()
{
```
Get Class & Method objects from reflection as **ReflClass** & **ReflMethod**,
```c++
  auto classPerson = MyReflection().getClass("Person");   //(returns instance of ReflClass)
  auto getAge = classPerson.getMethod("getAge");          //(returns instance of ReflMethod)
  auto getName = classPerson.getMethod("getName");
  auto setAge = classPerson.getMethod("setAge");
  auto setName = classPerson.getMethod("setName");
```
Create Instance using default constructor *(the one registered as **ctor::VOID**)*,
```c++
  //returns instance of Person wrapped in ReflObject<> which extends std::unique_ptr<>
  auto personObj1 = classPerson.instance();
```
Method Call Syntax : **ReflMethod(ReflObject<>).invoke<RETURN_TYPE>()**,
```c++
  int age = getAge(personObj1).invoke<int>();
  string name = getName(personObj1).invoke<string>();
  cout << "Person : { name : " << name << ", age: " << age << " }";   //Outs- Person : { name : NULLSTR, age: -1 }
```
No need to specify RETURN_TYPE if its void,
```c++
  setAge(personObj1).invoke(23);
  setName(personObj1).invoke(string("Scott"));
  age = getAge(personObj1).invoke<int>();
  name = getName(personObj1).invoke<string>();
  cout << "Person : { name : " << name << ", age: " << age << " }";     //Outs- Person : { name : Scott, age: 23 }
```
Create instance using overloaded constructor *(the one registered as **ctorArgs<string, int>**)*,
```c++
  auto personObj2 = classPerson.instance(string("John Doe"), 37);
  age = getAge(personObj2).invoke<int>();
  name = getName(personObj2).invoke<string>();
  cout << "Person : { name : " << name << ", age: " << age << " }";     //Outs- Person : { name : John Doe, age: 37 }
}
```
## Reflection Features,
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
- Exception handling (WIP)
- Access specifiers for reflection *(presently any Method/Field registerd is considered as public)*
- Light weight JSON Serialization/Deserialization feature.

# Reflection Template Library C++
###### (in development...)
Reflection Template Library for Modern C++
- Introspect a (user defined) class/struct/type, modify objects at run time without dealing with its type at "Compile Time".
- **Static Library**, core design is to maintain several tables of function/variable pointers, collected at compile time and providing a mechanism to access them in complete absence of their types at run time.
## Exclusive Features,
- Pure **Builder Pattern** for manual registration of types, super-easy to understand, No use of any "Mysterious MACROS" at all.</br>Thats Right- **NO MACROS!!**
- No need to add any bit of a code to any class/struct/type (to be reflected) declaration or to its implementation.</br>Yes, **No Code Littering, Keep it clean!**
- Manage all the manual registration of any required type in one single implementation unit, away from rest of the code in project.</br>Or in a **Class with Single Responsibility!**
- Create an Object of **"CxxMirror"**, pass all type information to reflect as constructor parameter and you're good to GO!
  ```c++
  const rtl::CxxMirror myReflection({/*.. Pass all type information ..*/});
  ```
- Wrap that powerful object in a singleton and use C++ Reflection with similar features as in Java or C#.
- *To generate this boilerplate code automatically, can be used **clang-reflect**
  https://github.com/neeraj31285/clang-reflect
  which is under development right now. Once completed, this boilerplate code can be generated automatically for any large projects.*

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

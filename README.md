# ReflectionTemplateLibrary-CPP
Reflection Template Library for Modern C++.
- Introspect a class/struct/type, modify objects at run time without dealing with its type at "Compile Time".
- **Static Library**, core functionality is built around the concept of **"Type Erasure"** using Lambdas, without utilizing any RTTI or dynamic_cast.
## Exclusive Features,
- Pure syntatic way of manual registration of types, No need to use any "Mysterious MACROS" at all. Thats Right- **NO MACROS!!**
- No need to add any bit of a code with any class/struct/type declearation or to its implementation. **No code littering, Keep it clean!**
- Manage all the manual registration of any required type in one single implementation unit, away from rest of the code in project.
- Create an Object of **"CppMirror<>"**, pass all type information to reflect as constructor parameter and you're good to GO!
- Wrap that powerful **(CppMirror<>)** object in a singleton and use C++ Reflection with richness as in Java or c# :)

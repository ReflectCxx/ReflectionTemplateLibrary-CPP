/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once


/*
* Provides the interface to register types and functions with RTL.
*
* Example usage:
*   rtl::type().ns("ns").function<int(std::string)>("func").build(&func);
*   rtl::type().ns("ns").record<MyClass>("MyClass").build();
*   rtl::type().member<MyClass>().constructor<std::string, int>().build();
*   rtl::type().member<MyClass>().method<void(const std::string&)>("setName").build(&MyClass::setName);
*
* Template parameters are required only for overload resolution:
*   - If the function/method is unique, template parameters are optional.
*   - If overloads exist and one of them has zero parameters, that overload
*     must be registered with <void>.
*   - Constructor overloads never require <void>, even if a zero-argument
*     constructor exists.
*
* Declared in namespace rtl::builder.
*/
#include "Reflect.hpp"


/*
* Interface for accessing user-defined classes/structs and their members
* (constructors, methods, and fields).
*
* A Record encapsulates all metadata for a reflected type and provides
* objects (Method, Function) to access its members.
*
* Record instances are retrieved from the global reflection mirror:
*   std::optional<rtl::Record> rec = cxx::mirror().getRecord("MyClass");
*
* Declared in namespace rtl.
*/
#include "Record.h"


/*
* Provides the interface for invoking global functions (optionally within
* a namespace) and static member functions of classes/structs.
*
* The class overloads operator(), allowing direct invocation:
*   auto [err, ret] = funcObj.bind().call(arg1, arg2);
*
* Global Function objects are obtained from the reflection mirror:
*   std::optional<rtl::Function> func = cxx::mirror().getFunction("ns", "funcName");
*
* Declared in namespace rtl.
*/
#include "Function.hpp"


/*
* Provides the interface for invoking member functions on reflected objects.
*
* Like Function, it overloads operator(), but instead of taking arguments
* directly, it first binds a target object and then allows calling with
* invoke(..args..).
*
* Example usage:
*   auto [err, ret] = methodObj.bind(targetObj).call(arg1, arg2);
*
* Difference between Function and Method:
*   - Function: bind() -> call(..args..)
*       Example -> funcObj.bind().call(..args..);
*
*   - Method: bind(targetObj) -> call(..args..)
*       Example -> methodObj.bind(targetObj).call(..args..);
*
* Declared in namespace rtl.
*/
#include "Method.hpp"


/*
* The root reflection container that aggregates all registrations.
* Users are expected to define a singleton CxxMirror that holds all
* records and functions:
*
*   namespace cxx {
*       const rtl::CxxMirror& mirror() {
*           static rtl::CxxMirror m = rtl::CxxMirror({
*               // registrations here...
*           });
*           return m;
*       }
*   }
*
* Declared in namespace rtl.
*/
#include "CxxMirror.hpp"
/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

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
#include <rtl/inc/Record.hpp>


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
#include <rtl/inc/Function.hpp>


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
#include <rtl/inc/Method.hpp>


/*
* The root reflection container that aggregates all registrations.
* example pattern-
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
#include <rtl/inc/CxxMirror.h>


#include <rtl/detail/inc/RObjectBuilder.hpp>
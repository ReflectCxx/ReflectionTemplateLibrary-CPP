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
#include <rtl/builder/Reflect.hpp>


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
#include <CxxMirror.h>
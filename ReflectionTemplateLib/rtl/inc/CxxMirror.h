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

#include <detail/inc/CxxReflection.h>

namespace rtl 
{   
/*  @class CxxMirror
    * Provides the primary interface to access registered functions and methods by name.
    * This is the single point of access to the entire reflection system.
    *
    * All type registrations happen during object construction.
    *
    * Objects of this class are regular stack-allocated objects (non-singleton) and are destroyed automatically when they go out of scope.
    * Copy constructor and assignment operator are deleted, instances can only be passed by reference or wrapped in a smart pointer.
    *
    * All inherited members are properly destroyed when the object is destroyed, except for the *functor containers*.
    *
    * Notes on Functor Storage:
    *   - Functor containers have static lifetime and are not part of this class or its base class.
    *   - This class (and its base) store only `Function` objects, which serve as hash-keys to look up actual functors.
    *   - Registering the same functor multiple times across different `CxxMirror` instances will not duplicate the functor in the container.
    *   - However, each `CxxMirror` instance will maintain its own unique `Function` hash-keys, even for the same functor.
    *   - Within a single `CxxMirror` object, registering the same functor multiple times is ignored (no duplicate `Function` hash-keys).
    *
    * Summary:
    *   - Functor objects are shared and static.
    *   - `Function` keys are per-instance.
    *   - Functor storage remains unaffected by the number of `CxxMirror` instances.
*/  
    class CxxMirror : public detail::CxxReflection
    {
    public:

        CxxMirror(CxxMirror&&) = default;
        CxxMirror(const CxxMirror&) = default;

        // Constructs CxxMirror using a set of Function objects. All other constructors are disabled.
        explicit CxxMirror(const std::vector<Function>& pFunctions);

        // Returns a Record containing function hash-keys for the given record ID.
        std::optional<Record> getRecord(const std::size_t pRecordId) const;

        // Returns a Record containing function hash-keys for the given record name.
        std::optional<Record> getRecord(const std::string& pRecordName) const;

        // Returns a Record containing function hash-keys for the given record name (overloaded for namespace support).
        std::optional<Record> getRecord(const std::string& pNameSpaceName, const std::string& pRecordName) const;

        // Returns a Function object for the given function name (non-member function).
        std::optional<Function> getFunction(const std::string& pFunctionName) const;

        // Returns a Function object for the given function name, within the specified namespace.
        std::optional<Function> getFunction(const std::string& pNameSpaceName, const std::string& pFunctionName) const;
    };
}
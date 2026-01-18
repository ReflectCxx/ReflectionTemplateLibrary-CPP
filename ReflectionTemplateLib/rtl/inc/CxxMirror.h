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
    /**
    * @class CxxMirror
    *
    * @brief Primary interface for accessing all registered types, functions, and methods by name.
    *
    * CxxMirror serves as the single point of entry to the entire reflection system.
    * All type, function, and method registrations occur during object construction.
    *
    * Instances of this class are regular, stack-allocated value-type objects.
    * The copy constructor is explicit, and the assignment operator is deleted.
    *
    * The class stores only metadata in the form of strings and PODs.
    * It does not own or manage any heap-allocated or static-lifetime resources.
    *
    * Function pointers provided during registration are cached separately and are
    * decoupled from this class. Each CxxMirror instance maintains its own metadata
    * that references the registered function pointers.
    *
    * As a result, the same function pointer may be associated with different string
    * keys across different CxxMirror instances without duplicating the underlying
    * function pointer storage.
    *
    * Within a single CxxMirror instance, attempting to register the same functor
    * multiple times is ignored, and a warning is emitted to the console.
    */
    class CxxMirror : public detail::CxxReflection
    {
    public:

        // avoids implicit move.
        explicit CxxMirror(CxxMirror&&) = default;

        // avoids implicit copy.
        explicit CxxMirror(const CxxMirror&) = default;

        // Constructs CxxMirror using a set of Function objects.
        explicit CxxMirror(const std::vector<Function>& pFunctions);

        // Returns a valid Record if the type is found by id; otherwise, std::nullopt.
        std::optional<Record> getRecord(const traits::uid_t pRecordId) const;

        // Returns a valid Record if the type is found by name in default namespace group; otherwise, std::nullopt.
        std::optional<Record> getRecord(const std::string& pRecordName) const;

        // Returns a valid Record if the type is found by name in the given namespace group; otherwise, std::nullopt.
        std::optional<Record> getRecord(const std::string& pNameSpaceName, const std::string& pRecordName) const;

        // Returns a valid Function if found by name in default namespace group; otherwise, std::nullopt.
        std::optional<Function> getFunction(const std::string& pFunctionName) const;

        // Returns a valid Function if found by name in the given namespace group; otherwise, std::nullopt.
        std::optional<Function> getFunction(const std::string& pNameSpaceName, const std::string& pFunctionName) const;
    };
}
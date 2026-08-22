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

#include <string>
#include <optional>
#include <unordered_map>
#include <inc/Record.h>

namespace rtl::detail {

/*  @class: CxxReflection
    * base class for main 'CxxMirror' interface.
    * accepts 'Function' objects for construction, frowared from 'CxxMirror' constructor
    * organizes the 'Function' objects by namespace, class/structs.
*/  class CxxReflection
    {
        using RecordRef = std::reference_wrapper<Record>;
        using RecordMap = std::unordered_map <std::string, RecordRef>;
        using MethodMap = std::unordered_map <std::string, Method>;
        using FunctionMap = std::unordered_map <std::string, Function>;

        std::unordered_map<traits::uid_t, Record> m_recordIdMap;
        //contains 'Record' (class/struct) objects, mapped with given namespace name.
        std::unordered_map<std::string, RecordRef> m_recordMap;
        //contains 'Function' (non-member-function) objects, mapped with given namespace name.
        std::unordered_map<std::string, Function> m_functionsMap;

        void buildRecordIdMap(const std::vector<Function>& pFunctions);
        bool insertMethodsToRecordIdMap(const Function& pFunction);

        void addFunction(const Function& pFunction);
        static void addMethod(MethodMap& pMethodMap, const Function& pFunction);
        static const bool validateMethodByRecordId(const Function& pFunction);

    protected:

        CxxReflection(const std::vector<Function>& pFunctions);

    public:

        CxxReflection() = delete;
        CxxReflection(CxxReflection&&) = default;
        CxxReflection(const CxxReflection&) = default;
        CxxReflection& operator=(CxxReflection&&) = delete;
        CxxReflection& operator=(const CxxReflection&) = delete;

        //returns the complete map of registered methods grouped by namespace, contained in 'Record' (class/struct) objects.
        constexpr const std::unordered_map<traits::uid_t, Record>& getRecordIdMap() const {
            return m_recordIdMap;
        }

        //returns the complete map of registered methods grouped by namespace, contained in 'Record' (class/struct) objects.
        constexpr const std::unordered_map<std::string, RecordRef>& getRecordsMap() const {
            return m_recordMap;
        }

        //returns the complete map of registered functions ('Function' objects) under a namespace.
        constexpr const std::unordered_map<std::string, Function>& getFunctionsMap() const {
            return m_functionsMap;
        }
    };
}
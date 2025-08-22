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

#include <string>
#include <optional>
#include <unordered_map>

#include "Record.h"

namespace rtl {

    namespace detail
    {
    /*  @class: CxxReflection
        * base class for main 'CxxMirror' interface.
        * accepts 'Function' objects for construction, frowared from 'CxxMirror' constructor
        * organizes the 'Function' objects by namespace, class/structs.
    */  class CxxReflection
        {
            using RecordRef = std::reference_wrapper<access::Record>; 
            using RecordMap = std::unordered_map <std::string, RecordRef>;
            using MethodMap = std::unordered_map <std::string, access::Method>;
            using FunctionMap = std::unordered_map <std::string, access::Function>;

            std::unordered_map<std::size_t, access::Record> m_recordIdMap;
            //contains 'Record' (class/struct) objects, mapped with given namespace name.
            std::unordered_map<std::string, RecordMap> m_recordNamespaceMap;
            //contains 'Function' (non-member-function) objects, mapped with given namespace name.
            std::unordered_map<std::string, FunctionMap> m_functionNamespaceMap;

            void buildRecordIdMap(const std::vector<access::Function>& pFunctions);
            void insertFunctionToNamespaceMap(const access::Function& pFunction);
            bool insertFunctionToRecordIdMap(const access::Function& pFunction);

            static void addMethod(MethodMap& pMethodMap, const access::Function& pFunction);
            static void addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction);
            static const bool validateFunctionByRecordId(const access::Function& pFunction);
            //static const bool validateFunctionByRecordName(const access::Record& pRecord, const access::Function& pFunction);

        protected:

            CxxReflection() = delete;
            CxxReflection(CxxReflection&) = delete;
            CxxReflection& operator=(CxxReflection&) = delete;
            CxxReflection(const std::vector<access::Function>& pFunctions);

        public:

            //returns the complete map of registered methods grouped by namespace, contained in 'Record' (class/struct) objects.
            constexpr const std::unordered_map<std::size_t, access::Record>& getRecordIdMap() const {
                return m_recordIdMap;
            }

            //returns the complete map of registered methods grouped by namespace, contained in 'Record' (class/struct) objects.
            constexpr const std::unordered_map<std::string, RecordMap>& getNamespaceRecordMap() const {
                return m_recordNamespaceMap;
            }

            //returns the complete map of registered functions ('Function' objects) under a namespace.
            constexpr const std::unordered_map<std::string, FunctionMap>& getNamespaceFunctionsMap() const {
                return m_functionNamespaceMap;
            }
        };
    }
}
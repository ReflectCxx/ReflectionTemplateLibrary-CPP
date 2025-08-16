/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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

            void insertFunctionToNamespaceMap(const access::Function& pFunction);
            bool insertFunctionToRecordIdMap(const access::Function& pFunction);

            static void addMethod(MethodMap& pMethodMap, const access::Function& pFunction);
            static void addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction);
            static const bool validateFunctionByRecordId(const access::Function& pFunction);
            static const bool validateFunctionByRecordName(const access::Record& pRecord, const access::Function& pFunction);

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
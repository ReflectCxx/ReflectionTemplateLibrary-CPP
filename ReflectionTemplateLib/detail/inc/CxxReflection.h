#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "Constants.h"

namespace rtl {

    namespace access 
    {
        //Forward decls.
        class Record;
        class Method;
        class Function;
    }

    namespace detail
    {
    /*  @class: CxxReflection
        * base class for main 'CxxMirror' interface.
        * accepts 'Function' objects for construction, frowared from 'CxxMirror' constructor
        * organizes the 'Function' objects by namespace, class/structs.
    */  class CxxReflection
        {
            using RecordMap = std::unordered_map <std::string, access::Record>;
            using MethodMap = std::unordered_map <std::string, access::Method>;
            using FunctionMap = std::unordered_map <std::string, access::Function>;

            //contains 'Record' (class/struct) objects, mapped with given namespace name.
            std::unordered_map<std::string, RecordMap> m_nsRecordsMap;

            //contains 'Function' (non-member-function) objects, mapped with given namespace name.
            std::unordered_map<std::string, FunctionMap> m_nsFunctionsMap;

            void organizeFunctorsMetaData(const access::Function& pFunction);

            void addRecord(RecordMap& pRecordMap, const access::Function& pFunction);
            void addMethod(MethodMap& pMethodMap, const access::Function& pFunction);
            void addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction);

        protected:

            CxxReflection() = delete;
            CxxReflection(CxxReflection&) = delete;
            CxxReflection& operator=(CxxReflection&) = delete;

            CxxReflection(const std::vector<access::Function>& pFunctions);

        public:

            //returns the complete map of registered methods grouped by namespace, contained in 'Record' (class/struct) objects.
            constexpr const std::unordered_map<std::string, RecordMap>& getNamespaceRecordMap() const {
                return m_nsRecordsMap;
            }

            //returns the complete map of registered functions ('Function' objects) under a namespace.
            constexpr const std::unordered_map<std::string, FunctionMap>& getNamespaceFunctionsMap() const {
                return m_nsFunctionsMap;
            }
        };
    }
}
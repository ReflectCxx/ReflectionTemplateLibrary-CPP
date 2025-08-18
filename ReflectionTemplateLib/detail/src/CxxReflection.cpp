/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#include <iostream>

#include "TypeId.h"
#include "Record.h"
#include "Method.h"
#include "CxxReflection.h"

namespace rtl {

    namespace detail
    {
    /*  @Constructor: CxxMirror
        @params: 'const std::vector<Function>&'
        * recieves vector of 'Function' objects, forwarded from 'CxxMirror' constructor.
        * initiates grouping of each 'Function' object under namespace, class/struct.
    */  CxxReflection::CxxReflection(const std::vector<access::Function>& pFunctions)
        {
            for (const auto& function : pFunctions) 
            {
                if (validateFunctionByRecordId(function) && insertFunctionToRecordIdMap(function)) 
                {
                    insertFunctionToNamespaceMap(function);
                }
            }
        }


    /*  @method: addFunction
        @params: FunctionMap, Function
        * adds the 'Function' object as non-member function mapped to the given namespace name.
    */  void CxxReflection::addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction)
        {
            const auto& fname = pFunction.getFunctionName();
            const auto& itr = pFunctionMap.find(fname);
            if (itr == pFunctionMap.end()) {
                pFunctionMap.emplace(fname, pFunction);
            }
            else {
                const auto& function = itr->second;
                //if the function is already present, add its 'FunctorId' as overload.
                function.addOverload(pFunction);
            }
        }


    /*  @method: addMethod
        @params: MethodMap, Function
        * adds the 'Function' object as 'Method' object in MethodMap, contained by 'Record' object.
        * if the function name already exists in the map, then 'FunctorId' from the param 'pFunction' is added to already existing 'Function'.
        * if a 'Function' object represents a Constructor, it might have the copy-constructor 'FunctorId' as well.
        * if copy-constructor 'FunctorId' is found, 'Function' object is created and added to the 'MethodMap' for the same.
    */  void CxxReflection::addMethod(MethodMap& pMethodMap, const access::Function& pFunction)
        {
            const auto& fname = pFunction.getFunctionName();
            const auto& itr = pMethodMap.find(fname);
            if (itr == pMethodMap.end()) {
                //construct 'Method' obejct and add.
                pMethodMap.emplace(fname, access::Method(pFunction));
            }
            else {
                const auto& function = itr->second;
                //if the method is already present, add as overload.
                function.addOverload(pFunction);
            }
        }


        bool CxxReflection::insertFunctionToRecordIdMap(const access::Function& pFunction)
        {
            const std::size_t recordId = pFunction.getRecordTypeId();
            if (recordId != TypeId<>::None) 
            {
                const auto& itr = m_recordIdMap.find(recordId);
                const std::string& recordName = pFunction.getRecordName();
                if (itr == m_recordIdMap.end()) {
                    const auto& record = m_recordIdMap.emplace(recordId, access::Record(recordName, recordId)).first->second;
                    addMethod(record.getFunctionsMap(), pFunction);
                }
                else {
                    const auto& record = itr->second;
                    if (validateFunctionByRecordName(record, pFunction)) {
                        addMethod(record.getFunctionsMap(), pFunction);
                    }
                    else return false;
                }
            }
            return true;
        }


    /*  @method: organizeFunctorsMetaData
        @params: Function
        * seggregates all the 'Function' objects and builds 'Record' & 'Method' objects.
    */  void CxxReflection::insertFunctionToNamespaceMap(const access::Function& pFunction)
        {
            const std::string& nameSpace = pFunction.getNamespace();
            const std::string& recordName = pFunction.getRecordName();
            const std::size_t recordId = pFunction.getRecordTypeId();
            //if the recordId(class/struct's type-id) is TypeId<>::None, 'Function' object is considered as non-member function.
            if (recordId == TypeId<>::None)
            {
                const auto& itr = m_functionNamespaceMap.find(nameSpace);
                if (itr == m_functionNamespaceMap.end()) {
                    const auto& funcMapItr = m_functionNamespaceMap.emplace(nameSpace, FunctionMap());
                    addFunction(funcMapItr.first->second, pFunction);
                }
                else {
                    addFunction(itr->second, pFunction);
                }
            }
            //if recordId is valid, 'Function' object is considered as member-function, a 'Method'.
            else 
            {
                const auto& itr = m_recordNamespaceMap.find(nameSpace);                
                if (itr == m_recordNamespaceMap.end()) 
                {
                    RecordMap& recordStrMap = m_recordNamespaceMap.emplace(nameSpace, RecordMap()).first->second;
                    recordStrMap.emplace(recordName, std::ref(m_recordIdMap.at(recordId)));
                }
                else 
                {
                    RecordMap& recordStrMap = itr->second;
                    const auto& itr0 = recordStrMap.find(recordName);
                    if (itr0 == recordStrMap.end()) {
                        recordStrMap.emplace(recordName, std::ref(m_recordIdMap.at(recordId)));
                    }
                }
            }
        }


    /*  During registration of a method using:
    *   Reflect().nameSpace("std").record<std::string>("string").methodConst("empty").build(&std::string::empty),
    *   the `givenRecordId` is generated by the `record<T>()` call (e.g., for `std::string`),
    *   and the `actualRecordId` is extracted from the type of the function pointer passed to `build(...)`.
    *
    *   - If the function is a non-member function, both `givenRecordId` and `actualRecordId` are zero (rtl::TypeId<>::None).
    *   - If it's a static member function, both IDs are equal, and no further validation is needed.
    *   - If it's a non-static member function, both IDs **must** match - this check helps catch registration errors
    *     where the member function belongs to a different class than the one being registered.
    *
    *   Example of incorrect usage (caught by this validation):
    *   Reflect().nameSpace("std").record<std::string_view>("string").methodConst("empty").build(&std::string::empty);
    *   Here, the record is being created for `std::string_view`, but the method pointer belongs to `std::string`.
    */  const bool CxxReflection::validateFunctionByRecordId(const access::Function& pFunction)
        {
            const std::size_t givenRecordId = pFunction.getRecordTypeId();
            const std::size_t actualRecordId = pFunction.getFunctorIds()[0].getRecordId(); //Index 0 is always guaranteed to reference a valid functor.
            if (givenRecordId != actualRecordId) {
                std::cout << "\n[WARNING] Member function pointer does not belong to the class being registered."
                          << "\n          Member function: " << pFunction.getFunctionName() << "(" << pFunction.getFunctorIds()[0].getSignatureStr() << ")"
                          << "\n          This function is ignored and not registered.\n\n";
                return false;
            }
            return true;
        }


    /*
    * This validation handles multiple registrations of the same C++ type under different names.
    *
    * For example, the first registration:
    * Reflect().nameSpace("std").record<std::string>("string").methodConst("empty").build(&std::string::empty);
    *
    * And a later, conflicting registration:
    * Reflect().nameSpace("std").record<std::string>("std_string").methodConst("empty").build(&std::string::empty);
    *
    * Both use the same type: record<std::string>, but with different names ("string" vs. "std_string").
    * RTL will retain the first registration and ignore the subsequent ones.
    * A warning is emitted to alert the user about the name conflict.
    */  const bool CxxReflection::validateFunctionByRecordName(const access::Record& pRecord, const access::Function& pFunction)
        {
            if (pRecord.m_recordName != pFunction.getRecordName())
            {
                std::cout << "\n[WARNING] Multiple registrations of the same type with different names detected."
                          << "\n          Type already registered as \"" << pRecord.m_recordName << "\""
                          << "\n          Attempted re-registration as \"" << pFunction.getRecordName() << "\""
                          << "\n          Member function: " << pFunction.getFunctionName() << "(" << pFunction.getFunctorIds()[0].getSignatureStr() << ")"
                          << "\n          This function is ignored and not registered.\n";
                return false;
            }
            return true;
        }
    }
}
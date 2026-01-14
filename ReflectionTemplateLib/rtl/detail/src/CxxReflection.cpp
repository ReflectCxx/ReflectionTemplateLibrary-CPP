/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <iostream>

#include <inc/Record.h>
#include <inc/Method.h>
#include <inc/type_meta.h>
#include <detail/inc/CxxReflection.h>

namespace rtl {

    namespace detail
    {
    /*  @Constructor: CxxReflection
        @params: 'const std::vector<Function>&'
        * recieves vector of 'Function' objects, forwarded from 'CxxMirror' constructor.
        * initiates grouping of each 'Function' object under namespace, class/struct.
    */  CxxReflection::CxxReflection(const std::vector<Function>& pFunctions)
        {
            // First, map all record (could be any type, not just class/struct) registered using interface-
            // 'rtl::type().record<TYPE>("...")' with its type-id (i.e, rtl::traits::uid<TYPE>).
            // every such registration will always have a default-constructor metadata.
            // Simultaneously, register any other user-defined constructor, if given.
            buildRecordIdMap(pFunctions);

            for (const auto& function : pFunctions) 
            {
                if (// Validate, if the member-function-pointer belongs to the 'TYPE' given using interface-
                    // rtl::type().member<TYPE>("...")', if not ignore this registration.
                     validateMethodByRecordId(function) &&  // Returns false if this 'function' is ignored.
                    // Once validated, try inserting 'function' as a member to its Record (i.e, to its class/struct metadata descriptor)
                    // returns 'false' if the 'function' represents a non-member function (C-Style function).
                    !insertMethodsToRecordIdMap(function) )
                {
                    // Finally, register the 'function' as a non-member function under the given or global namespace.
                    insertFunctionToNamespaceMap(function);
                }
            }
        }


    /*  @method: addFunction
        @params: FunctionMap, Function
        * adds the 'Function' object as non-member function mapped to the given namespace name.
    */  void CxxReflection::addFunction(FunctionMap& pFunctionMap, const Function& pFunction)
        {
            const auto& fname = pFunction.getFunctionName();
            const auto& itr = pFunctionMap.find(fname);
            if (itr == pFunctionMap.end()) {
                pFunctionMap.emplace(fname, pFunction);
            }
            else {
                const auto& function = itr->second;
                //if the function is already present, add its 'FunctorId' as overload.
                // TODO: Make sure every overload has identical return type/id.
                function.addOverload(pFunction);
            }
        }


    /*  @method: addMethod
        @params: MethodMap, Function
        * adds the 'Function' object as 'Method' object in MethodMap, contained by 'Record' object.
        * if the function name already exists in the map, then 'FunctorId' from the param 'pFunction' is added to already existing 'Function'.
        * if a 'Function' object represents a Constructor, it might have the copy-constructor 'FunctorId' as well.
        * if copy-constructor 'FunctorId' is found, 'Function' object is created and added to the 'MethodMap' for the same.
    */  void CxxReflection::addMethod(MethodMap& pMethodMap, const Function& pFunction)
        {
            const auto& fname = pFunction.getFunctionName();
            const auto& itr = pMethodMap.find(fname);
            if (itr == pMethodMap.end()) {
                //construct 'Method' obejct and add.
                pMethodMap.emplace(fname, Method(pFunction));
            }
            else {
                const auto& function = itr->second;
                //if the method is already present, add as overload.
                // TODO: Make sure every overload has identical return type/id.
                function.addOverload(pFunction);
            }
        }


    /*  @method: organizeFunctorsMetaData
        @params: Function
        * seggregates all the 'Function' objects and builds 'Record' & 'Method' objects.
    */  void CxxReflection::insertFunctionToNamespaceMap(const Function& pFunction)
        {
            const std::string& nameSpace = pFunction.getNamespace();
            const std::string& recordName = pFunction.getRecordName();
            const traits::uid_t recordId = pFunction.getRecordTypeId();
            //if the recordId(class/struct's type-id) is TypeId<>::None, 'Function' object is considered as non-member function.
            if (recordId == traits::uid<>::none)
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
        }


        void CxxReflection::addInNamespaceMap(Record& pRecord)
        {
            const auto& itr = m_recordNamespaceMap.find(pRecord.m_namespaceStr);
            if (itr == m_recordNamespaceMap.end())
            {
                RecordMap& recordStrMap = m_recordNamespaceMap.emplace(pRecord.m_namespaceStr, RecordMap()).first->second;
                recordStrMap.emplace(pRecord.m_recordName, std::ref(pRecord));
            }
            else
            {
                RecordMap& recordStrMap = itr->second;
                const auto& itr0 = recordStrMap.find(pRecord.m_recordName);
                if (itr0 == recordStrMap.end()) {
                    recordStrMap.emplace(pRecord.m_recordName, std::ref(pRecord));
                }
            }
        }


        void CxxReflection::buildRecordIdMap(const std::vector<Function>& pFunctions)
        {
            for (auto& function : pFunctions) {

                const auto& recordName = function.getRecordName();
                const traits::uid_t recordId = function.getRecordTypeId();
                const member memberKind = function.getMemberKind();
                if (memberKind == member::UserCtor || memberKind == member::DefaultCtor)
                {
                    bool isRegistrationIgnored = false;
                    auto& record = [&]()->const Record& {
                        const auto& itr = m_recordIdMap.find(recordId);
                        if (itr == m_recordIdMap.end()) {
                            auto& record = m_recordIdMap.emplace(recordId, Record(recordName, recordId, function.m_namespaceStr)).first->second;
                            addInNamespaceMap(record);
                            return record;
                        }
                        else {
                            auto& record = itr->second;
                            isRegistrationIgnored = (memberKind == member::DefaultCtor);
                            if (isRegistrationIgnored) {
                                std::cout << "\n[WARNING] Multiple registrations of the same type detected."
                                          << "\n          Type already registered as \"" << record.m_recordName << "\""
                                          << "\n          Attempted re-registration as \"" << recordName << "\""
                                          << "\n          This registration is ignored.\n";
                            }
                            return record;
                        }
                    }();

                    if (!isRegistrationIgnored) {
                        Function constructor = function;
                        constructor.m_recordStr = record.m_recordName;
                        constructor.m_namespaceStr = record.m_namespaceStr;
                        constructor.m_function = ctor_name(record.m_recordName);
                        addMethod(record.getFunctionsMap(), constructor);
                    }
                }
            }
        }


    /*  During registration of a method using:
    *   rtl::type().member<std::string>().methodConst("empty").build(&std::string::empty),
    *   the `givenRecordId` is generated by the `rtl::type().member<T>()` call (T = `std::string`),
    *   and the `actualRecordId` is extracted from the type of the function pointer passed to `build(...)`.
    *
    *   - If the function is a non-member function, both `givenRecordId` and `actualRecordId` are 'rtl::traits::uid<>::none'.
    *   - If it's a member-function, both IDs **must** match - this check helps catch registration errors
    *     where the member function belongs to a different class than the one being registered.
    *
    *   Example of incorrect usage (caught by this validation):
    *   rtl::type().member<std::string_view>().methodConst("empty").build(&std::string::empty);
    *   Here, the record-type is `std::string_view`, but the method pointer belongs to `std::string`.
    */  const bool CxxReflection::validateMethodByRecordId(const Function& pFunction)
        {
            const auto& functor = pFunction.getFunctors().back();
            const traits::uid_t givenRecordId = pFunction.getRecordTypeId();
            const traits::uid_t actualRecordId = functor.get_record_id();
            if (givenRecordId != actualRecordId) {
                std::cout << "\n[WARNING] Member function pointer does not belong to the class/struct being registered."
                          << "\n          Member function: " << functor.get_signature_str()
                          << "\n          This function is ignored and not registered.\n";
                return false;
            }
            return true;
        }


        bool CxxReflection::insertMethodsToRecordIdMap(const Function& pFunction)
        {
            const member memberKind = pFunction.getMemberKind();
            if (memberKind == member::Const || memberKind == member::NonConst || memberKind == member::Static)
            {
                const auto& itr = m_recordIdMap.find(pFunction.getRecordTypeId());
                if (itr != m_recordIdMap.end()) {

                    const auto& record = itr->second;
                    Function memberFunc = pFunction;

                    memberFunc.m_recordStr = record.m_recordName;
                    memberFunc.m_namespaceStr = record.m_namespaceStr;
                    addMethod(record.getFunctionsMap(), memberFunc);
                }
                else {
                    std::cout << "\n[WARNING] The class/struct for this member-function is not registered."
                              << "\n          While registering \"" << pFunction.m_function << "\""
                              << "\n          Make sure to register the 'Type' (struct/class) as well."
                              << "\n          This registration is ignored.\n";
                }
                return true;
            }
            return false;
        }
    }
}
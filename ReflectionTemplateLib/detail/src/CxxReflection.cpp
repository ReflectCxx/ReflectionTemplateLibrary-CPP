
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
            for (const auto& function : pFunctions) {
                organizeFunctorsMetaData(function);
            }
        }


    /*  @method: addRecord
        @params: RecordMap, Function
        * constructs the 'Record'(class/struct) object & adds 'Function' as 'Method' to it.
        * if the 'Record' already exists in the map, the 'Function' object is added as 'Method' to it.
    */  void CxxReflection::addRecord(RecordMap& pRecordMap, const access::Function& pFunction)
        {
            const auto& recordName = pFunction.getRecordName();
            const auto& itr = pRecordMap.find(recordName);
            if (itr == pRecordMap.end()) {
                const std::size_t recordId = pFunction.getRecordTypeId();
                const auto& record = pRecordMap.emplace(recordName, access::Record(recordName, recordId)).first->second;
                m_recordIdMap.emplace(recordId, record);
                addMethod(record.getFunctionsMap(), pFunction);
            }
            else {
                addMethod(itr->second.getFunctionsMap(), pFunction);
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


    /*  @method: organizeFunctorsMetaData
        @params: Function
        * seggregates all the 'Function' objects and builds 'Record' & 'Method' objects.
    */  void CxxReflection::organizeFunctorsMetaData(const access::Function& pFunction)
        {
            const auto& nameSpace = pFunction.getNamespace();

            //if the record-name is empty, 'Function' object is considered as non-member function.
            if (pFunction.getRecordName().empty()) {
                const auto& itr = m_functionMap.find(nameSpace);
                if (itr == m_functionMap.end()) {
                    const auto& funcMapItr = m_functionMap.emplace(nameSpace, FunctionMap());
                    addFunction(funcMapItr.first->second, pFunction);
                }
                else {
                    addFunction(itr->second, pFunction);
                }
            }
            //if the record-name is not-empty, 'Function' object is considered as member function, a 'Method'.
            else {
                const auto& itr = m_recordMap.find(nameSpace);
                if (itr == m_recordMap.end()) {
                    const auto& recordMapItr = m_recordMap.emplace(nameSpace, RecordMap());
                    addRecord(recordMapItr.first->second, pFunction);
                }
                else {
                    addRecord(itr->second, pFunction);
                }
            }
        }
    }
}
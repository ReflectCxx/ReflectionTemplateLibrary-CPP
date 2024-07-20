
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
                const auto& recordItr = pRecordMap.emplace(recordName, access::Record(recordName));
                addMethod(recordItr.first->second.getFunctionsMap(),pFunction);
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
        * adds the 'Function' object as 'Method' object the the method map contained by 'Record' object.
        * if the function name already exists in the map, then 'FunctorId' from the source 'Function' object is added to already existing 'Function' object.
        * if a 'Function' object represents a Constructor, it might have the destructor 'FunctorId' as well.
        * if destructor 'FunctorId' is found, destructor 'Function' object is created and added to the 'MethodMap'.
    */  void CxxReflection::addMethod(MethodMap& pMethodMap, const access::Function& pFunction)
        {
            const auto& fname = pFunction.getFunctionName();
            const auto& itr = pMethodMap.find(fname);
            if (itr == pMethodMap.end())
            {
                auto& functorIds = pFunction.getFunctorIds();
            /*  This condition will be true only in case that 'Function' object represents a constructor
                and has more that one 'FunctorId'. every other function registered will have only one 'FunctorId'.
            */  if (functorIds.size() > 1) 
                {
                    const auto& dctorName = CtorName::dctor(pFunction.getRecordName());
                    if (pMethodMap.find(dctorName) == pMethodMap.end()) {
                        //destructor 'FunctorId' will always be the second in the constructor's FunctorId's vector.
                        access::Method method = access::Method::getDestructorMethod(pFunction, functorIds[1]);
                        pMethodMap.insert(std::make_pair(method.getFunctionName(), method));
                    }
                    //remove the destructor 'FunctorId' from the constructor's 'FunctorId' vector.
                    functorIds.pop_back();
                }
                //construct 'Method' obejct from 'Function' object and add.
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

            if (pFunction.getRecordName().empty()) {
                const auto& itr = m_nsFunctionsMap.find(nameSpace);
                if (itr == m_nsFunctionsMap.end()) {
                    const auto& funcMapItr = m_nsFunctionsMap.emplace(nameSpace, FunctionMap());
                    addFunction(funcMapItr.first->second, pFunction);
                }
                else {
                    addFunction(itr->second, pFunction);
                }
            }
            else {
                const auto& itr = m_nsRecordsMap.find(nameSpace);
                if (itr == m_nsRecordsMap.end()) {
                    const auto& recordMapItr = m_nsRecordsMap.emplace(nameSpace, RecordMap());
                    addRecord(recordMapItr.first->second, pFunction);
                }
                else {
                    addRecord(itr->second, pFunction);
                }
            }
        }
    }
}
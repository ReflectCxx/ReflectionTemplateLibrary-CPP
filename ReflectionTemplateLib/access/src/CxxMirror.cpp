
#include "Record.h"
#include "Function.h"
#include "Method.h"
#include "CxxMirror.h"
#include "Constants.h"

namespace rtl {
	
    namespace access
    {
    /*  @Constructor: CxxMirror
        @params: 'const std::vector<Function>&'
        * accepts vector of 'Function' objects, which are hash-key to lookup a functor.
		* the only constructor to construct 'CxxMirror' object.
		* Syntax for constructing - CxxMirror({ Reflect().function("func_name").build(), ..., ... })
		* '.build()' function will return a 'Function' object, and passed to std::vector initializer list.
		* the vector is simply forwarded to the base class constructor.
    */  CxxMirror::CxxMirror(const std::vector<Function>& pFunctions)
            : detail::CxxReflection(pFunctions) {
        }


    /*  @method: getRecord
        @param: const std::string& (name of the class/struct)
        @return: std::optional<Record>
        * if the class/struct isn't found by the given name, std::nullopt is returned.
        * every class/struct's is grouped under a namespace.
		* if no namespace is specified while registration, NAMESPACE_GLOBAL is used.
    */  std::optional<Record> CxxMirror::getRecord(const std::string& pRecord) const
        {
            return getRecord(NAMESPACE_GLOBAL, pRecord);
        }


    /*  @method: getFunction
        @param: const std::string& (name of the non-member function)
        @return: std::optional<Function>
        * if the function isn't found by the given name, std::nullopt is returned.
        * every function is grouped under a namespace.
        * if no namespace is specified while registration, NAMESPACE_GLOBAL is used.
    */  std::optional<Function> CxxMirror::getFunction(const std::string& pFunction) const
        {
            return getFunction(NAMESPACE_GLOBAL, pFunction);
        }


    /*  @method: getRecord
        @param: std::string (namespace name), std::string (class/struct name)
        @return: std::optional<Record>
	    * retrieves the class/struct (as Record) registered under the given namespace.
        * if the class/struct isn't found by the given name, std::nullopt is returned.
    */  std::optional<Record> CxxMirror::getRecord(const std::string& pNameSpace, const std::string& pRecord) const
        {
            const auto& nsRecordMap = getNamespaceRecordMap();
            const auto& itr = nsRecordMap.find(pNameSpace);
            if (itr != nsRecordMap.end()) 
            {
                const auto& recordMap = itr->second;
                const auto& itr0 = recordMap.find(pRecord);
                if (itr0 != recordMap.end()) {
                    return std::make_optional(itr0->second);
                }
            }
            return std::nullopt;
        }


    /*  @method: getFunction
        @param: namespace name (std::string), non-mermber function name (std::string)
        @return: std::optional<Function>
        * retrieves the function (as 'Function' object) registered under the given namespace.
        * if the function isn't found by the given name, std::nullopt is returned.
    */  std::optional<Function> CxxMirror::getFunction(const std::string& pNameSpace, const std::string& pFunction) const
        {
            const auto& nsFunctionMap = getNamespaceFunctionsMap();
            const auto& itr = nsFunctionMap.find(pNameSpace);
            if (itr != nsFunctionMap.end())
            {
                const auto& functionMap = itr->second;
                const auto& itr0 = functionMap.find(pFunction);
                if (itr0 != functionMap.end()) {
                    return std::make_optional(itr0->second);
                }
            }
            return std::nullopt;
        }
    }
}
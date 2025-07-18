
#include "RObject.h"
#include "Record.h"
#include "Method.h"
#include "Function.hpp"
#include "Constants.h"

namespace rtl {

    namespace access
    {
        Record::Record(const std::string& pRecordName, const std::size_t pRecordId)
            : m_recordName(pRecordName)
            , m_recordId(pRecordId)
        {
        }


        Record& Record::operator=(const Record& pOther)
        {
            if (this == &pOther) {
                return *this;  // Return *this to handle self-assignment
            }

            m_recordName = pOther.m_recordName;
            m_methods = pOther.m_methods;
            return *this;
        }


    /*  @method: getFunctionsMap
        @param: none
        @return: std::unordered_map< std::string, access::Method >&
        * get set of all registered methods contained by the class/struct represented by this 'Record'.
        * provides 'mutable' map, which only detail::CxxReflection class can access.
    */  std::unordered_map< std::string, access::Method >& Record::getFunctionsMap() const
        {
            return m_methods;
        }


    /*  @method: getMethodMap
        @param: none
        @return: const std::unordered_map< std::string, access::Method >&
        * get set of all registered methods contained by the class/struct represented by this 'Record'.
        * provides 'const' map, publicly accessible.
    */  const std::unordered_map<std::string, access::Method>& Record::getMethodMap() const
        {
            return m_methods;
        }


    /*  @method: getMethod
        @param: const std::string& (name of the method)
        @return: std::optional<Method>
        * if the method isn't found by the given name, std::nullopt is returned.
    */  std::optional<Method> Record::getMethod(const std::string& pMethod) const
        {
            const auto& itr = m_methods.find(pMethod);
            if (itr != m_methods.end()) {
                return std::optional(itr->second);
            }
            return std::nullopt;
        }


    /*  @method: clone
        @param: Instance& (containing class/struct's object represented by this 'Record')
        @return: std::pair<RStatus, Instance> (RStatus: call success or not, Instance: containing copy constructed object)
        * calls copy constructor of class/struct represented by this 'Record'
        * creates copy of the object wrapped inside 'Instance' object.
        * returns 'RStatus' object indicating the success of the reflection call with other infos.
    */  std::pair<error, RObject> Record::clone(RObject& pOther) const
        {
            //validate the source object, should not be empty.
            if (pOther.isEmpty()) {
                //return empty instance with error status.
                return { error::EmptyRObject, RObject() };
            }

            //type of the object wrapped under source 'Instance' should match with type of this class/struct.
            if (m_recordId != pOther.getTypeId()) {
                //if source instance & ctor type didn't match, return empty instance with error status.
                return { error::MethodTargetMismatch, RObject() };
            }

            const std::string& constCopyStr = CtorName::copyCtor(m_recordName);
            std::optional<Function> constCopyCtor = getMethod(constCopyStr);			
            //if the object is const, only copy constructor with 'const&' can be called on it.
            if (constCopyCtor) {
                //object and type validated. call the const-copy-constructor.
                return (*constCopyCtor).bind<RObject&>().call(pOther);
            }

            //if no registered copy constructor found, return empty instance with error status.
            return { error::CopyConstructorPrivateOrDeleted, RObject() };
        }
    }
}
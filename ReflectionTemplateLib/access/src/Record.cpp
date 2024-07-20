
#include "Record.h"
#include "Method.h"
#include "RStatus.h"
#include "Instance.h"
#include "Constants.h"
#include "Function.hpp"

namespace rtl {

    namespace access
    {
        Record::Record(const std::string& pRecordName)
            : m_recordName(pRecordName)
        {
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
    */  const std::pair<RStatus, Instance> Record::clone(Instance& pOther) const
        {
            //validate the source object, should not be empty.
            if (pOther.isEmpty()) {
                //return empty instance with error status.
                return std::make_pair(RStatus(Error::EmptyInstance), Instance());
            }

            const std::string& dctor = CtorName::dctor(m_recordName);
            const std::string& copyStr = CtorName::copy(m_recordName);
            const std::string& constCopyStr = CtorName::constCopy(m_recordName);

            std::optional<Function> destructor = getMethod(dctor);
            std::optional<Function> constCopyCtor = getMethod(constCopyStr);
			
            //if the object is const, only copy constructor with 'const&' can be called on it.
            if (pOther.isConst())
            {
                if (constCopyCtor) 
                {
                /*  type of the object wrapped under source 'Instance' should match with type of the class/struct
                    associated by constructor ('Function')object.
                */  if (constCopyCtor->getRecordTypeId() != pOther.getTypeId()) {
                        //if source instance & ctor type didn't match, return empty instance with error status.
                        return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
                    }
                    //object and type validated. call the const-copy-constructor.
                    RStatus status = (*constCopyCtor)(pOther.get());
                    return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
                }
                else {
                    //if the object is 'const' and no constructor found accepting 'const&'
                    return std::make_pair(RStatus(Error::ConstCopyConstructorNotFound), Instance());
                }
            }
            else {
                //if the source 'Instance' is non-const, find copy-constructor taking non-const ref.
                std::optional<Function> copyCtor = getMethod(copyStr);
                if (copyCtor)
                {
                /*  type of the object wrapped under source 'Instance' should match with type of the class/struct
                    associated by constructor ('Function')object.
                */  if (copyCtor->getRecordTypeId() != pOther.getTypeId()) {
                        //if source instance & ctor type didn't match, return empty instance with error status.
                        return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
                    }
                    //object and type validated. call the non-const-copy-constructor.
                    RStatus status = (*copyCtor)(pOther.get());
                    return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
                }
                //if copy-constructor taking non-const ref not found, and with const-ref found, use that copy constructor.
                else if (constCopyCtor)
                {
                /*  type of the object wrapped under source 'Instance' should match with type of the class/struct
                    associated by constructor ('Function')object.
                */  if (constCopyCtor->getRecordTypeId() != pOther.getTypeId()) {
                        //if source instance & ctor type didn't match, return empty instance with error status.
                        return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
                    }
                    //object and type validated. call the const-copy-constructor.
                    RStatus status = (*constCopyCtor)(pOther.get());
                    return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
                }
            }
            //if no registered copy constructor found, return empty instance with error status.
            return std::make_pair(RStatus(Error::CopyConstructorNotFound), Instance());
        }
    }
}

#include "Function.h"

namespace rtl {

    namespace access
    {
    /*  @constructor: Function()
        @params: pNamespace - given namespace while registering the type.
        *        pRecord - given class/struct name, empty if this 'Function' represents a non-member functor
        *        pFunction - given name of the function as string.
        *        pFunctorId - 'FunctorId', generated for every functor being registered.
        *        pRecordTypeId - type id of class/struct if the functor is member-function, '0' for non-member-functions.
        *        pQualifier - whether the member-function is const or non-const. TypeQ::None for non-member-functions.
        * 'Function' object is created for every functor (member/non-member) being registered.
    */  Function::Function(const std::string& pNamespace, const std::string& pRecord,
                           const std::string& pFunction, const detail::FunctorId& pFunctorId,
                           const std::size_t pRecordTypeId, const TypeQ pQualifier)
            : m_qualifier(pQualifier)
            , m_recordTypeId(pRecordTypeId)
            , m_record(pRecord)
            , m_function(pFunction)
            , m_namespace(pNamespace)
            , m_functorIds({ pFunctorId }) {
        }


    /*  @constructor: Function()
        @params: pOther - 'Function' object associated with a constructor.
        *        pFunctorId - 'FunctorId', object associated with a destructor.
        *        pFunctorName - name of the destructor.
        * this constructor is only called to create 'Function' object associated with destructor.
        * the destructor 'FunctorId' is added to the 'Function' object associated with a constructor while registration.
        * the very first registration of constructor adds the destructor lambda in the functor-container and sends its
          'FunctorId' with the 'Function' object associated with a constructor.
    */  Function::Function(const Function& pOther, const detail::FunctorId& pFunctorId,
                           const std::string& pFunctorName)
            : m_qualifier(pOther.m_qualifier)
            , m_recordTypeId(pOther.m_recordTypeId)
            , m_record(pOther.m_record)
            , m_function(pFunctorName)
            , m_namespace(pOther.m_namespace)
            , m_functorIds({ pFunctorId }) {
        }


    /*  @method: hasSignatureId()
        @param: const std::size_t& (signatureId to be found)
        @return: the index of the functor in the functor-table.
        * a 'Function' object may be associated with multiple functors in case of overloads.
        * every overload will have unique 'FunctorId', contained by one 'Function' object.
        * given signatureId is compared against the signatureId of all overloads registered.
    */	const std::size_t Function::hasSignatureId(const std::size_t& pSignatureId) const
        {
            //simple linear-search, efficient for small set of elements.
            for (const auto& functorId : m_functorIds) {
                if (functorId.getSignatureId() == pSignatureId) {
                    return functorId.getIndex();
                }
            }
            return -1;
        }


    /*  @method: addOverload()
        @param: 'Function' object
        * every 'Function' object produced while registration will have a single 'FunctorId' object, except constructors.
        * for overloads, registered with the same name, the 'FunctorId' from the 'pOtherFunc' object will be added to this.
        * if the same functor is registered again with the same name, it will be ignored.
    */	void Function::addOverload(const Function& pOtherFunc) const
		{
            const std::size_t& otherFuncSignId = pOtherFunc.m_functorIds[0].getSignatureId();
            //simple linear-search, efficient for small set of elements.
            for (const auto& functorId : m_functorIds) {
                if (functorId.getSignatureId() == otherFuncSignId) {
                    return; //ignore and return since its already registered.
                }
            }

            //add the 'functorId' of the overloaded functor.
            m_functorIds.push_back(pOtherFunc.m_functorIds[0]);
        }
    }
}
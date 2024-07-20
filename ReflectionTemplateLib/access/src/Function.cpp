
#include "Function.h"

namespace rtl {

    namespace access
    {
        Function::Function(const std::string& pNamespace, const std::string& pRecord,
                           const std::string& pFunction, const detail::FunctorId& pFunctorId,
                           const std::size_t pRecordTypeId, const TypeQ pQualifier)
            : m_qualifier(pQualifier)
            , m_recordTypeId(pRecordTypeId)
            , m_functorIds({ pFunctorId })
            , m_record(pRecord)
            , m_function(pFunction)
            , m_namespace(pNamespace) {
        }


        Function::Function(const Function& pOther, const detail::FunctorId& pFunctorId,
                           const std::string& pFunctorName)
            : m_qualifier(pOther.m_qualifier)
            , m_recordTypeId(pOther.m_recordTypeId)
            , m_functorIds({ pFunctorId })
            , m_record(pOther.m_record)
            , m_function(pFunctorName)
            , m_namespace(pOther.m_namespace) {
        }


    /*  @method: hasSignatureId()
        @param: const std::size_t& (signatureId to be found)
        @return: the index of the functor in the functor-table.
        * a 'Function' object may be associated with multiple functors in case of overloads.
        * every overload will have unique 'FunctorId', contained by one 'Function' object.
        * given signatureId is compared against the signatureId of all overloads registered.
    */	const std::size_t Function::hasSignatureId(const std::size_t& pSignatureId) const
        {
            //simple linear-search, most efficient for small set of elements.
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
        * for overloads registered with the same name, the 'FunctorId' from the other 'Function' object will be accumlated in one.
        * if the same functor is registered again with the same name, it will be ignored.
    */	void Function::addOverload(const Function& pOtherFunc) const
		{
            const std::size_t& otherFuncSignId = pOtherFunc.m_functorIds[0].getSignatureId();
            //simple linear-search, most efficient for small set of elements.
            for (const auto& functorId : m_functorIds) {
                if (functorId.getSignatureId() == otherFuncSignId) {
                    return; //ignore and return if its already registered.
                }
            }

            //add the 'functorId' of the overloaded functor.
            m_functorIds.push_back(pOtherFunc.m_functorIds[0]);
        }
    }
}
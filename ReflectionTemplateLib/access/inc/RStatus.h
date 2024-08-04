#pragma once

#include <any>
#include "Constants.h"
#include "TypeId.h"

namespace rtl
{
    namespace access
    {
    /*  @class: RStatus
        * Every reflection call made, returns a RStatus object.
        * it contains the error status of the call, defined by enum rtl::Error (in Constants.h)
        * indicates all possible failure-errors that could happen on calling reflected funtion/method/constructor.
        * it also contains the return value/object from the reflected function/method call wrapped under std::any.
    */  class RStatus
        {
            //indicates the reflection call status error
            const Error m_callStatus;

            //indicates whether the returned value from reflected call is const/non-const.
            const TypeQ m_typeQualifier;

            //contains the return value of the from reflected call. Type erased.
            const std::any m_returnObj;

            //type-id of the return value.
            const std::size_t m_typeId;

        public:

            //used when the reflected call doesn't have any return value, or in case of call failure.
            RStatus(const Error pCallStatus);

            //used when the reflected call returns a value, called only in case of no call failure.
            RStatus(const std::any& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier);

            GETTER(std::any, Return, m_returnObj)
            GETTER(std::size_t, TypeId, m_typeId)
            GETTER(TypeQ, Qualifier, m_typeQualifier)

            //RStatus object converted to bool based on call succes or not.
            operator bool() const {
                //Error::None, reflected call successful.
                return (m_callStatus == Error::None);
            }

            //RStatus object can be directly checked agains any error-code.
            const bool operator==(const Error pError) const {
                return (m_callStatus == pError);
            }

            //check if the returned object is of certain type. expected type must be passed as template param.
            //if the expected type is 'const', <const _type> must be used as templeate parameter.
            template<class _type>
            constexpr const bool isOfType() const {
                return (detail::TypeId<_type>::get() == m_typeId);
            }
        };
    }
}
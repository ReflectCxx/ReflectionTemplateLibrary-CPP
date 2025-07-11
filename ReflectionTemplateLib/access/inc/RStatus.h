#pragma once

#include <any>
#include "Constants.h"
#include "TypeId.h"

namespace rtl
{
    namespace access
    {
        //forward decls
        class Record;
        class Instance;
        template<class ..._signature>
        class FunctionCaller;
        template<class ..._signature>
        class MethodInvoker;

    /*  @class: RStatus
        * Every reflection call made, returns a RStatus object.
        * it contains the error status of the call, defined by enum rtl::error (in Constants.h)
        * indicates all possible failure-errors that could happen on calling reflected funtion/method/constructor.
        * it also contains the return value/object from the reflected function/method call wrapped under std::any.
    */  class RStatus
        {
            //indicates the reflection call status error
            error m_callStatus;

            //indicates whether the returned value from reflected call is const/non-const.
            TypeQ m_typeQualifier;

            //contains the return value of the from reflected call. Type erased.
            std::any m_returnObj;

            //type-id of the return value.
            std::size_t m_typeId;
            
            explicit RStatus();
            
            explicit RStatus(const error pCallStatus);

        public:

            //used when the reflected call doesn't have any return value, or in case of call failure.
            void init(const error pCallStatus);

            //used when the reflected call returns a value, called only in case of no call failure.
            void init(std::any&& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier);

            GETTER(std::any, Return, m_returnObj)
            GETTER(std::size_t, TypeId, m_typeId)
            GETTER(TypeQ, Qualifier, m_typeQualifier)

            RStatus(RStatus&&) = default;
            
            RStatus(const RStatus&) = default;
            
            RStatus& operator=(RStatus&&) = default;

            RStatus& operator=(const RStatus&) = default;

            operator error() const {
                return m_callStatus;
            }

            //RStatus object converted to bool based on call succes or not.
            operator bool() const {
                //error::None, reflected call successful.
                return (m_callStatus == error::None);
            }

            //RStatus object can be directly checked against any error-code.
            const bool operator==(const error pError) const {
                return (m_callStatus == pError);
            }

            //check if the returned object is of certain type. expected type must be passed as template param.
            //if the expected type is 'const', <const _type> must be used as templeate parameter.
            template<class _type>
            constexpr const bool isOfType() const {
                return (detail::TypeId<_type>::get() == m_typeId);
            }

            //friends :)
            friend Record;
            friend Instance;
            template<class ..._signature>
            friend class FunctionCaller;
            template<class ..._signature>
            friend class MethodInvoker;
        };
    }
}
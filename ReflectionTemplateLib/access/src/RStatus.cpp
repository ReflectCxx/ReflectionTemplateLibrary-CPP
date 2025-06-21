
#include <cassert>

#include "RStatus.h"

namespace rtl {

    namespace access {

        RStatus::RStatus()
            : m_callStatus(error::None)
            , m_typeQualifier(TypeQ::None)
            , m_typeId(detail::TypeId<>::None) {
        }


        RStatus::RStatus(const error pCallStatus)
            : m_callStatus(pCallStatus)
            , m_typeQualifier(TypeQ::None)
            , m_typeId(detail::TypeId<>::None) {
        }


        void RStatus::init(const error pCallStatus)
        {
            assert(m_callStatus == error::None && "must not be already initialized. Abort!");

            //no type is represented by value '0'.
            m_typeId = detail::TypeId<>::None;
            m_typeQualifier = TypeQ::None;
            m_callStatus = pCallStatus;
        }

		
        void RStatus::init(std::any&& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier)
        {
            const bool alreadyInitialized = (m_returnObj.has_value() || m_typeId != detail::TypeId<>::None || m_typeQualifier != TypeQ::None);
            assert(!alreadyInitialized && "must not be already initialized. Abort!");

            m_callStatus = error::None;
            m_typeQualifier = pQualifier;
            m_returnObj = std::move(pRetObj);
            m_typeId = pTypeId;
        }
    }
}
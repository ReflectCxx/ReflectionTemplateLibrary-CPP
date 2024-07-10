
#include "RStatus.h"

namespace rtl {

	namespace access {
				
		RStatus::RStatus(const bool pCallStatus)
			: m_callStatus(pCallStatus)
			, m_typeId(detail::TypeId<>::None)
			, m_typeIdConst(detail::TypeId<>::None)
			, m_typeQualifier(TypeQ::None) {
		}

		
		RStatus::RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId,
				   const std::size_t pConstTypeId, const TypeQ pQualifier)
			: m_callStatus(pCallStatus)
			, m_returnObj(pRetObj)
			, m_typeId(pTypeId)
			, m_typeIdConst(pConstTypeId)
			, m_typeQualifier(pQualifier) {
		}
	}
}
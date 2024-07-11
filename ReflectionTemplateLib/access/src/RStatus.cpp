
#include "RStatus.h"

namespace rtl {

	namespace access {
				
		RStatus::RStatus(const Error pCallStatus)
			: m_callStatus(pCallStatus)
			, m_typeQualifier(TypeQ::None)
			, m_typeId(detail::TypeId<>::None)
			, m_typeIdConst(detail::TypeId<>::None) {
		}

		
		RStatus::RStatus(const std::any& pRetObj, const std::size_t pTypeId,
				   const std::size_t pConstTypeId, const TypeQ pQualifier)
			: m_callStatus(Error::None)
			, m_typeQualifier(pQualifier)
			, m_returnObj(pRetObj)
			, m_typeId(pTypeId)
			, m_typeIdConst(pConstTypeId) {
		}
	}
}

#include "RStatus.h"

namespace rtl {

	namespace access {

		RStatus::RStatus(const bool pCallStatus) 
			: m_callStatus(pCallStatus) {
		}

		RStatus::RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier,
				 const std::function< void(const std::any&) >& pDctor, const std::function< void(std::any&, std::size_t&) >& pToConst)
			: m_callStatus(pCallStatus)
			, m_returnObject(pRetObj, pTypeId, pQualifier, pDctor, pToConst) {
		}

		const bool RStatus::didCallSucceed() const
		{
			return m_callStatus;
		}

		UniqueAny RStatus::releaseReturn() const
		{
			return std::move(m_returnObject);
		}
	}

}
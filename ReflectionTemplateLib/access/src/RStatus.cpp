
#include "RStatus.h"

namespace rtl {

	namespace access {

		RStatus::RStatus(const bool pCallStatus) 
			: m_callStatus(pCallStatus) {
		}

		RStatus::RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId,
						 const std::function<void(const std::any&)>& pDctor)
			: m_callStatus(pCallStatus)
			, m_returnObject(pRetObj, pTypeId, pDctor) {
		};

		const bool RStatus::didCallSucceed()
		{
			return m_callStatus;
		}

		UniqueAny RStatus::releaseReturn()
		{
			return std::move(m_returnObject);
		}

		const UniqueAny RStatus::releaseReturn() const
		{
			return std::move(m_returnObject);
		}
	}

}
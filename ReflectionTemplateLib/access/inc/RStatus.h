#pragma once

#include "UniqueAny.h"

namespace rtl 
{
	namespace access 
	{
		class RStatus
		{
			const bool m_callStatus;
			mutable UniqueAny m_returnObject;

		public:

			RStatus() = delete;

			RStatus(const bool pCallStatus);

			RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier,
				const std::function< void(const std::any&) >& pDctor = std::function< void(const std::any&) >());

			UniqueAny releaseReturn() const;

			const bool didCallSucceed() const;
		};
	}
}
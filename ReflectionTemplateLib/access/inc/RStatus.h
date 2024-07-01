#pragma once

#include "UniqueAny.h"

namespace rtl 
{
	namespace detail
	{
		template<class ..._signature>
		class FunctorContainer;
	}

	namespace access 
	{
		class Record;
		class Function;

		class RStatus
		{
			const bool m_callStatus;
			UniqueAny m_returnObject;

			RStatus(const bool pCallStatus);
			RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId,
					const std::function<void(const std::any&)>& pDctor = std::function<void(const std::any&)>());

		public:

			RStatus() = delete;

			UniqueAny releaseReturn();
			const bool didCallSucceed();

			template<class ..._signature>
			friend class detail::FunctorContainer;
			friend class Record;
			friend class Function;
		};
	}
}
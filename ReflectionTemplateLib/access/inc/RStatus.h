#pragma once

#include "UniqueAny.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		class SetupMethod;

		template<class _derivedType>
		class SetupFunction;

		template<class _derivedType>
		class SetupConstructor;

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
			mutable UniqueAny m_returnObject;

			RStatus(const bool pCallStatus);
			RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId,
					const std::function<void(const std::any&)>& pDctor = std::function<void(const std::any&)>());

		public:

			RStatus() = delete;

			const bool didCallSucceed();

			UniqueAny releaseReturn();
			const UniqueAny releaseReturn() const;

			friend class Record;
			friend class Function;

			template<class _derivedType>
			friend class detail::SetupMethod;

			template<class _derivedType>
			friend class detail::SetupFunction;

			template<class _derivedType>
			friend class detail::SetupConstructor;

			template<class ..._signature>
			friend class detail::FunctorContainer;
		};
	}
}
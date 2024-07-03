#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupConstructor
		{
			template<class _recordType>
			static const std::size_t getHashCode(const std::size_t pContainerId);

		protected:

			template<class _recordType, class ..._signature>
			static const access::FunctorId pushBack();
		};
	}
}
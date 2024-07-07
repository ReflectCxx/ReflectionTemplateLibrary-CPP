#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupConstructor
		{
			template<class _recordType>
			static const std::function< void(std::any&, std::size_t&) >getConstConverter();

			template<class _recordType>
			static const std::function< void(const std::any&, const TypeQ&) > getDestructor();
			
			template<class _recordType>
			static const std::size_t getHashCode(const std::size_t pContainerId, const std::size_t pIndex,
							     const std::size_t pArgsCount);

		protected:

			template<class _recordType, class ..._signature>
			static const detail::FunctorId pushBackCtor();
		};
	}
}
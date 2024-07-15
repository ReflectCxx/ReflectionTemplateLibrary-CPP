#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupConstructor
		{	
		protected:

			template<class _recordType>
			static const detail::FunctorId addDestructor();

			template<class _recordType, class ..._signature>
			static const detail::FunctorId addConstructor();

			template<class _recordType>
			static const detail::FunctorId addCopyConstructor();

			template<class _recordType>
			static const detail::FunctorId addConstCopyConstructor();
		};
	}
}
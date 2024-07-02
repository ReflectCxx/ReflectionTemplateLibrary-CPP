#pragma once

#include "Constants.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupConstructor
		{
		protected:

			template<class _recordType, class ..._signature>
			static int addConstructor();
		};
	}
}
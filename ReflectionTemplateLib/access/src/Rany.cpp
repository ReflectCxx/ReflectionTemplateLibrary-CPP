#pragma once

#include <any>
#include "Rany.h"

namespace rtl {

	namespace access 
	{
		Rany::Rany()
			: m_typeId(0) {
		}

		Rany::Rany(const std::any pAnyObj, const std::size_t pTypeId)
			: m_anyObject(pAnyObj)
			, m_typeId(pTypeId) {
		}
	}
}
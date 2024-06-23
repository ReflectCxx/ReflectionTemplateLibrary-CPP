#pragma once

#include <string>
#include <optional>

#include "Constants.h"

namespace rtl {

	namespace access 
	{
		class RObject
		{
			const std::string m_type;
			const std::size_t m_typeId;

		protected:

			RObject(const std::size_t& pTypeId, const std::string& pType);

		public:

			RObject() = delete;
			virtual ~RObject() = 0;

			GETTER(std::string, Type, m_type)
			GETTER(std::size_t, TypeId, m_typeId)

			template<class _type>
			std::optional<_type> get();
		};
	}
}

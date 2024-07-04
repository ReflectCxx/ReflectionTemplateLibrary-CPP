#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Function.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace access
	{
		class Method;
		class RStatus;
		class UniqueAny;

		class Record
		{
			const std::string m_recordName;

			mutable std::unordered_map< std::string, access::Method > m_methods;

			Record(const std::string& pRecordName);

			std::unordered_map< std::string, access::Method >& getFunctionsMap() const;

		public:

			Record() = delete;

			std::optional<Method> getMethod(const std::string& pMethod) const;

			//creates dynamic instance, calling copy ctor, using new.
			RStatus clone(UniqueAny& pOther) const;

			//creates dynamic instance, using new.
			template<class ..._ctorArgs>
			RStatus instance(_ctorArgs ...params) const;

			friend class detail::CxxReflection;
		};
	}
}
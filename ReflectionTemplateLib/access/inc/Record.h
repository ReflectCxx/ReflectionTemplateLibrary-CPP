#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Method.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace access
	{
		class Method;
		class RStatus;
		class Instance;

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
			std::optional<Instance> clone(Instance& pOther) const;

			//creates dynamic instance, using new.
			template<class ..._ctorArgs>
			const std::pair<RStatus, Instance> instance(_ctorArgs ...params) const;

			friend class detail::CxxReflection;
		};
	}
}
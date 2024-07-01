#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Function.h"

namespace rtl {

	namespace detail 
	{
		class ReflectTypeMeta;
		using FunctionMap = std::unordered_map <std::string, access::Function>;
	}

	namespace access 
	{
		class Method;
		class RStatus;

		class Record
		{
			const std::string m_recordName;
			mutable std::shared_ptr<detail::FunctionMap> m_functions;

			Record(const std::string& pRecordName);

			detail::FunctionMap& getFunctionsMap() const;

		public:

			Record() = delete;

			std::optional<Method> getMethod(const std::string& pMethod) const;

			//creates dynamic instance, using new.
			template<class ..._ctorArgs>
			RStatus instance(_ctorArgs ...params) const;

			friend class detail::ReflectTypeMeta;
		};
	}
}
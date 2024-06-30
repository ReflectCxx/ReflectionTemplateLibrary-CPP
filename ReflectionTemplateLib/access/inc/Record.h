#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Function.h"

namespace rtl {

	namespace detail {
		class ReflectTypeMeta;
	}

	namespace access 
	{
		class Method;
		class SmartAny;

		class Record
		{
			friend class detail::ReflectTypeMeta;

			const std::string m_recordName;
			mutable std::unordered_map <std::string, Function> m_functions;

			Record(const std::string& pRecordName);

			std::unordered_map <std::string, Function>& getFunctionsMap() const;

		public:

			Record() = delete;

			std::optional<Method> getMethod(const std::string& pMethod) const;

			template<class ..._ctorArgs>
			SmartAny instance(_ctorArgs ...params) const;

			//Instance on heap, constructed via new.
			template<class ..._ctorArgs>
			SmartAny newInstance(_ctorArgs ...params) const;
		};
	}
}
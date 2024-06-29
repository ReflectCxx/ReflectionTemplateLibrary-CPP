#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "ReflectTypeMeta.h"

namespace rtl {

	namespace access 
	{
		class Rany;
		class Method;
		class Function;
		class CxxMirror;

		class Record
		{
			friend CxxMirror;

			const std::string m_recordName;
			const detail::FunctionMap& m_functions;

			Record(const std::string& pRecordName, const detail::FunctionMap& pFunctions);

		public:

			Record() = delete;

			std::optional<Method> getMethod(const std::string& pMethod) const;

			template<class ..._ctorArgs>
			Rany newInstance(_ctorArgs ...params) const;
		};
	}
}
#pragma once

#include <string>
#include <vector>

#include "FunctorId.h"
#include "Constants.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
		class ReflectionBuilder;
	}

	namespace access
	{
		class RStatus;

		class Function
		{
			const TypeQ m_qualifier;
			const std::string m_record;
			const std::string m_function;
			const std::string m_namespace;

			mutable std::string m_signatures;
			mutable std::vector<detail::FunctorId> m_functorIndex;

			Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName,
				 const std::string& pSignature, const detail::FunctorId& pFunctorId, const TypeQ pQualifier = TypeQ::None);

		protected:

			void sortFunctorsHash() const;
			void addOverload(const Function& pOtherFunc) const;

			const bool hasSignatureId(const std::size_t& pSignId, std::size_t& pIndex, std::size_t& pHashCode) const;

		public:

			Function() = delete;

			GETTER(TypeQ, Qualifier, m_qualifier)
			GETTER(std::string, RecordName, m_record)
			GETTER(std::string, Namespace, m_namespace)
			GETTER(std::string, FunctionName, m_function)
			GETTER(std::string, Signatures, m_signatures)

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;

			friend detail::CxxReflection;
			friend detail::ReflectionBuilder;
		};
	}
}
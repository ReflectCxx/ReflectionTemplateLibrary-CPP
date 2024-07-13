#pragma once

#include <string>
#include <vector>
#include <functional>

#include "RStatus.h"
#include "FunctorId.h"
#include "Constants.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
		class ReflectionBuilder;
	}

	namespace access
	{
		class Function
		{
			const TypeQ m_qualifier;
			const std::size_t m_recordTypeId;

			const std::string m_record;
			const std::string m_function;
			const std::string m_namespace;

			mutable std::string m_signatures;
			mutable std::vector<detail::FunctorId> m_functorIds;

			Function();
			Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName,
				 const std::string& pSignature, const detail::FunctorId& pFunctorId,
				 std::size_t pRecordTypeId, const TypeQ pQualifier);

			void addOverload(const Function& pOtherFunc) const;

			GETTER_REF(std::vector<detail::FunctorId>, FunctorIds, m_functorIds)

		protected:

			Function(const Function& pOther, const detail::FunctorId& pFunctorId,
				 const std::string& pFunctorName, const std::string& pSignatureStr);

			const bool hasSignatureId(const std::size_t& pSignatureId) const;
			const bool hasSignatureId(const std::size_t& pSignatureId, std::size_t& pIndex, std::size_t& pHashCode) const;

		public:

			GETTER(TypeQ, Qualifier, m_qualifier)
			GETTER(std::string, RecordName, m_record)
			GETTER(std::string, Namespace, m_namespace)
			GETTER(std::string, FunctionName, m_function)
			GETTER(std::string, Signatures, m_signatures)
			GETTER(std::size_t, RecordTypeId, m_recordTypeId)

			const FunctorType& getFunctorType() const {
				return m_functorIds[0].getFunctorType();
			}

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;

			template<class ..._args>
			RStatus call(_args...params) const noexcept;

			friend detail::CxxReflection;
			friend detail::ReflectionBuilder;
		};
	}
}
#pragma once

#include <string>
#include <vector>

#include "FunctorId.h"
#include "Constants.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace builder
	{
		template<class ..._signature>
		class FunctionBuilder;
	}

	namespace access
	{
		class FunctorId;
		class Record;
		class RStatus;
		class UniqueAny;
		class MethodInvoker;

		class Function
		{
			const std::string m_record;
			const std::string m_function;
			const std::string m_namespace;

			mutable std::string m_signatures;
			mutable std::vector<FunctorId> m_functorIndex;

			void sortFunctorsHash() const;

			void addOverload(const Function& pOtherFunc) const;

			const bool hasSignatureId(const std::size_t& pSignId, std::size_t& pIndex, std::size_t& pHashCode) const;

			Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName,
				 const std::string& pSignature, const FunctorId& pFunctorId);

			template<class ..._args>
			RStatus invokeConstructor(_args...params) const;

			template<class ..._args>
			RStatus invokeMethod(const UniqueAny& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConstMethod(const UniqueAny& pTarget, _args...params) const;

		public:

			Function() = delete;

			GETTER(std::string, RecordName, m_record)
			GETTER(std::string, FunctionName, m_function)
			GETTER(std::string, Signatures, m_signatures)
			GETTER(std::string, Namespace, m_namespace)

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;

			friend class Record;
			friend class MethodInvoker;
			friend class detail::CxxReflection;

			template<class ..._signature>
			friend class builder::FunctionBuilder;
		};
	}
}
#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

namespace rtl {

	namespace access {
		class RStatus;
		class Function;
	}

	namespace builder {
		template<class ..._args>
		class FunctionBuilder;
	}

	namespace detail
	{
		template<class ..._signature>
		class FunctorContainer
		{
			friend access::Function;

			template<class ..._args>
			friend class builder::FunctionBuilder;

		public:

			static const std::size_t& getContainerId();

		private: 
			
			static const std::size_t m_containerId;

			using FunctorType = std::function < access::RStatus(_signature...) >;
			using CtorFunctorType = std::function < access::RStatus(_signature...) >;
			using MethodPtrType = std::function < access::RStatus(const access::UniqueAny&, _signature...) >;

			static std::vector<FunctorType> m_functors;
			static std::vector<MethodPtrType> m_methodPtrs;
			static std::vector<CtorFunctorType> m_ctorPtrs;

			template<class _recordType>
			static int addConstructor();

			template<class _returnType>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _returnType>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType>
			static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType>
			static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

			template<class ..._params>
			static access::RStatus reflectFunctionCall(std::size_t pFunctorId, _params..._args);

			template<class ..._params>
			static access::RStatus reflectConstructorCall(std::size_t pFunctorId, _params..._args);

			template<class ..._params>
			static access::RStatus reflectMethodCall(const access::UniqueAny& pTarget, std::size_t pFunctorId, _params..._args);
		};
	}
}

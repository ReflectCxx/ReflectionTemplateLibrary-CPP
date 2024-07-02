#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.hpp"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl {

	namespace builder {
		template<class ..._args>
		class FunctionBuilder;
	}

	namespace detail
	{
		template<class ..._signature>
		class FunctorContainer : SetupMethod<FunctorContainer<_signature...>>, 
								 SetupFunction<FunctorContainer<_signature...>>,
								 SetupConstructor<FunctorContainer<_signature...>>,
								 CallReflector<FunctorContainer<_signature...>>
		{
			GETTER_STATIC_CONST_REF(std::size_t, ContainerId, m_containerId)

			using FunctorType = std::function < access::RStatus(_signature...) >;
			using CtorFunctorType = std::function < access::RStatus(_signature...) >;
			using MethodPtrType = std::function < access::RStatus(const access::UniqueAny&, _signature...) >;

			static const std::size_t m_containerId;

			static std::vector<FunctorType> m_functors;
			static std::vector<MethodPtrType> m_methodPtrs;
			static std::vector<CtorFunctorType> m_ctorPtrs;

			GETTER_STATIC_REF(std::vector<FunctorType>, Functors, m_functors)
			GETTER_STATIC_REF(std::vector<MethodPtrType>, MethodFunctors, m_methodPtrs)
			GETTER_STATIC_REF(std::vector<CtorFunctorType>, CtorFunctors, m_ctorPtrs)

			friend access::Function;
			friend class SetupMethod<FunctorContainer<_signature...>>;
			friend class SetupFunction<FunctorContainer<_signature...>>;
			friend class SetupConstructor<FunctorContainer<_signature...>>;
			friend class CallReflector<FunctorContainer<_signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};

		extern std::size_t g_signIdCounter;

		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = g_signIdCounter++;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::FunctorType> FunctorContainer<_signature...>::m_functors;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::CtorFunctorType> FunctorContainer<_signature...>::m_ctorPtrs;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::MethodPtrType> FunctorContainer<_signature...>::m_methodPtrs;
	}
}

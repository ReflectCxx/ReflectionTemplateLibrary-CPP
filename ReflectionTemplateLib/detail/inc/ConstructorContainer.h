#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupConstructor.hpp"

namespace rtl {

	namespace builder {
		template<class ..._args>
		class FunctionBuilder;
	}

	namespace detail
	{
		template<class ..._signature>
		class ConstructorContainer : SetupConstructor<ConstructorContainer<_signature...>>,
					 CallReflector<ConstructorContainer<_signature...>>
		{
			using CtorFunctorType = std::function < access::RStatus(_signature...) >;

			static const std::size_t m_containerId;

			static std::vector<CtorFunctorType> m_ctorPtrs;

			static GETTER(std::size_t, ContainerId, m_containerId,)
			static GETTER_REF(std::vector<CtorFunctorType>, CtorFunctors, m_ctorPtrs)

			friend access::Function;
			friend class SetupConstructor<ConstructorContainer<_signature...>>;
			friend class CallReflector<ConstructorContainer<_signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};

		extern std::size_t g_signIdCounter;

		template<class ..._signature>
		const std::size_t ConstructorContainer<_signature...>::m_containerId = g_signIdCounter++;

		template<class ..._signature>
		std::vector<typename ConstructorContainer<_signature...>::CtorFunctorType> ConstructorContainer<_signature...>::m_ctorPtrs;
	}
}

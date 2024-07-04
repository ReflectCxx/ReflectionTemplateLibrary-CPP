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
			static std::vector< std::pair<std::size_t, CtorFunctorType> > m_ctorPtrs;

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static std::vector< std::pair<std::size_t, CtorFunctorType> >& getCtorFunctors() {
				return m_ctorPtrs;
			}

			friend access::Method;
			friend access::Function;

			friend class SetupConstructor<ConstructorContainer<_signature...>>;
			friend class CallReflector<ConstructorContainer<_signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};

		extern std::size_t g_containerIdCounter;

		template<class ..._signature>
		const std::size_t ConstructorContainer<_signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		std::vector< std::pair<std::size_t, typename ConstructorContainer<_signature...>::CtorFunctorType> > 
		ConstructorContainer<_signature...>::m_ctorPtrs;
	}
}

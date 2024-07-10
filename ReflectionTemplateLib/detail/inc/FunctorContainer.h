#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl {

	namespace access {
		class Method;
	}

	namespace detail
	{
		class ReflectionBuilder;
		extern std::size_t g_containerIdCounter;

		template<class ..._signature>
		class FunctorContainer : SetupFunction<FunctorContainer<_signature...>>,
					 SetupConstructor<FunctorContainer<_signature...>>,
					 CallReflector<FunctorContainer<_signature...>>
		{
			using FunctionLambda = std::function < access::RStatus(_signature...) >;

			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, FunctionLambda> > m_functors;

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static std::vector< std::pair<std::size_t, FunctionLambda> >& getFunctors() {
				return m_functors;
			}

			friend access::Method;
			friend access::Function;
			friend ReflectionBuilder;
			friend CallReflector<FunctorContainer<_signature...>>;
			friend SetupFunction<FunctorContainer<_signature...>>;
			friend SetupConstructor<FunctorContainer<_signature...>>;
		};


		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		std::vector< std::pair< std::size_t, typename FunctorContainer<_signature...>::FunctionLambda> > 
		FunctorContainer<_signature...>::m_functors;
	}
}

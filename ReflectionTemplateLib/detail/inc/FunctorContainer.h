#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl {

	namespace detail
	{
		class ReflectionBuilder;
		extern std::size_t g_containerIdCounter;

		template<class ..._signature>
		class FunctorContainer : public SetupFunction<FunctorContainer<_signature...>>,
					 public SetupConstructor<FunctorContainer<_signature...>>,
					 public CallReflector<FunctorContainer<_signature...>>
		{
			using FunctionLambda = std::function < access::RStatus(_signature...) >;
		public:

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			const static std::vector< std::pair<std::size_t, FunctionLambda> >& getFunctors() {
				return m_functors;
			}

		private:
			
			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, FunctionLambda> > m_functors;

			static void pushBack(const std::size_t& pHashCode, const FunctionLambda& pFunctor) {
				m_functors.emplace_back(pHashCode, pFunctor);
			}

			friend ReflectionBuilder;
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

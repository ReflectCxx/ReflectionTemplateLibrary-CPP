#pragma once

#include <mutex>
#include <atomic>
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
		extern std::atomic<std::size_t> g_containerIdCounter;

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

			const static std::vector<FunctionLambda>& getFunctors() {
				return m_functors;
			}

		private:
			
			static const std::size_t m_containerId;
			static std::vector<FunctionLambda> m_functors;

			static const std::size_t pushBack(const FunctionLambda& pFunctor, 
							  std::function<const std::size_t()> pGetIndex,
							  std::function<void(const std::size_t&)> pUpdate)
			{
				static std::mutex mtx;
				std::lock_guard<std::mutex> lock(mtx);

				std::size_t index = pGetIndex();
				if (index == -1) {
					index = m_functors.size();
					pUpdate(index);
					m_functors.push_back(pFunctor);
				}
				return index;
			}

			friend ReflectionBuilder;
			friend SetupFunction<FunctorContainer<_signature...>>;
			friend SetupConstructor<FunctorContainer<_signature...>>;
		};

		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::FunctionLambda> FunctorContainer<_signature...>::m_functors;
	}
}
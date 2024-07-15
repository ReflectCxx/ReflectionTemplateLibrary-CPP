#pragma once

#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.hpp"

namespace rtl {

	namespace detail
	{
		class ReflectionBuilder;
		extern std::atomic<std::size_t> g_containerIdCounter;

		template<TypeQ, class ..._signature>
		class MethodContainer;

		template<class ..._signature>
		class MethodContainer<TypeQ::Mute, _signature...> : public SetupMethod<MethodContainer<TypeQ::Mute, _signature...>>,
			public CallReflector<MethodContainer<TypeQ::Mute, _signature...>>
		{
			using MethodLambda = std::function < access::RStatus(std::any, _signature...) >;

		public:

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static const std::vector<MethodLambda>& getMethodFunctors() {
				return m_methodPtrs;
			}

		private:

			static const std::size_t m_containerId;
			static std::vector<MethodLambda> m_methodPtrs;

			static const std::size_t pushBack(const MethodLambda& pFunctor,
							  std::function<const std::size_t()> pGetIndex,
							  std::function<void(const std::size_t&)> pUpdateIndex)
			{
				static std::mutex mtx;
				std::lock_guard<std::mutex> lock(mtx);

				std::size_t index = pGetIndex();
				if (index == -1) {
					index = m_methodPtrs.size();
					pUpdateIndex(index);
					m_methodPtrs.push_back(pFunctor);
				}
				return index;
			}

			friend ReflectionBuilder;
			friend SetupMethod<MethodContainer<TypeQ::Mute, _signature...>>;
		};

		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Mute, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

		template<class ..._signature>
		std::vector<typename MethodContainer<TypeQ::Mute, _signature...>::MethodLambda>
		MethodContainer<TypeQ::Mute, _signature...>::m_methodPtrs;
	}
	

	namespace detail
	{
		template<class ..._signature>
		class MethodContainer<TypeQ::Const, _signature...> : public SetupMethod<MethodContainer<TypeQ::Const, _signature...>>,
								     public CallReflector<MethodContainer<TypeQ::Const, _signature...>>
		{
			using MethodLambda = std::function < access::RStatus(std::any, _signature...) >;

		public:

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static const std::vector<MethodLambda>& getMethodFunctors() {
				return  m_methodPtrs;
			}

		private:

			static const std::size_t m_containerId;
			static std::vector<MethodLambda> m_methodPtrs;

			static const std::size_t pushBack(const MethodLambda& pFunctor,
							  std::function<const std::size_t()> pGetIndex,
							  std::function<void(const std::size_t&)> pUpdateIndex)
			{
				static std::mutex mtx;
				std::lock_guard<std::mutex> lock(mtx);

				std::size_t index = pGetIndex();
				if (index == -1) {
					index = m_methodPtrs.size();
					pUpdateIndex(index);
					m_methodPtrs.push_back(pFunctor);
				}
				return index;
			}

			friend ReflectionBuilder;
			friend SetupMethod<MethodContainer<TypeQ::Const, _signature...>>;
		};

		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Const, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

		template<class ..._signature>
		std::vector<typename MethodContainer<TypeQ::Const, _signature...>::MethodLambda> 
		MethodContainer<TypeQ::Const, _signature...>::m_methodPtrs;
	}
}
#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.hpp"

namespace rtl {

	namespace detail
	{
		class ReflectionBuilder;
		extern std::size_t g_containerIdCounter;

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

			static const std::vector< std::pair<std::size_t, MethodLambda> >& getMethodFunctors() {
				return m_methodPtrs;
			}

		private:

			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, MethodLambda> > m_methodPtrs;

			static void pushBack(const std::size_t& pHashCode, const MethodLambda& pFunctor) {
				m_methodPtrs.emplace_back(pHashCode, pFunctor);
			}

			friend ReflectionBuilder;
			friend SetupMethod<MethodContainer<TypeQ::Mute, _signature...>>;		
		};


		template<class ..._signature>
		class MethodContainer<TypeQ::Const, _signature...> : public SetupMethod<MethodContainer<TypeQ::Const, _signature...>>,
								     public CallReflector<MethodContainer<TypeQ::Const, _signature...>>
		{
			using MethodLambda = std::function < access::RStatus(std::any, _signature...) >;

		public:

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static const std::vector< std::pair<std::size_t, MethodLambda> >& getMethodFunctors() {
				return  m_methodPtrs;
			}

		private:

			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, MethodLambda> > m_methodPtrs;

			static void pushBack(const std::size_t& pHashCode, const MethodLambda& pFunctor) {
				m_methodPtrs.emplace_back(pHashCode, pFunctor);
			}

			friend ReflectionBuilder;
			friend SetupMethod<MethodContainer<TypeQ::Const, _signature...>>;
		};

		
		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Mute, _signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Const, _signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		std::vector< std::pair <std::size_t, typename MethodContainer<TypeQ::Mute, _signature...>::MethodLambda> > 
		MethodContainer<TypeQ::Mute, _signature...>::m_methodPtrs;

		template<class ..._signature>
		std::vector< std::pair <std::size_t, typename MethodContainer<TypeQ::Const, _signature...>::MethodLambda> > 
		MethodContainer<TypeQ::Const, _signature...>::m_methodPtrs;
	}
}
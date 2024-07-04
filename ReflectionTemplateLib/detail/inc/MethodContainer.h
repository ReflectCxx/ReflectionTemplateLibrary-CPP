#pragma once

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.hpp"

namespace rtl {

	namespace builder {
		template<class ..._args>
		class FunctionBuilder;
	}

	namespace detail
	{
		template<TypeQ, class ..._signature>
		class MethodContainer;

		template<class ..._signature>
		class MethodContainer<TypeQ::Vol, _signature...> : SetupMethod<MethodContainer<TypeQ::Vol, _signature...>>,
								   CallReflector<MethodContainer<TypeQ::Vol, _signature...>>
		{
			using MethodPtrType = std::function < access::RStatus(const access::UniqueAny&, _signature...) >;

			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, MethodPtrType> > m_methodPtrs;
			
			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static std::vector< std::pair<std::size_t, MethodPtrType> >& getMethodFunctors() {
				return m_methodPtrs;
			}

			friend access::Method;
			friend access::Function;
			friend class SetupMethod<MethodContainer<TypeQ::Vol, _signature...>>;
			friend class CallReflector<MethodContainer<TypeQ::Vol, _signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};


		template<class ..._signature>
		class MethodContainer<TypeQ::Const, _signature...> : SetupMethod<MethodContainer<TypeQ::Const, _signature...>>,
								     CallReflector<MethodContainer<TypeQ::Const, _signature...>>
		{
			using MethodPtrType = std::function < access::RStatus(const access::UniqueAny&, _signature...) >;

			static const std::size_t m_containerId;
			static std::vector< std::pair<std::size_t, MethodPtrType> > m_methodPtrs;

			static const std::size_t& getContainerId() {
				return m_containerId;
			}

			static std::vector< std::pair<std::size_t, MethodPtrType> >& getMethodFunctors() {
				return  m_methodPtrs;
			}

			friend access::Method;
			friend access::Function;
			friend class SetupMethod<MethodContainer<TypeQ::Const, _signature...>>;
			friend class CallReflector<MethodContainer<TypeQ::Const, _signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};

		extern std::size_t g_containerIdCounter;

		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Vol, _signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		std::vector< std::pair <std::size_t, typename MethodContainer<TypeQ::Vol, _signature...>::MethodPtrType> > 
		MethodContainer<TypeQ::Vol, _signature...>::m_methodPtrs;

		template<class ..._signature>
		const std::size_t MethodContainer<TypeQ::Const, _signature...>::m_containerId = g_containerIdCounter++;

		template<class ..._signature>
		std::vector< std::pair <std::size_t, typename MethodContainer<TypeQ::Const, _signature...>::MethodPtrType> > 
		MethodContainer<TypeQ::Const, _signature...>::m_methodPtrs;
	}
}

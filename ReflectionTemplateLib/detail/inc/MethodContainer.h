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
		template<typeQ, class ..._signature>
		class MethodContainer;

		template<class ..._signature>
		class MethodContainer<typeQ::Vol, _signature...> : SetupMethod<MethodContainer<typeQ::Vol, _signature...>>,
														   CallReflector<MethodContainer<typeQ::Vol, _signature...>>
		{
			using MethodPtrType = std::function < access::RStatus(access::UniqueAny&, _signature...) >;

			static const std::size_t m_containerId;

			static std::vector<MethodPtrType> m_methodPtrs;
			
			static GETTER(std::size_t, ContainerId, m_containerId,)
			static GETTER_REF(std::vector<MethodPtrType>, MethodFunctors, m_methodPtrs)

			friend access::Function;
			friend class SetupMethod<MethodContainer<typeQ::Vol, _signature...>>;
			friend class CallReflector<MethodContainer<typeQ::Vol, _signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};


		template<class ..._signature>
		class MethodContainer<typeQ::Const, _signature...> : SetupMethod<MethodContainer<typeQ::Const, _signature...>>,
															 CallReflector<MethodContainer<typeQ::Const, _signature...>>
		{
			using MethodPtrType = std::function < access::RStatus(const access::UniqueAny&, _signature...) >;

			static const std::size_t m_containerId;

			static std::vector<MethodPtrType> m_methodPtrs;

			static GETTER(std::size_t, ContainerId, m_containerId, )
			static GETTER_REF(std::vector<MethodPtrType>, MethodFunctors, m_methodPtrs)

			friend access::Function;
			friend class SetupMethod<MethodContainer<typeQ::Const, _signature...>>;
			friend class CallReflector<MethodContainer<typeQ::Const, _signature...>>;

			template<class ..._args>
			friend class builder::FunctionBuilder;
		};

		extern std::size_t g_signIdCounter;

		template<class ..._signature>
		const std::size_t MethodContainer<typeQ::Vol, _signature...>::m_containerId = g_signIdCounter++;

		template<class ..._signature>
		std::vector<typename MethodContainer<typeQ::Vol, _signature...>::MethodPtrType> MethodContainer<typeQ::Vol, _signature...>::m_methodPtrs;

		template<class ..._signature>
		const std::size_t MethodContainer<typeQ::Const, _signature...>::m_containerId = g_signIdCounter++;

		template<class ..._signature>
		std::vector<typename MethodContainer<typeQ::Const, _signature...>::MethodPtrType> MethodContainer<typeQ::Const, _signature...>::m_methodPtrs;
	}
}

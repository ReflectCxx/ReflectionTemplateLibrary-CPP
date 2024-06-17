#pragma once

#include <vector>
#include <iostream>
#include <functional>


namespace rtl {

	template<class ..._signature>
	class FunctorContainer
	{
		static const std::size_t m_containerId;

		static std::vector<std::function<void(_signature...)>> m_functors;

	public:

		static const std::size_t& getContainerId();

		template<class ..._params>
		static void reflectCall(std::size_t pFunctorId, _params..._args);

		template<class _returnType>
		static int addFunctor(_returnType(*pFunctor)(_signature...));

		template<class _recordType>
		static int addConstructor();
	};
}

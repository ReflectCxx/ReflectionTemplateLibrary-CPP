#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <functional>

#include "RObject.hpp"
#include "Constants.h"

namespace rtl {

	class Function;

	template<class ..._signature>
	class FunctorContainer
	{
	public: friend class Function;
		  
		  static const std::size_t& getContainerId();
		  
		  using FunctorType = std::function < std::unique_ptr<RObject> (_signature...) >;
		  using MethodPtrType = std::function < std::unique_ptr<RObject> (const std::unique_ptr<RObject>&, _signature...) >;

	private:
		
		static const std::size_t m_containerId;

		static std::vector<FunctorType> m_functors;
		static std::vector<MethodPtrType> m_methodPtrs;

		template<class _returnType>
		static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

		template<class _returnType>
		static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

		template<class _recordType, class _returnType>
		static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

		template<class _recordType, class _returnType>
		static int addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);

		template<class _recordType>
		static int addConstructor(const std::string& pCtorType);

		template<class ..._params>
		static std::unique_ptr<RObject> reflectCall(std::size_t pFunctorId, _params..._args);

		template<class ..._params>
		static std::unique_ptr<RObject> reflectCall(const std::unique_ptr<RObject>& pTarget, std::size_t pFunctorId, _params..._args);
	};
}

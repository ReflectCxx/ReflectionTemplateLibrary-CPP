#pragma once

#include <functional>

#include "Function.h"
#include "Instance.h"

namespace rtl {

	namespace access
	{
		class Method;
		class Record;

		template<FunctorType _type>
		class MethodInvoker
		{
			const Method& m_method;
			const Instance& m_target;
			
			MethodInvoker(const Method& pMethod, const Instance& pTarget);

		public:

			template<class ..._args>
			RStatus call(_args...) const noexcept;

			friend Method;
		};


		template<>
		class MethodInvoker<FunctorType::Static>
		{
			const Method& m_method;

			MethodInvoker(const Method& pMethod);

		public:

			template<class ..._args>
			RStatus call(_args...) const noexcept;

			friend Method;
		};


		class Method : public Function
		{
			Method(const Function& pFunction);

			Method(const Function& pFunction, const detail::FunctorId& pFunctorId,
				const std::string& pFunctorName, const std::string& pSignatureStr);

			template<class ..._args>
			RStatus invokeCtor(_args...params) const;

			template<class ..._args>
			RStatus invoke(const Instance& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConst(const Instance& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeStatic(_args...params) const;

			static Method getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId);

		public:

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			const MethodInvoker<FunctorType::Static> on() const;
			const MethodInvoker<FunctorType::Method> on(const Instance& pTarget) const;

			constexpr auto operator()() const
			{
				return [this](auto...params) {
					return Function::operator()(params...);
				};
			}

			constexpr auto operator()(const Instance& pTarget) const
			{
				return [&](auto...params)->RStatus
				{
					if (pTarget.isEmpty()) {
						return RStatus(Error::EmptyInstance);
					}

					if (pTarget.getTypeId() != getRecordTypeId()) {
						return RStatus(Error::InstanceTypeMismatch);
					}

					switch (pTarget.getQualifier())
					{
					case TypeQ::Mute: return invoke(pTarget, params...);
					case TypeQ::Const: return invokeConst(pTarget, params...);
					}
					return RStatus(Error::EmptyInstance);
				};
			}

			template<class ..._args>
			RStatus operator()(_args...) const noexcept = delete;

			template<class ..._args>
			RStatus call(_args...) const noexcept = delete;

			template<FunctorType _type>
			friend class MethodInvoker;
			friend detail::CxxReflection; 
			friend Record;
		};
	}
}
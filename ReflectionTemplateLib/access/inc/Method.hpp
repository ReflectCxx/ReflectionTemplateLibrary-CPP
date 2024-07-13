#pragma once
#include "Method.h"

namespace rtl 
{
	namespace access 
	{
		template<FunctorType _type>
		inline MethodInvoker<_type>::MethodInvoker(const Method& pMethod, const Instance& pTarget) 
			:m_method(pMethod)
			, m_target(pTarget) {
		}


		template<FunctorType _type>
		template<class ..._args>
		inline RStatus MethodInvoker<_type>::call(_args ...params) const noexcept
		{
			if (m_target.isEmpty()) {
				return RStatus(Error::EmptyInstance);
			}

			if (m_target.getTypeId() != m_method.getRecordTypeId()) {
				return RStatus(Error::InstanceTypeMismatch);
			}

			switch (m_target.getQualifier())
			{
			case TypeQ::Mute: return m_method.invoke(m_target, params...);
			case TypeQ::Const: return m_method.invokeConst(m_target, params...);
			}
			return RStatus(Error::EmptyInstance);
		}


		inline MethodInvoker<FunctorType::Static>::MethodInvoker(const Method& pMethod)
			:m_method(pMethod) {
		}


		template<class ..._args>
		inline RStatus MethodInvoker<FunctorType::Static>::call(_args ...params) const noexcept
		{
			return m_method.invokeStatic(params...);
		}
	}


	namespace access
	{
		inline const MethodInvoker<FunctorType::Static> Method::on() const
		{
			return MethodInvoker<FunctorType::Static>(*this);
		}


		inline const MethodInvoker<FunctorType::Method> Method::on(const Instance& pTarget) const
		{
			return MethodInvoker<FunctorType::Method>(*this, pTarget);
		}


		template<class ..._args>
		inline RStatus Method::invokeCtor(_args ...params) const
		{
			return Function::operator()(params...);
		}


		template<class ..._args>
		inline RStatus Method::invokeStatic(_args ...params) const
		{
			return Function::operator()(params...);
		}


		template<>
		inline const bool Method::hasSignature<void>() const
		{
			switch (getQualifier())
			{
			case TypeQ::None: return Function::hasSignature<void>();
			case TypeQ::Mute: return hasSignatureId(detail::MethodContainer<TypeQ::Mute>::getContainerId());
			case TypeQ::Const: return hasSignatureId(detail::MethodContainer<TypeQ::Const>::getContainerId());
			}
			return false;
		}


		template<class _arg0, class ..._args>
		inline const bool Method::hasSignature() const
		{
			switch (getQualifier())
			{
			case TypeQ::None: return Function::hasSignature<_arg0, _args...>();
			case TypeQ::Mute: return hasSignatureId(detail::MethodContainer<TypeQ::Mute, _arg0, _args...>::getContainerId());
			case TypeQ::Const: return hasSignatureId(detail::MethodContainer<TypeQ::Const, _arg0, _args...>::getContainerId());
			}
			return false;
		}


		template<class ..._args>
		inline RStatus Method::invokeConst(const Instance& pTarget, _args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::MethodContainer<TypeQ::Const, _args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::MethodContainer<TypeQ::Const, _args...>::reflectMethodCall(pTarget.get(), index, hashCode, params...);
			}
			else {
				const std::size_t& nonConstSignId = detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId();
				if (hasSignatureId(nonConstSignId, index, hashCode)) {
					return RStatus(Error::InstanceConstMismatch);
				}
			}
			return RStatus(Error::SignatureMismatch);
		}


		template<class ..._args>
		inline RStatus Method::invoke(const Instance& pTarget, _args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::MethodContainer<TypeQ::Mute, _args...>::reflectMethodCall(pTarget.get(), index, hashCode, params...);
			}
			else {
				return invokeConst(pTarget, params...);
			}
			return RStatus(Error::SignatureMismatch);
		}
	}
}
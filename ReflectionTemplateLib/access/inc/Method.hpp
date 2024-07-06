#include "Method.h"

namespace rtl {

	namespace access
	{
		inline StaticMethodInvoker::StaticMethodInvoker(const Function& pFunction)
			: m_function(pFunction) {
		}


		template<class ..._args>
		inline RStatus StaticMethodInvoker::operator()(_args ...params) const noexcept
		{
			return m_function(params...);
		}
	}


	namespace access
	{
		inline MethodInvoker::MethodInvoker(const Method& pMethod, const UniqueAny& pTarget)
			: m_method(pMethod)
			, m_target(pTarget) {
		}


		template<class ..._args>
		inline RStatus MethodInvoker::operator()(_args ...params) const noexcept
		{
			if (m_target.getQualifier() == TypeQ::Const) {
				return m_method.invokeConstMethod(m_target, params...);
			}
			else {
				return m_method.invokeMethod(m_target, params...);
			}
		}
	}


	namespace access
	{
		inline const StaticMethodInvoker Method::operator()() const
		{
			return StaticMethodInvoker(*this);
		}


		inline const MethodInvoker Method::operator()(const UniqueAny& pTarget) const
		{
			return MethodInvoker(*this, pTarget);
		}


		template<class ..._args>
		inline RStatus Method::invokeConstructor(_args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::ConstructorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::ConstructorContainer<_args...>::reflectConstructorCall(index, hashCode, params...);
			}
			return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Method::invokeConstMethod(const UniqueAny& pTarget, _args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::MethodContainer<TypeQ::Const, _args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::MethodContainer<TypeQ::Const, _args...>::reflectMethodCall(pTarget, index, hashCode, params...);
			}
			return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Method::invokeMethod(const UniqueAny& pTarget, _args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::MethodContainer<TypeQ::Mute, _args...>::reflectMethodCall(pTarget, index, hashCode, params...);
			}
			else {
				return invokeConstMethod(pTarget, params...);
			}
			return RStatus(false);
		}


		template<>
		inline const bool Method::hasSignature<void>() const
		{
			switch (getQualifier())
			{
				case TypeQ::None: {
					return Function::hasSignature<void>();
				}
				case TypeQ::Mute: {
					std::size_t index, hashCode;
					const std::size_t& signId = detail::MethodContainer<TypeQ::Mute>::getContainerId();
					return hasSignatureId(signId, index, hashCode);
				}
				case TypeQ::Const: {
					std::size_t index, hashCode;
					const std::size_t& signId = detail::MethodContainer<TypeQ::Const>::getContainerId();
					return hasSignatureId(signId, index, hashCode);
				}
				default: return false;
			}
		}


		template<class _arg0, class ..._args>
		inline const bool Method::hasSignature() const
		{
			switch (getQualifier())
			{
				case TypeQ::None: {
					return Function::hasSignature<_arg0, _args...>();
				}
				case TypeQ::Mute: {
					std::size_t index, hashCode;
					const std::size_t& signId = detail::MethodContainer<TypeQ::Mute, _arg0, _args...>::getContainerId();
					return hasSignatureId(signId, index, hashCode);
				}
				case TypeQ::Const: {
					std::size_t index, hashCode;
					const std::size_t& signId = detail::MethodContainer<TypeQ::Const, _arg0, _args...>::getContainerId();
					return hasSignatureId(signId, index, hashCode);
				}
				default: return false;
			}
		}
	}
}
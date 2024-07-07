#pragma once
#include "Method.h"

namespace rtl {

	namespace access
	{
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
		inline RStatus Method::invokeCtor(_args ...params) const
		{
			return Function::operator()(params...);

			//std::size_t index, hashCode;
			//const std::size_t& signId = detail::<_args...>::getContainerId();
			//if (hasSignatureId(signId, index, hashCode))
			//{
			//	return detail::ConstructorContainer<_args...>::reflectFunctionCall(index, hashCode, params...);
			//}
			//return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Method::invokeConst(const UniqueAny& pTarget, _args ...params) const
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
		inline RStatus Method::invoke(const UniqueAny& pTarget, _args ...params) const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::MethodContainer<TypeQ::Mute, _args...>::reflectMethodCall(pTarget, index, hashCode, params...);
			}
			else {
				return invokeConst(pTarget, params...);
			}
			return RStatus(false);
		}
	}
}
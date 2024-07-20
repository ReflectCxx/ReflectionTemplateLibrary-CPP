
#include "RStatus.h"
#include "SetupFunction.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const detail::FunctorId SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...))
		{
			static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				functorSet.emplace_back(pFunctor, pIndex);
			};
			const auto& getIndex = [&]()->const std::size_t {
				for (const auto& fptr : functorSet) {
					if (fptr.first == pFunctor) {
						return fptr.second;
					}
				}
				return -1;
			};

			const auto& retTypeId = TypeId<_returnType>::get();
			const auto functor = [=](_signature...params)->access::RStatus
			{
				if constexpr (std::is_same_v<_returnType, void>) {
					(*pFunctor)(params...);
					return access::RStatus(Error::None);
				}
				else {
					const _returnType& retObj = (*pFunctor)(params...);
					const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Mute;
					return access::RStatus(std::make_any<_returnType>(retObj), retTypeId, qualifier);
				}
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, retTypeId, TypeId<>::None, _derivedType::getContainerId(),
						 _derivedType::template getSignatureStr<_returnType>());
		}
	}
}

#include "RStatus.h"
#include "SetupConstructor.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline int SetupConstructor<_derivedType>::addConstructor()
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				std::function<void(const std::any&)> destructor = [](const std::any& pTarget)->void {
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
				};
				return access::RStatus(true, std::make_any<_recordType*>(retObj), typeId, destructor);
			};

			auto& ctorFunctors = _derivedType::getCtorFunctors();
			ctorFunctors.push_back(functor);
			return (ctorFunctors.size() - 1);
		}
	}
}
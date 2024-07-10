
#include "Method.h"

namespace rtl {

	namespace access 
	{
		Method::Method(const Function& pFunction)
			:Function(pFunction) {
		}


		Method::Method(const Function& pFunction, const detail::FunctorId& pFunctorId) 
			: Function(pFunction, pFunctorId, [&]()->std::string
			{
				if (pFunctorId.getFunctorType() == FunctorType::DCtor)
				{
					return (pFunction.getRecordName() + Member::DCTOR);
				}
				return pFunction.getFunctionName();
			}) 
		{}
	}
}
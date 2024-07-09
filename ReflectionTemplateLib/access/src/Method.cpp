
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
				switch (pFunctorId.getFunctorType())
				{
				case FunctorType::DCtor:
					return pFunction.getRecordName() + DCTOR_SUFFIX;
				case FunctorType::ConstConverter:
					return pFunction.getRecordName() + CONST_CONVERTER_SUFFIX;
				}
				return std::string();
			}) 
		{}
	}
}
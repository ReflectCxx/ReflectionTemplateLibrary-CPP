
#include "Method.h"
#include "Constants.hpp"

namespace rtl {

	namespace access 
	{
		Method::Method(const Function& pFunction)
			:Function(pFunction) {
		}


		Method::Method(const Function& pFunction, const detail::FunctorId& pFunctorId, const std::string& pFunctorName)
			: Function(pFunction, pFunctorId, pFunctorName) {
		}


		Method Method::getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId)
		{
			const std::string dctorStr = getDctorName(pFunction.getRecordName());
			return Method(pFunction, pFunctorId, dctorStr);
		}
	}
}
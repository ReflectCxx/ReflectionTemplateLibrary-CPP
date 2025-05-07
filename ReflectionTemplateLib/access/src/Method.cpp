
#include "Method.h"

namespace rtl {

	namespace access 
	{
		Method::Method(const Function& pFunction)
			: Function(pFunction) {
		}


		Method::Method(const Function& pFunction, const detail::FunctorId& pFunctorId, const std::string& pFunctorName)
			: Function(pFunction, pFunctorId, pFunctorName) {
		}


		Method Method::getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId)
		{
			const std::string dctorStr = CtorName::dctor(pFunction.getRecordName());
			return Method(pFunction, pFunctorId, dctorStr);
		}


		Method Method::getCopyConstructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId)
		{
			const std::string cpCtorStr = CtorName::copyCtor(pFunction.getRecordName());
			return Method(pFunction, pFunctorId, cpCtorStr);
		}
	}
}
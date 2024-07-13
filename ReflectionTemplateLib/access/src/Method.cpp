
#include "Method.h"

namespace rtl {

	namespace access 
	{
		Method::Method(const Function& pFunction)
			:Function(pFunction) {
		}


		Method::Method(const Function& pFunction, const detail::FunctorId& pFunctorId,
			const std::string& pFunctorName, const std::string& pSignatureStr)
			: Function(pFunction, pFunctorId, pFunctorName, pSignatureStr) {
		}


		Method Method::getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId)
		{
			const std::string dctorStr = pFunction.getRecordName() + Ctor::DCTOR;
			const std::string signatureStr = pFunction.getRecordName() + "::~()";
			return Method(pFunction, pFunctorId, dctorStr, signatureStr);
		}
	}
}
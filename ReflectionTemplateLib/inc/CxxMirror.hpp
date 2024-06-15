#include "CxxMirror.h"
#include "Constants.h"
#include "NameSpace.h"
#include "FunctorContainer.hpp"

namespace rtl {

	template<class ..._signaturesTypeList>
	inline CxxMirror<_signaturesTypeList...>::CxxMirror(std::vector<Function> pFunctions)
	{
		NameSpace::init(pFunctions, m_namespaces);
	}

	template<class ..._signaturesTypeList>
	inline std::optional<Function> CxxMirror<_signaturesTypeList...>::getFunction(const std::string& pFunction)
	{
		return getFunction(NS_GLOBAL, pFunction);
	}

	template<class ..._signaturesTypeList>
	inline const bool CxxMirror<_signaturesTypeList...>::init()
	{
		TypesDescriptor::init();
		return true;
	}

	template<class ..._signaturesList>
	inline auto CxxMirror<_signaturesList...>::operator()(const Function& pFunction)
	{
		return [&](auto...params) {
			TypesDescriptor::call(pFunction.getSignatureId(), pFunction.getFunctorId(), params...);
		};
	}

	template<class ..._signaturesList>
	inline std::optional<Function> CxxMirror<_signaturesList...>::getFunction(const std::string& pNameSpace, const std::string& pFunction)
	{
		const auto& itr = m_namespaces.find(pNameSpace);
		if (itr != m_namespaces.end()) {
			return itr->second.getFunction(pFunction);
		}
		return std::nullopt;
	}
}
#pragma once

#include "CxxMirror.hpp"

namespace rtl_tests {

	/* CxxReflection, a singleton class, which encapsulates the registration of all types and function signatures and
	*  creates an object of CxxMirror<...> which provides complete functionality of reflection. Template parameters
	*  of CxxMirror are the function signatures & types to be reflected. Uses following syntax,
	* 
	*	CxxMirror< 
	*		TypeSignature<..function signature 1..>
	*		TypeSignature<..function signature 2..>
	*		......
	*		TypeSignature<..function signature N..>
	*	std::nullptr_t>
	*/
	struct CxxReflection
	{
		using Reflection =
			rtl::CxxMirror<
				rtl::TypeSignature<>,	//Function signature, taking zero arguments, Mandatory.
				rtl::TypeSignature<const char*, const char*>,
				rtl::TypeSignature<unsigned int>,
				rtl::TypeSignature<float>,
				rtl::TypeSignature<const char*, const char*, unsigned int, float>,
				rtl::TypeSignature<const char*, std::string, unsigned int, double>,
			std::nullptr_t>;			//Mandatory, to denote list termination.

		//Mandatory, to initialize the ids to types registered.
		static const bool init;

		//Singleton object provider.
		static Reflection& instance();
	};
}
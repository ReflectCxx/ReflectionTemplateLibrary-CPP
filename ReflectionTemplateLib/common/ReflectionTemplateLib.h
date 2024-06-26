#pragma once

#include "Record.hpp"   //Interface to access user defined classes/structs and its members and to create objects.


#include "Method.hpp"   //Interface to call methods on objects created via reflection of classes/structs.
#include "Function.hpp" //interface to call global functions (may be in a namespace), static methods(member functions) of classes/structs. 
/* Difference between Method & Function class:
*	- They both overload the operator(), but when calling via "Function" object, it takes parameters to be passed.
*	- When calling via "Method", it takes target object on which the method need to be called and then provides
*	  interface "invoke()" to pass the parameters. So,
*		Function call:	function(..args..);
*		Method call:	method(targetObj).invoke(..args..);
*/


/*
* Provides interface to register all types.
* Reflect().nameSpace("namespaceName").function("funcName").build(funcPtr)
* Reflect().nameSpace("namespaceName").record("className").method("methodName").build(&MethodPtr)
*/
#include "Reflect.hpp"


/* Class containing everything required to provide reflection interface and functionality.
* Users are required to instantiate this class and pass all registration as constructor parameter.
*/
#include "CxxMirror.h"

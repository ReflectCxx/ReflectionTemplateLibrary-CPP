#pragma once

/*
* Provides interface to register all types.
* Reflect().nameSpace("namespaceName").function<>("funcName").build(funcPtr)
* Reflect().nameSpace("namespaceName").record("className").constructor<>("methodName").build()
* Reflect().nameSpace("namespaceName").record("className").method<>("methodName").build(&MethodPtr) 
* 
* template params are for overloading the different signatures (of method/function/constructors).
* if the function/method is unique, no need to specify the signature as templete params. if they
* are overloaded and any one of them takes zero params, then that function must be registered by specifying <void> as
* template parameter. Constructor overloads do not need to specify <void> as tempelate params even if other overload exists.
* decleared in namespace rtl::builder. */
#include "Reflect.hpp"


/*
* Interface to access user defined class/struct(s) and its members(veariables, functions, constructor & destructor).
* it encapsulates all the member's information and provides objects (Function/Method) to access them.
* the Record objects are obtained from reflection object ie, CxxMirror, querying by string.
* decleared in namespace rtl::access.*/
#include "Record.hpp"


/*
* Provides interface to call global functions (may or not be in a namespace), static member functions of class/struct(s).
* it overloads "operator()". can be called as functionObj(..args..), where functionObj is object of "class Function"
* the global Function objects can be directly obtained from reflection object ie, CxxMirror, querying by string.
* decleared in namespace rtl::access.*/
#include "Function.hpp"


/* 
* Provides interface to call methods on objects created via reflection of classes/structs.
* it also overloads "operator()", but this takes the object (type 'UniqueAny') instead of the method arguments and returns
* the obeject of class 'MethodInvoker, which provides 'invoke' function to finally call the method with arguments.
* 
* Difference between Method & Function class:
*   - They both overload the operator(), but when calling via "Function" object, it takes parameters to be passed.
*   - When calling via "Method", it takes target object on which the reflected method needs to be called and then provides
*     interface 'invoke()' on the return value, which takes the actual parameters. So,
*       Function call:	function(..args..);
*       Method call:	method(targetObj).invoke(..args..);
* 
* decleared in namespace rtl::access. */
#include "Method.hpp"


/*
* RStatus, Provides interface to check if the call succeeded and to access the return values obtained 
* from calling methods/functions/constructors if any. It contains object of UniqueAny, which may or may not have the return value.
* UniqueAny hold resource, it is owned by RStatus, once 'reteaseReturn()' is called on RStatus, it will relieve itseld from the ownership.
* 
* 'UniqueAny' is a wrapper class for std::any, which adds interface to perform exception-safe non-rtti type check. and
* calls the destructor when goes out of scope, only for the objects created by calling instance() method on Record objects, 
* ie, the destructor will only be called for the objects that are created via reflection on the heap. It will not be called for 
* the objects recieved as return vales from reflected method/function call.
* - supports only move semantics.
* Interfaces:
*   - get(), provides the std::any object, which can be checked using has_value() if it contains any object.
*   - isOfType<_type>(), checks of the underlying object is of '_type'.
*   - finally, std::any_cast<_type>() can be used to obtain the actual object with '_type'
* For example, a function returns value as 'std::string', but calling it via reflection will return the 'UniqueAny'
* object (suppose, retObj). it must be validated before finally applying the std::any_cast<>() to avoid exception, like,
*    1. if(retObj.get().has_value() == true)
*    2. if(retObj.isOfType<std::string>() == true)
*    3. std::string str = std::any_cast<std::string>(retObj.get())
* 
* decleared in namespace rtl::access. */
#include "RStatus.h"


/* Class containing everything required to provide reflection interface and functionality.
* Users are required to instantiate this class and pass all registration as constructor parameter. */
#include "CxxMirror.h"
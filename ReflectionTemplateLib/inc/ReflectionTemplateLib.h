#pragma once

#include "Record.hpp"   //Reflects user defined classes/structs.

#include "Method.hpp"   //Reflects methods(member functions) of classes/structs.

#include "Function.hpp" //Reflects global functions (may be in a namespace), static methods(member functions) of classes/structs.


/* Class containing everything required to provide reflection interface and functionality. 
 * Users are required to instantiate this class and pass all registration as constructor parameter. */
#include "CxxMirror.h"
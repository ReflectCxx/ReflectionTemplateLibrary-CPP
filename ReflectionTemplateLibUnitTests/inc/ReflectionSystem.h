#pragma once

#include "RTLibInterface.h"

namespace rtl
{
    namespace unit_test 
    {
        struct ReflectionSystem 
        {
            static bool init() 
            {
                //instantiating a reflection system to initialize the RObject's cast/conversion mechanism.
                static rtl::access::CxxMirror reflectionSystem({/*...empty reflection system...no types passed...*/});
                return true;
            }
        };
    }
}
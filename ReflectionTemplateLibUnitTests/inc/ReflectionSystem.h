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
                //instantiate the empty reflection system to initialize the implicit conversion mechanism.
                static rtl::access::CxxMirror reflectionSystem({});
                return true;
            }
        };
    }
}
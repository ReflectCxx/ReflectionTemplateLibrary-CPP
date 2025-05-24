#pragma once

namespace rtl::access {
    class CxxMirror;
}

namespace rtl::detail
{
    class RObjectConverterInit
    {
        static void registerConverters();

        friend rtl::access::CxxMirror;
    };
}
#pragma once

#include "BenchMark.h"

struct ReflectedCall
{
    static void noReturn(benchmark::State& state);
    
    static void noReturnMethod(benchmark::State& state);

    static void withReturn(benchmark::State& state);

    static void withReturnMethod(benchmark::State& state);
};

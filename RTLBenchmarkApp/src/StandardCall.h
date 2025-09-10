#pragma once

#include "BenchMark.h"

struct DirectCall
{
    static void noReturn(benchmark::State& state);
    
    static void withReturn(benchmark::State& state);
};


struct StdFunctionCall
{
    static void noReturn(benchmark::State& state);
    
    static void noReturnMethod(benchmark::State& state);

    static void withReturn(benchmark::State& state);

    static void withReturnMethod(benchmark::State& state);
};
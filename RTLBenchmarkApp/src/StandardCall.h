#pragma once

#include "BenchMark.h"

struct DirectCall
{
    static void noReturn(benchmark::State& state);
    
    static void withReturn(benchmark::State& state);
};


struct StdFuncCall
{
    static void noReturn(benchmark::State& state);

    static void withReturn(benchmark::State& state);
};


struct StdFuncMethodCall
{    
    static void noReturn(benchmark::State& state);

    static void withReturn(benchmark::State& state);
};
#pragma once

#include <benchmark/benchmark.h>

struct NativeCall
{
    static void returnVoid(benchmark::State& state);
    
    static void returnNonVoid(benchmark::State& state);
};


struct StdFunction_call
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};


struct StdFunction_callMethod
{    
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};
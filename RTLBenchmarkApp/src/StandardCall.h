#pragma once

#include <benchmark/benchmark.h>

struct NativeCall
{
    static void returnTypeVoid(benchmark::State& state);
    
    static void returnTypeNonVoid(benchmark::State& state);
};


struct StdFunctionCall
{
    static void returnTypeVoid(benchmark::State& state);

    static void returnTypeNonVoid(benchmark::State& state);
};


struct StdFunctionMethodCall
{    
    static void returnTypeVoid(benchmark::State& state);

    static void returnTypeNonVoid(benchmark::State& state);
};
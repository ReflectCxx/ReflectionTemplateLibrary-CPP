#pragma once

#include <benchmark/benchmark.h>

struct NativeCall
{
    static void set(benchmark::State& state);
    
    static void get(benchmark::State& state);
};


struct StdFuncCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct StdFuncMethodCall
{    
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
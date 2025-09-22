#pragma once

#include <benchmark/benchmark.h>

struct RtlReflectedCall_retUnknown
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct RtlReflectionMethodCall_retUnknown
{    
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
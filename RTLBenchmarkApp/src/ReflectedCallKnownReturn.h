#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCallKnownReturn
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct FunctionPointerCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct ReflectedMethodCallKnownReturn
{    
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
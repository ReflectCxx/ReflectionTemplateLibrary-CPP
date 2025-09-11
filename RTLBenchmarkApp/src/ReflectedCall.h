#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCall
{
    static void noReturn(benchmark::State& state);

    static void withReturn(benchmark::State& state);
};


struct ReflectedMethodCall
{    
    static void noReturn(benchmark::State& state);

    static void withReturn(benchmark::State& state);
};
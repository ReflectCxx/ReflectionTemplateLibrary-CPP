#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCallUnknownReturn
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct ReflectedMethodCallUnknownReturn
{    
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
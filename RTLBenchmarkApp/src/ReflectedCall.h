#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);

    static void new_design_set(benchmark::State& state);
};


struct ReflectedMethodCall
{    
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCallUnknownReturn
{
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};


struct ReflectedMethodCallUnknownReturn
{    
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};
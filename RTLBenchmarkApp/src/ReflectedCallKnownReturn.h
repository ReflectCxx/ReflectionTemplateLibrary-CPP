#pragma once

#include <benchmark/benchmark.h>

struct RtlReflectedCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct FunctionPointerCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct MethodFnPointerCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};


struct RtlReflectedMethodCall
{
    static void set(benchmark::State& state);

    static void get(benchmark::State& state);
};
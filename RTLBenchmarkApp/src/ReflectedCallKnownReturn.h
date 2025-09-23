#pragma once

#include <benchmark/benchmark.h>

struct RtlFunction_call
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};


struct NativeFunctionPtr_call
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};


struct NativeFunctionPtr_callMethod
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};


struct RtlFunction_callMethod
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};
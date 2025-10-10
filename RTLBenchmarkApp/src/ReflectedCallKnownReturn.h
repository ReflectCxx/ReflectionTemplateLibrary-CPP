#pragma once

#include <benchmark/benchmark.h>

struct RtlStaticTyped_call
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


struct RtlStaticTyped_callMethod
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};
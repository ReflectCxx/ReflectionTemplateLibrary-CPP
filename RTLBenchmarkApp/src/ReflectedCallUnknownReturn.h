#pragma once

#include <benchmark/benchmark.h>

struct RtlErasedReturnType_call
{
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);
};


struct RtlErasedReturnType_callMethod
{    
    static void returnVoid(benchmark::State& state);

    static void returnNonVoid(benchmark::State& state);

    static void unknownTarget_returnVoid(benchmark::State& state);

    static void unknownTarget_returnNonVoid(benchmark::State& state);
};
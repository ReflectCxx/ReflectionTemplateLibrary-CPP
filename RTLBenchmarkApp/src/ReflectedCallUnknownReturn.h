#pragma once

#include <benchmark/benchmark.h>

struct RtlErasedType_call_unknownReturn
{
    static void Void(benchmark::State& state);

    static void NonVoid(benchmark::State& state);
};


struct RtlErasedType_callMethod_unknownReturn
{    
    static void Void(benchmark::State& state);

    static void NonVoid(benchmark::State& state);

    static void unknownTarget_Void(benchmark::State& state);

    static void unknownTarget_NonVoid(benchmark::State& state);
};
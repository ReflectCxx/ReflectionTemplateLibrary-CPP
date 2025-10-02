#pragma once

#include <benchmark/benchmark.h>

struct RtlFunction_call_ReturnUnknown
{
    static void Void(benchmark::State& state);

    static void NonVoid(benchmark::State& state);
};


struct RtlFunction_callMethod_ReturnUnknown
{    
    static void Void(benchmark::State& state);

    static void NonVoid(benchmark::State& state);

    static void erasedTarget_Void(benchmark::State& state);

    static void erasedTarget_NonVoid(benchmark::State& state);
};
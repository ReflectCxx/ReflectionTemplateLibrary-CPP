#pragma once

#include <benchmark/benchmark.h>

struct RtlFunction_call_ReturnUnknown
{
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};


struct RtlFunction_callMethod_ReturnUnknown
{    
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};
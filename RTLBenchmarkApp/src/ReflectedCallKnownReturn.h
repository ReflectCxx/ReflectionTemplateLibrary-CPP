#pragma once

#include <benchmark/benchmark.h>

struct ReflectedCallKnownReturn
{
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};


struct FunctionPointerCall
{
    static void returnTypeVoid(benchmark::State& state);

    static void returnTypeNonVoid(benchmark::State& state);
};


struct MethodFnPointerCall
{
    static void returnTypeVoid(benchmark::State& state);

    static void returnTypeNonVoid(benchmark::State& state);
};


struct ReflectedMethodCallKnownReturn
{
    static void typeVoid(benchmark::State& state);

    static void typeNonVoid(benchmark::State& state);
};
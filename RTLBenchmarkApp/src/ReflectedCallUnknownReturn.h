#pragma once

#include <benchmark/benchmark.h>

namespace bm_rtl
{
    struct function_ErasedReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method___ErasedReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method___ErasedTargetType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method___ErasedTargetAndReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
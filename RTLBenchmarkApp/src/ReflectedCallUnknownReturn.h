#pragma once

#include <benchmark/benchmark.h>

namespace bm_rtl
{
    struct function__ErasedReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method____ErasedReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method____ErasedTargetType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method____ErasedTargetAndReturnType
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
#pragma once

#include <benchmark/benchmark.h>

namespace bm_call
{
    struct direct__Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}

namespace bm_std
{
    struct function_calls__Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };


    struct function_calls____Method
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
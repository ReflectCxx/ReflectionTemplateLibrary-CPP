#pragma once

#include <benchmark/benchmark.h>

namespace bm_call
{
    struct direct_Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}

namespace bm_std
{
    struct function_CallsFunction
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };


    struct function___CallsMethod
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
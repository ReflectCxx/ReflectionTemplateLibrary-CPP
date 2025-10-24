#pragma once

#include <benchmark/benchmark.h>

namespace bm_call
{
    struct by_FunctionPtr_Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct by_FunctionPtr___Method
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}

namespace bm_rtl
{
    struct function_CallsFunction
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method_____CallsMethod
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
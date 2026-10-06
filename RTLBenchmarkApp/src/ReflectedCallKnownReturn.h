#pragma once

#include <benchmark/benchmark.h>

namespace bm_call
{
    struct via_function_ptr__Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct via_function_ptr____Method
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}

namespace bm_rtl
{
    struct function_calls__Function
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };

    struct method_calls______Method
    {
        static void set_string(benchmark::State& state);

        static void get_string(benchmark::State& state);
    };
}
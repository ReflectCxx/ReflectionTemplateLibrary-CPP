
#include <iostream>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCallKnownReturn.h"
#include "ReflectedCallUnknownReturn.h"

BENCHMARK(bm_call::direct__Function::set_string);

BENCHMARK(bm_call::via_function_ptr__Function::set_string);
BENCHMARK(bm_call::via_function_ptr____Method::set_string);

BENCHMARK(bm_std::function_calls__Function::set_string);
BENCHMARK(bm_std::function_calls____Method::set_string);

BENCHMARK(bm_rtl::function_calls__Function::set_string);
BENCHMARK(bm_rtl::method_calls______Method::set_string);

BENCHMARK(bm_rtl::function__ErasedReturnType::set_string);
BENCHMARK(bm_rtl::method____ErasedReturnType::set_string);
BENCHMARK(bm_rtl::method____ErasedTargetType::set_string);
BENCHMARK(bm_rtl::method____ErasedTargetAndReturnType::set_string);

BENCHMARK(bm_call::direct__Function::get_string);

BENCHMARK(bm_call::via_function_ptr__Function::get_string);
BENCHMARK(bm_call::via_function_ptr____Method::get_string);

BENCHMARK(bm_std::function_calls__Function::get_string);
BENCHMARK(bm_std::function_calls____Method::get_string);

BENCHMARK(bm_rtl::function_calls__Function::get_string);
BENCHMARK(bm_rtl::method_calls______Method::get_string);

BENCHMARK(bm_rtl::function__ErasedReturnType::get_string);
BENCHMARK(bm_rtl::method____ErasedReturnType::get_string);
BENCHMARK(bm_rtl::method____ErasedTargetType::get_string);
BENCHMARK(bm_rtl::method____ErasedTargetAndReturnType::get_string);

namespace bm 
{
    extern std::size_t g_work_load;
}

int main(int argc, char** argv) 
{
    if (argc > 1)
    {
        bm::g_work_load = std::stoi(argv[1]);
        for (int i = 1; i < argc - 1; ++i) {
            argv[i] = argv[i + 1];
        }
        --argc;

        std::cout << "\n======== RTL Benchmark Configuration ========\n"
                    << "Workload: concatenate string of length 500\n"
                    << "Scale   : " << bm::g_work_load << " iterations\n"
                    << "=============================================\n\n";
    }

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
}

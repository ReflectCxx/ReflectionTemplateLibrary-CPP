
#include <iostream>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCallKnownReturn.h"
#include "ReflectedCallUnknownReturn.h"

BENCHMARK(bm_call::direct_Function::set_string);

BENCHMARK(bm_call::by_FunctionPtr_Function::set_string);
BENCHMARK(bm_call::by_FunctionPtr___Method::set_string);

BENCHMARK(bm_std::function_CallsFunction::set_string);
BENCHMARK(bm_std::function___CallsMethod::set_string);

BENCHMARK(bm_rtl::function_CallsFunction::set_string);
BENCHMARK(bm_rtl::method_____CallsMethod::set_string);

BENCHMARK(bm_rtl::function_ErasedReturnType::set_string);
BENCHMARK(bm_rtl::method___ErasedReturnType::set_string);
BENCHMARK(bm_rtl::method___ErasedTargetType::set_string);
BENCHMARK(bm_rtl::method___ErasedTargetAndReturnType::set_string);

BENCHMARK(bm_call::direct_Function::get_string);

BENCHMARK(bm_call::by_FunctionPtr_Function::get_string);
BENCHMARK(bm_call::by_FunctionPtr___Method::get_string);

BENCHMARK(bm_std::function_CallsFunction::get_string);
BENCHMARK(bm_std::function___CallsMethod::get_string);

BENCHMARK(bm_rtl::function_CallsFunction::get_string);
BENCHMARK(bm_rtl::method_____CallsMethod::get_string);

BENCHMARK(bm_rtl::function_ErasedReturnType::get_string);
BENCHMARK(bm_rtl::method___ErasedReturnType::get_string);
BENCHMARK(bm_rtl::method___ErasedTargetType::get_string);
BENCHMARK(bm_rtl::method___ErasedTargetAndReturnType::get_string);

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

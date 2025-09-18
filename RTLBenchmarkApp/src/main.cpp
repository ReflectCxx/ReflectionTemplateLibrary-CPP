
#include <iostream>
#include <optional>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCall.h"

BENCHMARK(NativeCall::set);

BENCHMARK(StdFuncCall::set);
BENCHMARK(ReflectedCall::new_design_set);
BENCHMARK(ReflectedCall::set);

BENCHMARK(StdFuncMethodCall::set);
BENCHMARK(ReflectedMethodCall::set);

BENCHMARK(NativeCall::get);

BENCHMARK(StdFuncCall::get);
BENCHMARK(ReflectedCall::get);

BENCHMARK(StdFuncMethodCall::get);
BENCHMARK(ReflectedMethodCall::get);

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

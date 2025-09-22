
#include <iostream>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCallKnownReturn.h"
#include "ReflectedCallUnknownReturn.h"

BENCHMARK(NativeCall::returnTypeVoid);

BENCHMARK(FunctionPointerCall::returnTypeVoid);
BENCHMARK(MethodFnPointerCall::returnTypeVoid);

BENCHMARK(StdFunctionCall::returnTypeVoid);
BENCHMARK(StdFunctionMethodCall::returnTypeVoid);

BENCHMARK(ReflectedCallKnownReturn::typeVoid);
BENCHMARK(ReflectedMethodCallKnownReturn::typeVoid);

BENCHMARK(ReflectedCallUnknownReturn::typeVoid);
BENCHMARK(ReflectedMethodCallUnknownReturn::typeVoid);

BENCHMARK(NativeCall::returnTypeNonVoid);

BENCHMARK(FunctionPointerCall::returnTypeNonVoid);
BENCHMARK(MethodFnPointerCall::returnTypeNonVoid);

BENCHMARK(StdFunctionCall::returnTypeNonVoid);
BENCHMARK(StdFunctionMethodCall::returnTypeNonVoid);

BENCHMARK(ReflectedCallKnownReturn::typeNonVoid);
BENCHMARK(ReflectedMethodCallKnownReturn::typeNonVoid);

BENCHMARK(ReflectedCallUnknownReturn::typeNonVoid);
BENCHMARK(ReflectedMethodCallUnknownReturn::typeNonVoid);

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

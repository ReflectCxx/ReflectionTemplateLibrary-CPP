
#include <iostream>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCallKnownReturn.h"
#include "ReflectedCallUnknownReturn.h"

BENCHMARK(NativeCall::returnVoid);

BENCHMARK(NativeFunctionPtr_call::returnVoid);
BENCHMARK(NativeFunctionPtr_callMethod::returnVoid);

BENCHMARK(StdFunction_call::returnVoid);
BENCHMARK(StdFunction_callMethod::returnVoid);

BENCHMARK(RtlFunction_call::returnVoid);
BENCHMARK(RtlFunction_callMethod::returnVoid);

BENCHMARK(RtlFunction_call_ReturnUnknown::Void);
BENCHMARK(RtlFunction_callMethod_ReturnUnknown::Void);
BENCHMARK(RtlFunction_callMethod_ReturnUnknown::erasedTarget_Void);

BENCHMARK(NativeCall::returnNonVoid);

BENCHMARK(NativeFunctionPtr_call::returnNonVoid);
BENCHMARK(NativeFunctionPtr_callMethod::returnNonVoid);

BENCHMARK(StdFunction_call::returnNonVoid);
BENCHMARK(StdFunction_callMethod::returnNonVoid);

BENCHMARK(RtlFunction_call::returnNonVoid);
BENCHMARK(RtlFunction_callMethod::returnNonVoid);

BENCHMARK(RtlFunction_call_ReturnUnknown::NonVoid);
BENCHMARK(RtlFunction_callMethod_ReturnUnknown::NonVoid);
BENCHMARK(RtlFunction_callMethod_ReturnUnknown::erasedTarget_NonVoid);

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

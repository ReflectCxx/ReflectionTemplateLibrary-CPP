
#include <string>
#include <benchmark/benchmark.h>

#include "StandardCall.h"
#include "ReflectedCall.h"

std::size_t g_work_load_scale = 1;

BENCHMARK(DirectCall::noReturn);
BENCHMARK(StdFunctionCall::noReturn);
BENCHMARK(StdFunctionCall::noReturnMethod);
BENCHMARK(ReflectedCall::noReturn);
BENCHMARK(ReflectedCall::noReturnMethod);

BENCHMARK(DirectCall::withReturn);
BENCHMARK(StdFunctionCall::withReturn);
BENCHMARK(StdFunctionCall::withReturnMethod);
BENCHMARK(ReflectedCall::withReturn);
BENCHMARK(ReflectedCall::withReturnMethod);

BENCHMARK_MAIN();

#include <string>
#include <benchmark/benchmark.h>

#include "BenchMark.h"


BENCHMARK(rtl_bench::BenchMark::directCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::autoLambdaCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_noReturn);

BENCHMARK(rtl_bench::BenchMark::directCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::autoLambdaCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_withReturn);

BENCHMARK(rtl_bench::BenchMark::BM_LambdaFunc);
BENCHMARK(rtl_bench::BenchMark::BM_FunctionCall);

BENCHMARK_MAIN();

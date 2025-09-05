
#include <string>
#include <benchmark/benchmark.h>

#include "BenchMark.h"

// ------------------------------------------------------------
// Register benchmarks
// ------------------------------------------------------------

BENCHMARK(rtl_bench::BenchMark::directCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::lambdaCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedCall_noReturn);
//BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_noReturn);
//BENCHMARK(rtl_bench::BenchMark::directCall_withReturn);
//BENCHMARK(rtl_bench::BenchMark::lambdaCall_withReturn);
//BENCHMARK(rtl_bench::BenchMark::reflectedCall_withReturn);
//BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_withReturn);
BENCHMARK_MAIN();

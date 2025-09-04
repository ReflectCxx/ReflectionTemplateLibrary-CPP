
#include <string>
#include <benchmark/benchmark.h>

#include "BenchMark.h"

// ------------------------------------------------------------
// Register benchmarks
// ------------------------------------------------------------

BENCHMARK(rtl_bench::BenchMark::directCall);
BENCHMARK(rtl_bench::BenchMark::lambdaCall);
BENCHMARK(rtl_bench::BenchMark::reflectedCall);
BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall);

BENCHMARK_MAIN();

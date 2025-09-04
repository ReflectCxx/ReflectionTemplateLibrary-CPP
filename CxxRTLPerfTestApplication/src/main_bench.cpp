
#include <benchmark/benchmark.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../../CxxTestProps/inc/Person.h"
#include "../../CxxTestProps/inc/Complex.h"

// Direct call vs. Reflected call
// ------------------------------------------------------------
static void DirectCall(benchmark::State& state) 
{
    Person obj;
    for (auto _ : state) {
        benchmark::DoNotOptimize(complex::getMagnitude());
    }
}

static void ReflectedCall(benchmark::State& state)
{
    rtl::Function getMagnitude = test_mirror::cxx().mirror().getFunction(test_utils::str_complex,test_utils::str_getMagnitude).value();
    for (auto _ : state) {;
        benchmark::DoNotOptimize(getMagnitude.bind().call());
    }
}


// ------------------------------------------------------------
// Register benchmarks
// ------------------------------------------------------------
BENCHMARK(DirectCall);
BENCHMARK(ReflectedCall);

BENCHMARK_MAIN();

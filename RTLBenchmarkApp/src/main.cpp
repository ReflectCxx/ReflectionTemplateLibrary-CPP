
#include <string>
#include <benchmark/benchmark.h>

#include "BenchMark.h"

auto sendMessagePtr = rtl_bench::sendMessage;
auto getMessagePtr = rtl_bench::getMessage;
auto sendMessageNodePtr = &rtl_bench::Node::sendMessage;
auto getMessageNodePtr = &rtl_bench::Node::getMessage;

BENCHMARK(rtl_bench::BenchMark::directCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionMethodCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedCall_noReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_noReturn);

BENCHMARK(rtl_bench::BenchMark::directCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::stdFunctionMethodCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedCall_withReturn);
BENCHMARK(rtl_bench::BenchMark::reflectedMethodCall_withReturn);

BENCHMARK_MAIN();
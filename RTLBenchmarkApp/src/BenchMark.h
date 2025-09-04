#pragma once

#include <benchmark/benchmark.h>

namespace rtl_bench
{
	struct BenchMark
	{
		static void directCall(benchmark::State& state);

		static void lambdaCall(benchmark::State& state);

		static void reflectedCall(benchmark::State& state);

		static void reflectedMethodCall(benchmark::State& state);
	};
}
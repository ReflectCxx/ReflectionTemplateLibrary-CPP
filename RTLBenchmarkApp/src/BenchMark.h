#pragma once

#include <benchmark/benchmark.h>

namespace rtl_bench
{
	struct BenchMark
	{
		static void directCall_noReturn(benchmark::State& state);

		static void lambdaCall_noReturn(benchmark::State& state);

		static void reflectedCall_noReturn(benchmark::State& state);

		static void reflectedMethodCall_noReturn(benchmark::State& state);

		static void directCall_withReturn(benchmark::State& state);

		static void lambdaCall_withReturn(benchmark::State& state);

		static void reflectedCall_withReturn(benchmark::State& state);

		static void reflectedMethodCall_withReturn(benchmark::State& state);
	};
}
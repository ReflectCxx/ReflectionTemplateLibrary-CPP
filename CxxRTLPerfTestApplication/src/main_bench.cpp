
#include <string>
#include <benchmark/benchmark.h>

#include "RTLibInterface.h"


#if defined(_MSC_VER)
#  define NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE
#endif

namespace rtl_bench {
    
    static std::optional<std::string> g_msg;

    NOINLINE void sendMessage(const char* pMsgStr)
    {
        g_msg = pMsgStr;
    }

    const rtl::CxxMirror& cxx_mirror() {
        static rtl::CxxMirror m = rtl::CxxMirror({
            rtl::type().function("sendMessage").build(sendMessage)
        });
        return m;
    }
}

// Direct call vs. Reflected call
// ------------------------------------------------------------
static void DirectCall(benchmark::State& state) 
{
    for (auto _ : state) {
        rtl_bench::sendMessage("direct");
        benchmark::ClobberMemory();
    }
}

static void ReflectedCall(benchmark::State& state)
{
    rtl::Function sendMessage = rtl_bench::cxx_mirror().getFunction("sendMessage").value();
    for (auto _ : state) {;
        sendMessage.bind().call("reflected");
        benchmark::ClobberMemory();
    }
}


// ------------------------------------------------------------
// Register benchmarks
// ------------------------------------------------------------
BENCHMARK(DirectCall);
BENCHMARK(ReflectedCall);

BENCHMARK_MAIN();

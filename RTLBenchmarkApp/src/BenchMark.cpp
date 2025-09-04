
#include <string>
#include <optional>

#include "BenchMark.h"
#include "RTLibInterface.h"

#if defined(_MSC_VER)
#  define NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE
#endif


namespace {

	static std::optional<std::string> g_msg;

	NOINLINE static void sendMesage(const char* pMsg) { g_msg = pMsg; }

	struct Node {
		NOINLINE void sendMesage(const char* pMsg) { g_msg = pMsg; }
	};

	const rtl::CxxMirror& cxx_mirror() 
	{
		static auto m = rtl::CxxMirror({

			rtl::type().record<Node>("node").build(),

			rtl::type().function("sendMessage").build(sendMesage),

			rtl::type().member<Node>().method("sendMessage").build(&Node::sendMesage)
		});
		return m;
	}
}


namespace rtl_bench
{
	void BenchMark::directCall(benchmark::State& state)
	{
		for (auto _ : state) 
		{
			sendMesage("direct");
			benchmark::ClobberMemory();
		}
	}
	
	void BenchMark::lambdaCall(benchmark::State& state)
	{
		std::function sendMsg = [](const char* pMsg) {
			sendMesage(pMsg);
		};

		for (auto _ : state) 
		{
			sendMsg("lambda");
			benchmark::ClobberMemory();
		}
	}

	void BenchMark::reflectedCall(benchmark::State& state)
	{
		rtl::Function sendMsg = cxx_mirror().getFunction("sendMessage").value();
		for (auto _ : state)
		{
			sendMsg.bind().call("reflected");
			benchmark::ClobberMemory();
		}
	}

	void BenchMark::reflectedMethodCall(benchmark::State& state)
	{
		rtl::Record rNode = cxx_mirror().getRecord("node").value();
		rtl::Method sendMsg = rNode.getMethod("sendMessage").value();
		rtl::RObject robj = rNode.create<rtl::alloc::Stack>().second;

		for (auto _ : state)
		{
			sendMsg.bind<const char*>(robj).call("reflected");
			benchmark::ClobberMemory();
		}
	}
}

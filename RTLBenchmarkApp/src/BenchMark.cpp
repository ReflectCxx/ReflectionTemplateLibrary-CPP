
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

	NOINLINE static void sendMessage(const char* pMsg) 
	{ 
		g_msg = pMsg; 
	}

	NOINLINE static std::string getMessage(const char* pMsg) 
	{ 
		g_msg = pMsg;
		return std::string(pMsg); 
	}

	struct Node 
	{
		NOINLINE void sendMessage(const char* pMsg) 
		{ 
			g_msg = pMsg; 
		}

		NOINLINE std::string getMessage(const char* pMsg)
		{ 
			g_msg = pMsg;
			return std::string(pMsg);
		}
	};

	const rtl::CxxMirror& cxx_mirror() 
	{
		static auto m = rtl::CxxMirror({

			rtl::type().record<Node>("node").build(),

			rtl::type().function("sendMessage").build(sendMessage),

			rtl::type().member<Node>().method("sendMessage").build(&Node::sendMessage),

			rtl::type().function("getMessage").build(getMessage),

			rtl::type().member<Node>().method("getMessage").build(&Node::getMessage)
		});
		return m;
	}
}


namespace rtl_bench
{
	void BenchMark::directCall_noReturn(benchmark::State& state)
	{
		for (auto _ : state) 
		{
			sendMessage("direct");
			benchmark::DoNotOptimize(g_msg);
		}
	}
	

	void BenchMark::lambdaCall_noReturn(benchmark::State& state)
	{
		std::function sendMsg = [](const char* pMsg) {
			sendMessage(pMsg);
		};

		for (auto _ : state) 
		{
			sendMsg("lambda");
			benchmark::DoNotOptimize(g_msg);
		}
	}


	void BenchMark::reflectedCall_noReturn(benchmark::State& state)
	{
		rtl::Function sendMsg = cxx_mirror().getFunction("sendMessage").value();
		for (auto _ : state)
		{
			benchmark::DoNotOptimize(sendMsg.bind<const char*>().call("reflected"));
		}
	}


	void BenchMark::reflectedMethodCall_noReturn(benchmark::State& state)
	{
		rtl::Record rNode = cxx_mirror().getRecord("node").value();
		rtl::Method sendMsg = rNode.getMethod("sendMessage").value();
		rtl::RObject robj = rNode.create<rtl::alloc::Stack>().second;

		for (auto _ : state)
		{
			benchmark::DoNotOptimize(sendMsg.bind<const char*>(robj).call("reflected"));
		}
	}


	void BenchMark::directCall_withReturn(benchmark::State& state)
	{
		for (auto _ : state) 
		{
			benchmark::DoNotOptimize(getMessage("direct"));
		}
	}
	

	void BenchMark::lambdaCall_withReturn(benchmark::State& state)
	{
		std::function getMsg = [](const char* pMsg) {
			return getMessage(pMsg);
		};

		for (auto _ : state) 
		{
			benchmark::DoNotOptimize(getMsg("lambda"));
		}
	}


	void BenchMark::reflectedCall_withReturn(benchmark::State& state)
	{
		rtl::Function getMsg = cxx_mirror().getFunction("getMessage").value();
		for (auto _ : state)
		{
			benchmark::DoNotOptimize(getMsg.bind<const char*>().call("reflected"));
		}
	}


	void BenchMark::reflectedMethodCall_withReturn(benchmark::State& state)
	{
		rtl::Record rNode = cxx_mirror().getRecord("node").value();
		rtl::Method getMsg = rNode.getMethod("getMessage").value();
		rtl::RObject robj = rNode.create<rtl::alloc::Stack>().second;

		for (auto _ : state)
		{
			benchmark::DoNotOptimize(getMsg.bind<const char*>(robj).call("reflected"));
		}
	}
}
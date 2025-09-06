
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

static const std::string LONG_STR =
"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

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
			sendMessage(LONG_STR.c_str());
			benchmark::DoNotOptimize(g_msg);
		}
	}
	

	void BenchMark::lambdaCall_noReturn(benchmark::State& state)
	{
		static std::function sendMsg = [](const char* pMsg) {
			sendMessage(pMsg);
		};

		for (auto _ : state) 
		{
			sendMsg(LONG_STR.c_str());
			benchmark::DoNotOptimize(g_msg);
		}
	}


	void BenchMark::reflectedCall_noReturn(benchmark::State& state)
	{
		static rtl::Function sendMsg = cxx_mirror().getFunction("sendMessage").value();
		for (auto _ : state)
		{
			benchmark::DoNotOptimize(sendMsg.bind().call(LONG_STR.c_str()));
		}
	}


	void BenchMark::reflectedMethodCall_noReturn(benchmark::State& state)
	{
		static rtl::Record rNode = cxx_mirror().getRecord("node").value();
		static rtl::Method sendMsg = rNode.getMethod("sendMessage").value();
		static rtl::RObject robj = rNode.create<rtl::alloc::Stack>().rObject;

		for (auto _ : state)
		{
			benchmark::DoNotOptimize(sendMsg.bind(robj).call(LONG_STR.c_str()));
		}
	}


	void BenchMark::directCall_withReturn(benchmark::State& state)
	{
		for (auto _ : state) 
		{
			benchmark::DoNotOptimize(getMessage(LONG_STR.c_str()));
		}
	}
	

	void BenchMark::lambdaCall_withReturn(benchmark::State& state)
	{
		static std::function getMsg = [](const char* pMsg) {
			return getMessage(pMsg);
		};

		for (auto _ : state) 
		{
			benchmark::DoNotOptimize(getMsg(LONG_STR.c_str()));
		}
	}


	void BenchMark::reflectedCall_withReturn(benchmark::State& state)
	{
		static rtl::Function getMsg = cxx_mirror().getFunction("getMessage").value();
		for (auto _ : state)
		{
			benchmark::DoNotOptimize(getMsg.bind().call(LONG_STR.c_str()));
		}
	}


	void BenchMark::reflectedMethodCall_withReturn(benchmark::State& state)
	{
		static rtl::Record rNode = cxx_mirror().getRecord("node").value();
		static rtl::Method getMsg = rNode.getMethod("getMessage").value();
		static rtl::RObject robj = rNode.create<rtl::alloc::Stack>().rObject;

		for (auto _ : state)
		{
			benchmark::DoNotOptimize(getMsg.bind(robj).call(LONG_STR.c_str()));
		}
	}
}
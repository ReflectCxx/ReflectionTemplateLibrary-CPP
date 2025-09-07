#pragma once

#include <benchmark/benchmark.h>

#include "RTLibInterface.h"

#if defined(_MSC_VER)
#  define NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE
#endif

using str_type = /*std::string; //*/ std::string_view;

namespace rtl_bench
{
    static std::optional<std::string> g_msg;

    NOINLINE static void sendMessage(str_type pMsg) {
        std::string result = std::string(pMsg) + std::string(pMsg);
        result = result + result;
        result = result + result;
        g_msg = pMsg;
    }

    NOINLINE static str_type getMessage(str_type pMsg) {
        std::string result = std::string(pMsg) + std::string(pMsg);
        result = result + result;
        result = result + result;
        g_msg = pMsg;
        return str_type(g_msg->c_str());
    }

    struct Node
    {
        NOINLINE void sendMessage(str_type pMsg) {
            std::string result = std::string(pMsg) + std::string(pMsg);
            result = result + result;
            result = result + result;
            g_msg = pMsg;
            g_msg = pMsg;
        }

        NOINLINE str_type getMessage(str_type pMsg) 
        {
            std::string result = std::string(pMsg) + std::string(pMsg);
            result = result + result;
            result = result + result;
            g_msg = pMsg;
            return str_type(g_msg->c_str());
        }
    };


    static const rtl::CxxMirror& cxx_mirror()
    {
        static auto m = rtl::CxxMirror({

            rtl::type().record<Node>("Node").build(),

            rtl::type().function<str_type>("sendMessage").build(sendMessage),

            rtl::type().member<Node>().method("sendMessage").build(&Node::sendMessage),

            rtl::type().function("getMessage").build(getMessage),

            rtl::type().member<Node>().method("getMessage").build(&Node::getMessage)
        });
        return m;
    }


	struct BenchMark
	{
		static void directCall_noReturn(benchmark::State& state);

		static void autoLambdaCall_noReturn(benchmark::State& state);

		static void stdFunctionCall_noReturn(benchmark::State& state);

		static void reflectedCall_noReturn(benchmark::State& state);

		static void reflectedMethodCall_noReturn(benchmark::State& state);

		static void directCall_withReturn(benchmark::State& state);

		static void autoLambdaCall_withReturn(benchmark::State& state);

		static void stdFunctionCall_withReturn(benchmark::State& state);

		static void reflectedCall_withReturn(benchmark::State& state);

		static void reflectedMethodCall_withReturn(benchmark::State& state);
	};
}
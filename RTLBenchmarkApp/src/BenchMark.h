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

using argStr_t = std::string_view;
using retStr_t = std::string_view;

#define WORK_LOAD(S) (std::string(S))


namespace rtl_bench
{
    static std::optional<std::string> g_msg;

    NOINLINE static void sendMessage(argStr_t pMsg) 
    {
        std::string str = WORK_LOAD(pMsg);
        volatile auto* p = &str;
        static_cast<void>(p);
        g_msg = str;
    }

    NOINLINE static retStr_t getMessage(argStr_t pMsg)
    {
        std::string str = WORK_LOAD(pMsg);
        volatile auto* p = &str;
        static_cast<void>(p);
        g_msg = str;
        return retStr_t(g_msg->c_str());
    }

    struct Node
    {
        NOINLINE void sendMessage(argStr_t pMsg) 
        {
            std::string str = WORK_LOAD(pMsg);
            volatile auto* p = &str;
            static_cast<void>(p);
    	    g_msg = str;
        }

        NOINLINE retStr_t getMessage(argStr_t pMsg)
        {
            std::string str = WORK_LOAD(pMsg);
            volatile auto* p = &str;
            static_cast<void>(p);
            g_msg = str;
            return retStr_t(g_msg->c_str());
        }
    };


    static const rtl::CxxMirror& cxx_mirror()
    {
        static auto m = rtl::CxxMirror({

            rtl::type().record<Node>("Node").build(),

            rtl::type().function("sendMessage").build(sendMessage),

            rtl::type().member<Node>().method("sendMessage").build(&Node::sendMessage),

            rtl::type().function("getMessage").build(getMessage),

            rtl::type().member<Node>().method("getMessage").build(&Node::getMessage)
        });
        return m;
    }


	struct BenchMark
	{
        static void directCall_noReturn(benchmark::State& state);

		static void stdFunctionCall_noReturn(benchmark::State& state);

		static void reflectedCall_noReturn(benchmark::State& state);

        static void stdFunctionMethodCall_noReturn(benchmark::State& state);

		static void reflectedMethodCall_noReturn(benchmark::State& state);

		static void directCall_withReturn(benchmark::State& state);

		static void stdFunctionCall_withReturn(benchmark::State& state);

        static void stdFunctionMethodCall_withReturn(benchmark::State& state);

		static void reflectedCall_withReturn(benchmark::State& state);

		static void reflectedMethodCall_withReturn(benchmark::State& state);
    };
}


#include <any>
#include <optional>

#include <iostream>

#include "BenchMark.h"

namespace {

    static const char* LONG_STR = "Lorem ipsum";// dolor sit amet, consectetur adipiscing elit, sed do";
    //"do aeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis"
    //"nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure"
    //"dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Except"
    //"eur ssint occaecat cupidatat nnon proident, sunt in culpa qui officia deserunt mollit anim id";
}

// Pre-created string to isolate call overhead
static argStr_t g_longStr(LONG_STR);

namespace rtl_bench
{
    void BenchMark::directCall_noReturn(benchmark::State& state)
    {
        for (auto _ : state)
        {
            sendMessage(g_longStr);
            benchmark::DoNotOptimize(g_msg);
        }
    }


    void BenchMark::stdFunctionCall_noReturn(benchmark::State& state)
    {
        static std::function sendMsg = [](argStr_t& pMsg) {
            sendMessage(pMsg);
        };

        for (auto _ : state)
        {
            sendMsg(g_longStr);
            benchmark::DoNotOptimize(g_msg);
        }
    }


    void BenchMark::directCall_withReturn(benchmark::State& state)
    {
        static auto _ = []() {
            std::cout << "--------------------------------------------------"
                         "---------------------------------------------" << std::endl;
            return 0; 
        }();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(getMessage(g_longStr));
        }
    }


    void BenchMark::stdFunctionCall_withReturn(benchmark::State& state)
    {
        static std::function getMsg = [](argStr_t& pMsg) {
            return getMessage(pMsg);
        };

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(getMsg(g_longStr));
        }
    }
}


namespace rtl_bench 
{
    void BenchMark::reflectedCall_noReturn(benchmark::State& state)
    {
        static rtl::Function sendMsg = cxx_mirror().getFunction("sendMessage").value();
        static auto _ = []() {
            auto err = sendMsg.bind().call(g_longStr).err;
            if (err != rtl::error::None) {
                std::cout << "[rtl:0] err: "<< rtl::to_string(err)<<"\n";
            }
            return 0;
        }();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(sendMsg.bind().call(g_longStr));
        }
    }


    void BenchMark::reflectedMethodCall_noReturn(benchmark::State& state)
    {
        static rtl::Record rNode = cxx_mirror().getRecord("Node").value();
        static rtl::Method sendMsg = rNode.getMethod("sendMessage").value();
        static rtl::RObject robj = rNode.create<rtl::alloc::Stack>().rObject;
        static auto _ = []() {
            auto err = sendMsg.bind(robj).call(g_longStr).err;
            if (err != rtl::error::None)  {
                std::cout << "[rtl:1] err: " << rtl::to_string(err) << "\n";
            }
            return 0;
        }();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(sendMsg.bind(robj).call(g_longStr));
        }
    }


    void BenchMark::reflectedCall_withReturn(benchmark::State& state)
    {
        static rtl::Function getMsg = cxx_mirror().getFunction("getMessage").value();
        static auto _ = []() {
            auto err = getMsg.bind().call(g_longStr).err;
            if (err != rtl::error::None) {
                std::cout << "[rtl:2] err: " << rtl::to_string(err) << "\n";
            }
            return 0;
        }();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(getMsg.bind().call(g_longStr));
        }
    }


    void BenchMark::reflectedMethodCall_withReturn(benchmark::State& state)
    {
        static rtl::Record rNode = cxx_mirror().getRecord("Node").value();
        static rtl::Method getMsg = rNode.getMethod("getMessage").value();
        static rtl::RObject robj = rNode.create<rtl::alloc::Heap>().rObject;
        static auto _ = []() {
            auto err = getMsg.bind(robj).call(g_longStr).err;
            if (err != rtl::error::None) {
                std::cout << "[rtl:3] err: " << rtl::to_string(err) << "\n";
            }
            return 0;
        }();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(getMsg.bind(robj).call(g_longStr));
        }
    }
}
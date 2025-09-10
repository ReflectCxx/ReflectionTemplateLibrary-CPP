
#include <iostream>
#include <functional>
#include "StandardCall.h"

namespace
{
    static bm::Node node;

    static std::function sendMsg = [](bm::argStr_t& pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        bm::sendMessage(pMsg);
    };

    static std::function sendMsgMethod = [](bm::argStr_t& pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        node.sendMessage(pMsg);
    };

    static std::function getMsg = [](bm::argStr_t& pMsg) 
    {
        {
            volatile auto* p = &pMsg;
            static_cast<void>(p);
        }
        const auto& retMsg = bm::getMessage(pMsg);
        {
            volatile auto* p = &retMsg;
            static_cast<void>(p);
        }
        return retMsg;
    };

    static std::function getMsgMethod = [](bm::argStr_t& pMsg)
    {
        {
            volatile auto* p = &pMsg;
            static_cast<void>(p);
        }
        const auto& retMsg = node.getMessage(pMsg);
        {
            volatile auto* p = &retMsg;
            static_cast<void>(p);
        }
        return retMsg;
    };
}


void DirectCall::noReturn(benchmark::State& state)
{
    for (auto _ : state)
    {
        bm::sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_msg);
    }
}


void DirectCall::withReturn(benchmark::State& state)
{
    static auto _ = []() {
        std::cout << "--------------------------------------"
        "--------------------------------------" << std::endl;
        return 0;
    }();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(bm::getMessage(bm::g_longStr));
    }
}



void StdFunctionCall::noReturn(benchmark::State& state)
{
    for (auto _ : state)
    {
        sendMsg(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_msg);
    }
}


void StdFunctionCall::noReturnMethod(benchmark::State& state)
{
    for (auto _ : state)
    {
        sendMsgMethod(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_msg);
    }
}


void StdFunctionCall::withReturn(benchmark::State& state)
{
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMsg(bm::g_longStr));
    }
}


void StdFunctionCall::withReturnMethod(benchmark::State& state)
{
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMsgMethod(bm::g_longStr));
    }
}
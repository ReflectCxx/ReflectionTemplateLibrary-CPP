
#include <iostream>
#include <functional>
#include "StandardCall.h"

extern std::optional<std::string> g_work_done;

namespace 
{
    static auto _put_line = []() {
        std::cout << "-------------------------------------"
        "-------------------------------------" << std::endl;
        return 0;
    };

    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };
}

namespace
{
    static bm::Node node;

    static std::function SendMessage = [](bm::argStr_t& pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        bm::sendMessage(pMsg);
    };

    static std::function NodeSendMessage = [](bm::argStr_t& pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        node.sendMessage(pMsg);
    };

    static std::function GetMessage = [](bm::argStr_t& pMsg) 
    {
        auto retMsg = bm::getMessage(pMsg);
        volatile auto* p = &retMsg;
        static_cast<void>(p);
        return retMsg;
    };

    static std::function NodeGetMessage = [](bm::argStr_t& pMsg)
    {
        auto retMsg = node.getMessage(pMsg);
        volatile auto* p = &retMsg;
        static_cast<void>(p);
        return retMsg;
    };
}


void DirectCall::noReturn(benchmark::State& state)
{
    for (auto _: state)
    {
        bm::sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(g_work_done->c_str());
    }
}


void DirectCall::withReturn(benchmark::State& state)
{
    static auto _=_put_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::getMessage(bm::g_longStr));
    }
}



void StdFuncCall::noReturn(benchmark::State& state)
{
    for (auto _: state)
    {
        SendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(g_work_done->c_str());
    }
}


void StdFuncMethodCall::noReturn(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        NodeSendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(g_work_done->c_str());
    }
}


void StdFuncCall::withReturn(benchmark::State& state)
{
    for (auto _: state)
    {
        benchmark::DoNotOptimize(GetMessage(bm::g_longStr));
    }
}


void StdFuncMethodCall::withReturn(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(NodeGetMessage(bm::g_longStr));
    }
}

#include <any>
#include <iostream>
#include <optional>
#include <functional>

#include "BenchMark.h"
#include "StandardCall.h"

namespace 
{
    static auto _put_line = []() {
        std::cout << "-----------------------------------------------"
             "-------------------------------------------------------" << std::endl;
        return 0;
    };

    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };
}


namespace bm 
{
    extern void sendMessage(argStr_t);

    extern retStr_t getMessage(argStr_t);

    extern std::optional<std::string> g_work_done;

    extern std::function<void(argStr_t&)> SendMessage;

    extern std::function<void(bm::Node, argStr_t&)> NodeSendMessage;

    extern std::function<retStr_t(argStr_t&)> GetMessage;

    extern std::function<retStr_t(bm::Node, argStr_t&)> NodeGetMessage;
}


void NativeCall::returnVoid(benchmark::State& state)
{
    for (auto _: state)
    {
        bm::sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}


void NativeCall::returnNonVoid(benchmark::State& state)
{
    static auto _=_put_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::getMessage(bm::g_longStr));
    }
}


void StdFunction_call::returnVoid(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        bm::SendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}


void StdFunction_callMethod::returnVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    for (auto _: state)
    {
        bm::NodeSendMessage(nodeObj, bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}


void StdFunction_call::returnNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::GetMessage(bm::g_longStr));
    }
}


void StdFunction_callMethod::returnNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::NodeGetMessage(nodeObj, bm::g_longStr));
    }
}
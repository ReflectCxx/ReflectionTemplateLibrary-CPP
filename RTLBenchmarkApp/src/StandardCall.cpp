
#include <iostream>
#include <optional>
#include <functional>

#include "BenchMark.h"
#include "StandardCall.h"

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


namespace bm 
{
    extern void sendMessage(argStr_t);

    extern retStr_t getMessage(argStr_t);

    extern std::optional<std::string> g_work_done;

    extern std::function<void(argStr_t&)> SendMessage;

    extern std::function<void(argStr_t&)> NodeSendMessage;

    extern std::function<retStr_t(argStr_t&)> GetMessage;

    extern std::function<retStr_t(argStr_t&)> NodeGetMessage;
}


void DirectCall::noReturn(benchmark::State& state)
{
    for (auto _: state)
    {
        bm::sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
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
    static auto _=_new_line();
    for (auto _: state)
    {
        bm::SendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}


void StdFuncMethodCall::noReturn(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        bm::NodeSendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}


void StdFuncCall::withReturn(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::GetMessage(bm::g_longStr));
    }
}


void StdFuncMethodCall::withReturn(benchmark::State& state)
{
    static auto _=_new_line();
    for (auto _: state)
    {
        benchmark::DoNotOptimize(bm::NodeGetMessage(bm::g_longStr));
    }
}
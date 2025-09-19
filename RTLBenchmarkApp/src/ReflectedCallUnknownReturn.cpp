
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>

#include "BenchMark.h"
#include "ReflectedCallUnknownReturn.h"

namespace cxx
{
    extern const rtl::CxxMirror& mirror();
}

namespace
{
    static rtl::Function GetMessage;
    static rtl::Function SendMessage;

    static rtl::Method NodeGetMessage;
    static rtl::Method NodeSendMessage;

    static rtl::RObject nodeObj = []()
    {
        GetMessage = cxx::mirror().getFunction("getMessage").value();

        SendMessage = cxx::mirror().getFunction("sendMessage").value();

        rtl::Record Node = cxx::mirror().getRecord("Node").value();

        NodeGetMessage = Node.getMethod("getMessage").value();

        NodeSendMessage = Node.getMethod("sendMessage").value();

        auto [err, robj] = Node.create<rtl::alloc::Stack>();

        if (robj.isEmpty()) {
            std::cout << "[0] error: " << rtl::to_string(err) << "\n";
        }

        return std::move(robj);
    }();
}


namespace
{
    static auto _test0 = []()
    {
        auto err = SendMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[0] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test1 = []()
    {
        auto err = NodeSendMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[1] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test2 = []()
    {
        auto err = GetMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[2] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[3] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };
}



void ReflectedCallUnknownReturn::set(benchmark::State& state)
{
    static auto _ = _test0();
    for (auto _ : state) 
    {
        auto error = SendMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedCallUnknownReturn::get(benchmark::State& state)
{
    static auto _ = _test2();
    for (auto _ : state)
    {
        auto error = GetMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCallUnknownReturn::set(benchmark::State& state)
{
    static auto _ = _test1();
    for (auto _ : state)
    {
        auto error = NodeSendMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCallUnknownReturn::get(benchmark::State& state)
{
    static auto _ = _test3();
    for (auto _ : state)
    {
        auto error = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}
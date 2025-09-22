
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
    static rtl::Function GetMessage = []()
    {
        return *(cxx::mirror().getFunction("getMessage"));
    }();

    static rtl::Function SendMessage = []()
    {
        return *(cxx::mirror().getFunction("sendMessage"));
    }();

    static rtl::Method NodeGetMessage = []()
    {
        return *(cxx::mirror().getRecord("Node")->getMethod("getMessage"));
    }();

    static rtl::Method NodeSendMessage = []()
    {
        return *(cxx::mirror().getRecord("Node")->getMethod("sendMessage"));
    }();

    static const rtl::RObject nodeObj = []()
    {
        auto [err, robj] = cxx::mirror().getRecord("Node")->create<rtl::alloc::Stack>();
        if (robj.isEmpty()) {
            std::cout << "[x] error: " << rtl::to_string(err) << "\n";
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

    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };
}



void ReflectedCallUnknownReturn::typeVoid(benchmark::State& state)
{
    static auto __=_new_line();
    static auto _ = _test0();
    for (auto _ : state) 
    {
        benchmark::DoNotOptimize(SendMessage(bm::g_longStr));
    }
}


void ReflectedCallUnknownReturn::typeNonVoid(benchmark::State& state)
{
    static auto __=_new_line();
    static auto _ = _test2();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(GetMessage(bm::g_longStr));
    }
}


void ReflectedMethodCallUnknownReturn::typeVoid(benchmark::State& state)
{
    static auto _ = _test1();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(NodeSendMessage(nodeObj)(bm::g_longStr));
    }
}


void ReflectedMethodCallUnknownReturn::typeNonVoid(benchmark::State& state)
{
    static auto _ = _test3();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(NodeGetMessage(nodeObj)(bm::g_longStr));
    }
}
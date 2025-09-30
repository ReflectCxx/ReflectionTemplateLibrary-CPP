
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>

#include "BenchMark.h"
#include "ReflectedCallUnknownReturn.h"

namespace bm
{
    extern std::optional<std::string> g_work_done;
}

namespace cxx
{
    extern const rtl::CxxMirror& mirror();
}

namespace
{
    static rtl::Function GetMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("getMessage");
        if (!function) {
            std::cerr << "[0] error: erase_function 'getMessage' not found.\n";
            std::abort();
        }
        return *function;
    }();

    static rtl::Function SendMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("sendMessage");
        if (!function) {
            std::cerr << "[1] error: erase_function 'sendMessage' not found.\n";
            std::abort();
        }
        return *function;
    }();

    static rtl::Method NodeGetMessage = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\n";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("getMessage");
        if (!method) {
            std::cerr << "[2] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return *method;
    }();

    static rtl::Method NodeSendMessage = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\n";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("sendMessage");
        if (!method) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        return *method;
    }();

    // static const rtl::RObject nodeObj = []()
    // {
    //     std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
    //     if (!Node) {
    //         std::cerr << "[x] error: record 'Node' not found.\n";
    //         std::abort();
    //     }

    //     auto [err, robj] = Node->create<rtl::alloc::Stack>();
    //     if (robj.isEmpty()) {
    //         std::cout << "[x] error: " << rtl::to_string(err) << "\n";
    //     }
    //     return std::move(robj);
    // }();
}


namespace
{
    static auto _test0 = []()
    {
        auto err = SendMessage()(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[00] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test1 = []()
    {
        auto err = NodeSendMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[01] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test2 = []()
    {
        auto err = GetMessage()(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[02] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = NodeGetMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[03] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };
}



void RtlFunction_call_ReturnUnknown::typeVoid(benchmark::State& state)
{
    static auto __= _new_line();
    static auto _ = _test0();
    for (auto _ : state) 
    {
        benchmark::DoNotOptimize(SendMessage()(bm::g_longStr));
    }
}


void RtlFunction_call_ReturnUnknown::typeNonVoid(benchmark::State& state)
{
    static auto __= _new_line();
    static auto _ = _test2();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(GetMessage()(bm::g_longStr));
    }
}


void RtlFunction_callMethod_ReturnUnknown::typeVoid(benchmark::State& state)
{
    static auto _ = _test1();
    static bm::Node node;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(NodeSendMessage(node)(bm::g_longStr));
    }
}


void RtlFunction_callMethod_ReturnUnknown::typeNonVoid(benchmark::State& state)
{
    static auto _ = _test3();
    static bm::Node node;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(NodeGetMessage(node)(bm::g_longStr));
    }
}
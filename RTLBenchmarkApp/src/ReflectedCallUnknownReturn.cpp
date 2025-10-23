
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
    static rtl::Record class_Node = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\n";
            std::abort();
        }
        return Node.value();
    }();

    static const rtl::RObject nodeObj = []()
    {
        auto [err, robj] = class_Node.create<rtl::alloc::Stack>();
        if (robj.isEmpty()) {
            std::cerr << "[x] error: " << rtl::to_string(err) << "\n";
        }
        return std::move(robj);
    }();
}

namespace
{
    static rtl::function<rtl::Return(bm::argStr_t)> ErasedReturnFn_GetMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("getMessage");
        if (!function) {
            std::cerr << "[0] error: erase_function 'getMessage' not found.\n";
            std::abort();
        }
        return function->argsT<bm::argStr_t>().returnT();
    }();

    static rtl::function<rtl::Return(bm::argStr_t)> ErasedReturnFn_SendMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("sendMessage");
        if (!function) {
            std::cerr << "[1] error: erase_function 'sendMessage' not found.\n";
            std::abort();
        }
        return function->argsT<bm::argStr_t>().returnT();
    }();
}

namespace
{
    static rtl::Method ErasedTargetGetMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("getMessage");
        if (!method) {
            std::cerr << "[2] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return *method;
    }();

    static rtl::Method ErasedTargetSendMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("sendMessage");
        if (!method) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        return *method;
    }();

    //----------------------------------------------------------------------------
    static rtl::method<bm::Node, rtl::Return(bm::argStr_t)> ErasedReturnNode_SendMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("sendMessage");
        if (!method) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        return method->targetT<bm::Node>().argsT<bm::argStr_t>().returnT<>();
    }();

    //----------------------------------------------------------------------------
    static rtl::method<bm::Node, rtl::Return(bm::argStr_t)> ErasedReturn_GetMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("getMessage");
        if (!method) {
            std::cerr << "[2] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return method->targetT<bm::Node>().argsT<bm::argStr_t>().returnT<>();
    }();

    static rtl::method<rtl::RObject, bm::retStr_t(bm::argStr_t)> ErasedTarget_GetMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("getMessage");
        if (!method) {
            std::cerr << "[2] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return method->targetT<>().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
    }();

    static rtl::method<rtl::RObject, rtl::Return(bm::argStr_t)> ErasedReturnAndTarget_GetMessage = []()
    {
        std::optional<rtl::Method> method = class_Node.getMethod("getMessage");
        if (!method) {
            std::cerr << "[2] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return method->targetT<>().argsT<bm::argStr_t>().returnT<>();
    }();
}

namespace
{
    static auto _test0 = []()
    {
        auto err = ErasedReturnFn_SendMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[00] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test1 = []()
    {
        auto err = ErasedReturnNode_SendMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[01] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test2 = []()
    {
        auto err = ErasedReturnFn_GetMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[02] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = ErasedReturn_GetMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[03] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test4 = []()
    {
        auto err = ErasedTargetSendMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[01] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test5 = []()
    {
        //{
        //    auto [err, retOpt] = ErasedReturnAndTarget_GetMessage(rtl::RObject())(bm::g_longStr);
        //}

        auto err = ErasedTargetGetMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[03] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _new_line = []() {
        std::cerr << std::endl;
        return 0;
    };
}



void RtlErasedReturnType_call::returnVoid(benchmark::State& state)
{
    static auto __= _new_line();
    static auto _ = _test0();
    for (auto _ : state) 
    {
        benchmark::DoNotOptimize(ErasedReturnFn_SendMessage(bm::g_longStr).err);
    }
}


void RtlErasedReturnType_call::returnNonVoid(benchmark::State& state)
{
    static auto __= _new_line();
    static auto _ = _test2();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ErasedReturnFn_GetMessage(bm::g_longStr).err);
    }
}


void RtlErasedReturnType_callMethod::returnVoid(benchmark::State& state)
{
    static auto _ = _test1();
    static bm::Node node;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ErasedReturnNode_SendMessage(node)(bm::g_longStr).err);
    }
}


void RtlErasedReturnType_callMethod::returnNonVoid(benchmark::State& state)
{
    static auto _ = _test3();
    static bm::Node node;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ErasedReturn_GetMessage(node)(bm::g_longStr).err);
    }
}


void RtlErasedReturnType_callMethod::unknownTarget_returnVoid(benchmark::State& state)
{
    static auto _ = _test4();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ErasedTargetSendMessage(nodeObj)(bm::g_longStr).err);
    }
}


void RtlErasedReturnType_callMethod::unknownTarget_returnNonVoid(benchmark::State& state)
{
    static auto _ = _test5();
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ErasedTargetGetMessage(nodeObj)(bm::g_longStr).err);
    }
}
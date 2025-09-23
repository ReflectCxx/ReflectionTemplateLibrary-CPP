
#include <optional>
#include <rtl/rtl.h>
#include <benchmark/benchmark.h>

#include "BenchMark.h"
#include "Function.h"
#include "ReflectedCallKnownReturn.h"


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
    static const rtl::function<bm::retStr_t(bm::argStr_t)> getMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("getMessage");
        if(!function)
        {
            std::cerr << "[00] error: function 'getMessage' not found.";
            std::abort();
        }
        return function->lambda().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
    }();

    static const rtl::function<void(bm::argStr_t)> sendMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("sendMessage");
        if(!function)
        {
            std::cerr << "[01] error: function 'sendMessage' not found.";
            std::abort();
        }
        return function->lambda().argsT<bm::argStr_t>().returnT<void>();
    }();

    static const rtl::method<bm::retStr_t(bm::Node::*)(bm::argStr_t)> getMessageNode = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("getMessage");
        if (!method) {
            std::cerr << "[02] error: method 'Node::getMessage' not found.";
            std::abort();
        }
        return method->lambda<bm::Node>().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
    }();

    static const rtl::method<void(bm::Node::*)(bm::argStr_t)> sendMessageNode = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("sendMessage");
        if (!method) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.";
            std::abort();
        }
        return method->lambda<bm::Node>().argsT<bm::argStr_t>().returnT<void>();
    }();
}


namespace
{
    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };

    template<class T>
    static bool test(const T& lambda, int callerId) 
    {
        if (!lambda.is_valid()) {
            std::cerr << "[" << callerId << "] error: functor not valid, return-type or signature mismatch.";
            std::abort();
        }
        return true;
    }
}


void NativeFunctionPtr_call::returnNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto is_ok = test(getMessage, 0);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((getMessage.f_ptr())(bm::g_longStr));
    }
}

void NativeFunctionPtr_callMethod::returnNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 1);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((nodeObj.*getMessageNode.f_ptr())(bm::g_longStr));
    }
}

void NativeFunctionPtr_call::returnVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage, 2);
    for (auto _ : state)
    {
        (sendMessage.f_ptr())(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void NativeFunctionPtr_callMethod::returnVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 2);
    for (auto _ : state)
    {
        if (sendMessageNode.is_valid())
        {
            (nodeObj.*sendMessageNode.f_ptr())(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}



void RtlFunction_call::returnNonVoid(benchmark::State &state)
{
    static auto _ = _new_line();
    static auto is_ok = test(getMessage, 3);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessage(bm::g_longStr));
    }
}

void RtlFunction_callMethod::returnNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 4);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessageNode(nodeObj, bm::g_longStr));
    }
}

void RtlFunction_call::returnVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage, 0);
    for (auto _ : state)
    {
        sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void RtlFunction_callMethod::returnVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(sendMessageNode, 5);
    for (auto _ : state)
    {
        sendMessageNode(nodeObj, bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

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
    static const auto getMessage_functor = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("getMessage");
        if(!function)
        {
            std::cerr << "[00] error: function 'getMessage' not found.\n";
            std::abort();
        }
        return function->args_t<bm::argStr_t>().return_t<bm::retStr_t>();
    }();

    static const auto sendMessage_functor = []()
    {
        std::optional<rtl::Function> sendMessage = cxx::mirror().getFunction("sendMessage");
        if(!sendMessage)
        {
            std::cerr << "[01] error: function 'sendMessage' not found.\n";
            std::abort();
        }
        return sendMessage->args_t<bm::argStr_t>().return_t<void>();
    }();

    static const auto getMessageOnNode_functor = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\n";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("getMessage");
        if (!method) {
            std::cerr << "[02] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        return method->args_t<bm::Node, bm::argStr_t>().return_t<bm::retStr_t>();
    }();

    static const auto sendMessageOnNode_functor = []()
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
        return method->args_t<bm::Node, bm::argStr_t>().return_t<void>();
    }();
}


namespace
{
    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };

    template<class T>
    static bool test(const T& functor, int n) 
    {
        if (!functor.is_valid()) {
            std::cerr << "[" << n << "] error: functor not valid, return-type or signature mismatch.\n";
            std::abort();
        }
        return true;
    }
}


void FunctionPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto is_ok = test(getMessage_functor, 0);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((getMessage_functor.f_ptr())(bm::g_longStr));
    }
}

void MethodFnPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageOnNode_functor, 1);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((nodeObj.*getMessageOnNode_functor.f_ptr())(bm::g_longStr));
    }
}

void FunctionPointerCall::returnTypeVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage_functor, 2);
    for (auto _ : state)
    {
        (sendMessage_functor.f_ptr())(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void MethodFnPointerCall::returnTypeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageOnNode_functor, 2);
    for (auto _ : state)
    {
        if (sendMessageOnNode_functor.is_valid())
        {
            (nodeObj.*sendMessageOnNode_functor.f_ptr())(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}



void ReflectedCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(getMessage_functor, 3);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessage_functor(bm::g_longStr));
    }
}

void ReflectedMethodCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageOnNode_functor, 4);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessageOnNode_functor(nodeObj, bm::g_longStr));
    }
}

void ReflectedCallKnownReturn::typeVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage_functor, 0);
    for (auto _ : state)
    {
        sendMessage_functor(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void ReflectedMethodCallKnownReturn::typeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(sendMessageOnNode_functor, 5);
    for (auto _ : state)
    {
        sendMessageOnNode_functor(nodeObj, bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}
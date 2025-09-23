
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
            std::cerr << "[00] error: function 'getMessage' not found.\callerId";
            std::abort();
        }
        return function->getLambda().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
    }();

    static const rtl::function<void(bm::argStr_t)> sendMessage = []()
    {
        std::optional<rtl::Function> function = cxx::mirror().getFunction("sendMessage");
        if(!function)
        {
            std::cerr << "[01] error: function 'sendMessage' not found.\callerId";
            std::abort();
        }
        return function->getLambda().argsT<bm::argStr_t>().returnT<void>();
    }();

    static const rtl::method<bm::retStr_t(bm::Node::*)(bm::argStr_t)> getMessageNode = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\callerId";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("getMessage");
        if (!method) {
            std::cerr << "[02] error: method 'Node::getMessage' not found.\callerId";
            std::abort();
        }
        return method->getLambda<bm::Node>().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
    }();

    static const rtl::method<void(bm::Node::*)(bm::argStr_t)> sendMessageOnNode = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\callerId";
            std::abort();
        }

        std::optional<rtl::Method> method = Node->getMethod("sendMessage");
        if (!method) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.\callerId";
            std::abort();
        }
        return method->getLambda<bm::Node>().argsT<bm::argStr_t>().returnT<void>();
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
            std::cerr << "[" << callerId << "] error: functor not valid, return-type or signature mismatch.\callerId";
            std::abort();
        }
        return true;
    }
}


void FunctionPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto is_ok = test(getMessage, 0);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((getMessage.f_ptr())(bm::g_longStr));
    }
}

void MethodFnPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 1);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((nodeObj.*getMessageNode.f_ptr())(bm::g_longStr));
    }
}

void FunctionPointerCall::returnTypeVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage, 2);
    for (auto _ : state)
    {
        (sendMessage.f_ptr())(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void MethodFnPointerCall::returnTypeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 2);
    for (auto _ : state)
    {
        if (sendMessageOnNode.is_valid())
        {
            (nodeObj.*sendMessageOnNode.f_ptr())(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}



void ReflectedCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(getMessage, 3);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessage(bm::g_longStr));
    }
}

void ReflectedMethodCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(getMessageNode, 4);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessageNode(nodeObj, bm::g_longStr));
    }
}

void ReflectedCallKnownReturn::typeVoid(benchmark::State& state)
{
    static auto _ = _new_line();
    static auto is_ok = test(sendMessage, 0);
    for (auto _ : state)
    {
        sendMessage(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void ReflectedMethodCallKnownReturn::typeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto is_ok = test(sendMessageOnNode, 5);
    for (auto _ : state)
    {
        sendMessageOnNode(nodeObj, bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}
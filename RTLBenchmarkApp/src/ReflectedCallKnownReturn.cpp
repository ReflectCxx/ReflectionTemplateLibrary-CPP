
#include <rtl/rtl.h>
#include <benchmark/benchmark.h>

#include "BenchMark.h"
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
    static const rtl::lambda_function<bm::argStr_t>& getMessage_lambda = []()
    {
        auto lambda_ptr = cxx::mirror().getFunction("getMessage")->get_lambda<bm::argStr_t>();
        if(!lambda_ptr) {
            std::cerr << "[0] error: return-type mismatch.\n";
            std::abort();
        }
        return *lambda_ptr;
    }();

    static const rtl::lambda_function<bm::argStr_t>& sendMessage_lambda = []()
    {
        auto lambda_ptr = cxx::mirror().getFunction("sendMessage")->get_lambda<bm::argStr_t>();
        if(!lambda_ptr) {
            std::cerr << "[1] error: return-type mismatch.\n";
            std::abort();
        }
        return *lambda_ptr;

    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& getMessageOnNode_lambda = []()
    {
        auto lambda_ptr = cxx::mirror().getRecord("Node")->getMethod("getMessage")->get_lambda<bm::Node, bm::argStr_t>();
        if(!lambda_ptr) {
            std::cerr << "[2] error: return-type mismatch.\n";
            std::abort();
        }
        return *lambda_ptr;
    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& sendMessageOnNode_lambda = []()
    {
        auto lambda_ptr = cxx::mirror().getRecord("Node")->getMethod("sendMessage")->get_lambda<bm::Node, bm::argStr_t>();
        if(!lambda_ptr) {
            std::cerr << "[3] error: return-type mismatch.\n";
            std::abort();
        }
        return *lambda_ptr;
    }();
}


namespace
{
    static auto functor_set = [](int n) 
    {
        if(!sendMessage_lambda.is_returning<void>()) {
            std::cerr << "[0"<< n <<"] error: return-type mismatch.\n";
            std::abort();
        }
        // 'get_functor<return_t>': No validation is performed internally and this function
        //                          will not return nullptr on return_t mismatch. (by design).
        return sendMessage_lambda.get_functor<void>().f_ptr();
    };

    static auto method_set = [](int n)
    {
        if(!sendMessageOnNode_lambda.is_returning<void>()) {
            std::cerr << "[1"<< n <<"] error: return-type mismatch.\n";
            std::abort();
        }
        // 'get_functor<return_t>': No validation is performed internally and this function
        //                          will not return nullptr on return_t mismatch. (by design).
        return sendMessageOnNode_lambda.get_functor<void>().f_ptr();
    };

    static auto functor_get = [](int n)
    {
        if (!getMessage_lambda.is_returning<bm::retStr_t>()) {
            std::cerr << "[2"<< n <<"] error: return-type mismatch.\n";
            std::abort();
        }
        // 'get_functor<return_t>': No validation is performed internally and this function
        //                          will not return nullptr on return_t mismatch. (by design).
        return getMessage_lambda.get_functor<bm::retStr_t>().f_ptr();
    };

    static auto method_get = [](int n)
    {
        if (!getMessageOnNode_lambda.is_returning<bm::retStr_t>())
        {
            std::cerr << "[3"<< n <<"] error: return-type mismatch.\n";
            std::abort();
        }
        // 'get_functor<return_t>': No validation is performed internally and this function
        //                          will not return nullptr on return_t mismatch. (by design).
        return getMessageOnNode_lambda.get_functor<bm::retStr_t>().f_ptr();
    };

    static auto _new_line = []() {
        std::cout << std::endl;
        return 0;
    };
}



void FunctionPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto functor = functor_get(0);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((*functor)(bm::g_longStr));
    }
}

void MethodFnPointerCall::returnTypeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto functor = method_get(0);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize((nodeObj.*functor)(bm::g_longStr));
    }
}

void FunctionPointerCall::returnTypeVoid(benchmark::State& state)
{
    static auto __=_new_line();
    static auto _ = functor_set(0);
    static auto functor = sendMessage_lambda.get_functor<void>().f_ptr();
    for (auto _ : state)
    {
        (*functor)(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void MethodFnPointerCall::returnTypeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto functor = method_set(0);
    for (auto _ : state)
    {
        (nodeObj.*functor)(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}



void ReflectedCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto _test = functor_get(1);
    for (auto _: state)
    {
        benchmark::DoNotOptimize(getMessage_lambda.hop<bm::retStr_t>(bm::g_longStr));
    }
}

void ReflectedMethodCallKnownReturn::typeNonVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto _test = method_get(1);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMessageOnNode_lambda.hop<bm::retStr_t>(nodeObj, bm::g_longStr));
    }
}

void ReflectedCallKnownReturn::typeVoid(benchmark::State& state)
{
    static auto _=_new_line();
    static auto _test = functor_set(1);
    for (auto _ : state)
    {
        sendMessage_lambda.hop<void>(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}

void ReflectedMethodCallKnownReturn::typeVoid(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto _test = method_set(1);
    for (auto _ : state)
    {
        sendMessageOnNode_lambda.hop<void>(nodeObj, bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
    }
}
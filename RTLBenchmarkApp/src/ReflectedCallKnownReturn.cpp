
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>
//#include <rtl/dispatch/lambda_hop_method.hpp>
#include <rtl/dispatch/lambda_hop_function.hpp>

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
        return *(cxx::mirror().getFunction("getMessage")->lambda_hop<bm::argStr_t>());
    }();

    static const rtl::lambda_function<bm::argStr_t>& sendMessage_lambda = []()
    {
        return *(cxx::mirror().getFunction("sendMessage")->lambda_hop<bm::argStr_t>());
    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& getMessageOnNode_lambda = []()
    {
        return *(cxx::mirror().getRecord("Node")->getMethod("getMessage")->lambda_hop<bm::Node, bm::argStr_t>());
    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& sendMessageOnNode_lambda = []()
    {
        rtl::Record Node = cxx::mirror().getRecord("Node").value();
        return *(cxx::mirror().getRecord("Node")->getMethod("sendMessage")->lambda_hop<bm::Node, bm::argStr_t>());
    }();

    static const rtl::RObject nodeObj = []()
    {
        auto [err, robj] = cxx::mirror().getRecord("Node")->create<rtl::alloc::Stack>();
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
        if(!sendMessage_lambda.is_signature<bm::argStr_t>() || 
           !sendMessage_lambda.is_returning<void>())
        {
            std::cout << "[0] error: signature mismatch.\n";
            return false;
        }
        return true;
    };


    //static auto _test1 = []()
    //{
    //    if (sendMessageOnNode_lambda == nullptr)
    //    {
    //        std::cout << "[1] error: signature mismatch.\n";
    //        return false;
    //    }
    //    return true;
    //};


    static auto _test2 = []()
    {
        if (!getMessage_lambda.is_signature<bm::argStr_t>() ||
            !getMessage_lambda.is_returning<bm::retStr_t>())
        {
            std::cout << "[0] error: signature mismatch.\n";
            return false;
        }
        return true;
    };

    //static auto _test3 = []()
    //{
    //    if (getMessageOnNode_lambda == nullptr)
    //    {
    //        std::cout << "[3] error: signature mismatch.\n";
    //        return false;
    //    }
    //    return true;
    //};
}


void FunctionPointerCall::set(benchmark::State& state)
{
    static auto passed = _test0();

    // Unchecked: Passing an incorrect signature or return type is undefined behaviour.
    // No validation is performed and the function will not return nullptr on mismatch.
    static auto functor = sendMessage_lambda.get_functor().template args_t<bm::argStr_t>()
                                                          .template return_t<bm::retStr_t>();
    for (auto _ : state)
    {
        if (passed)
        {
            (*functor)(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}



void ReflectedCallKnownReturn::set(benchmark::State& state)
{
    static auto passed = _test0();
    for (auto _ : state)
    {
        if (passed)
        {
            sendMessage_lambda.dispatch<void>(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}


void ReflectedCallKnownReturn::get(benchmark::State& state)
{
    static auto passed = _test2();
    for (auto _: state)
    {
        if (passed)
        {
            auto retStr = getMessage_lambda.dispatch<bm::retStr_t>(bm::g_longStr);
            benchmark::DoNotOptimize(retStr);
        }
    }
}


void ReflectedMethodCallKnownReturn::set(benchmark::State& state)
{
    //static auto _=_test1();
    //for (auto _: state)
    //{
    //    auto error = (NodeSendMessage(nodeObj)(bm::g_longStr).err;
    //    benchmark::DoNotOptimize(error);
    //}
}


void ReflectedMethodCallKnownReturn::get(benchmark::State& state)
{
    //static auto _=_test3();
    //for (auto _: state)
    //{
    //    auto error = NodeGetMessage(nodeObj)(bm::g_longStr).err;
    //    benchmark::DoNotOptimize(error);
    //}
}
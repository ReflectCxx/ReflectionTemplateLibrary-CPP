
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>
#include <rtl/dispatch/lambda_function.hpp>

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
    static const rtl::dispatch::lambda<bm::argStr_t>* GetMessage_lambda = nullptr;

    static const rtl::dispatch::lambda<bm::argStr_t>* SendMessage_lambda = nullptr;

    static const rtl::dispatch::lambda<bm::argStr_t>* NodeGetMessage_lambda = nullptr;

    static const rtl::dispatch::lambda<bm::argStr_t>* NodeSendMessage_lambda = nullptr;

    static const rtl::RObject nodeObj = []()
    {
        rtl::Record Node = cxx::mirror().getRecord("Node").value();

        rtl::Method getMsgNode = Node.getMethod("getMessage").value();

        rtl::Method sendMsgNode = Node.getMethod("sendMessage").value();

        rtl::Function getMsg = cxx::mirror().getFunction("getMessage").value();

        rtl::Function sendMsg = cxx::mirror().getFunction("sendMessage").value();

        GetMessage_lambda = getMsg.getOverloads()[0].get_lambda_function<bm::argStr_t>();

        SendMessage_lambda = sendMsg.getOverloads()[0].get_lambda_function<bm::argStr_t>();

        NodeGetMessage_lambda = getMsgNode.getOverloads()[0].get_lambda_function<bm::argStr_t>();

        NodeSendMessage_lambda = sendMsgNode.getOverloads()[0].get_lambda_function<bm::argStr_t>();

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
        if( SendMessage_lambda == nullptr || 
           !SendMessage_lambda->is_returning<void>() ||
           !SendMessage_lambda->is_signature<bm::argStr_t>())
        {
            std::cout << "[0] error: signature mismatch.\n";
            return false;
        }
        return true;
    };


    static auto _test1 = []()
    {
        if (NodeSendMessage_lambda == nullptr)
        {
            std::cout << "[1] error: signature mismatch.\n";
            return false;
        }
        return true;
    };


    static auto _test2 = []()
    {
        if ( GetMessage_lambda == nullptr ||
            !GetMessage_lambda->is_returning<bm::retStr_t>() ||
            !GetMessage_lambda->is_signature<bm::argStr_t>())
        {
            std::cout << "[0] error: signature mismatch.\n";
            return false;
        }
        return true;
    };

    static auto _test3 = []()
    {
        if (NodeGetMessage_lambda == nullptr)
        {
            std::cout << "[3] error: signature mismatch.\n";
            return false;
        }
        return true;
    };
}



void ReflectedCallKnownReturn::set(benchmark::State& state)
{
    static auto passed = _test0();
    for (auto _ : state)
    {
        //if (passed)
        {
            (*SendMessage_lambda).dispatch<void>(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}


void ReflectedCallKnownReturn::get(benchmark::State& state)
{
    static auto passed = _test2();
    for (auto _: state)
    {
        //if (passed)
        {
            auto retStr = (*GetMessage_lambda).dispatch<bm::retStr_t>(bm::g_longStr);
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
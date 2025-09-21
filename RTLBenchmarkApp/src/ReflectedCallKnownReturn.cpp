
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>

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
        // No validation is performed internally and lambda_hop<signature_ts...>
        // will not return nullptr on signature mismatch. (by design)
        return *(cxx::mirror().getFunction("getMessage")->lambda_hop<bm::argStr_t>());
    }();

    static const rtl::lambda_function<bm::argStr_t>& sendMessage_lambda = []()
    {
        // No validation is performed internally and lambda_hop<signature_ts...>
        // will not return nullptr on signature mismatch. (by design)
        return *(cxx::mirror().getFunction("sendMessage")->lambda_hop<bm::argStr_t>());
    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& getMessageOnNode_lambda = []()
    {
        // No validation is performed internally and lambda_hop<signature_ts...>
        // will not return nullptr on signature mismatch. (by design)
        return *(cxx::mirror().getRecord("Node")->getMethod("getMessage")->lambda_hop<bm::Node, bm::argStr_t>());
    }();

    static const rtl::lambda_method<bm::Node, bm::argStr_t>& sendMessageOnNode_lambda = []()
    {
        rtl::Record Node = cxx::mirror().getRecord("Node").value();
        // No validation is performed internally and lambda_hop<signature_ts...>
        // will not return nullptr on signature mismatch. (by design)
        return *(cxx::mirror().getRecord("Node")->getMethod("sendMessage")->lambda_hop<bm::Node, bm::argStr_t>());
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

    static auto _test1 = []()
    {
       if(!sendMessageOnNode_lambda.is_signature<bm::argStr_t>() || 
          !sendMessageOnNode_lambda.is_returning<void>())
       {
           std::cout << "[1] error: signature mismatch.\n";
           return false;
       }
       return true;
    };

    static auto _test2 = []()
    {
        if (!getMessage_lambda.is_signature<bm::argStr_t>() ||
            !getMessage_lambda.is_returning<bm::retStr_t>())
        {
            std::cout << "[2] error: signature mismatch.\n";
            return false;
        }
        return true;
    };

    static auto _test3 = []()
    {
        if (!getMessageOnNode_lambda.is_signature<bm::argStr_t>() ||
            !getMessageOnNode_lambda.is_returning<bm::retStr_t>())
        {
           std::cout << "[3] error: signature mismatch.\n";
           return false;
        }
       return true;
    };
}


void FunctionPointerCall::set(benchmark::State& state)
{
    static auto* functor = []() -> void(*)(bm::argStr_t) 
    {   
        // Must be checked: Passing an incorrect argument or return type is undefined behaviour.
        if (sendMessage_lambda.is_returning<void>() && sendMessage_lambda.is_signature<bm::argStr_t>())
        {
            // No validation is performed internally and the function will not return nullptr on mismatch.
            return sendMessage_lambda.get_functor<void>().f_ptr();
        }
        std::cout << "[4] error: signature mismatch.\n";
        return nullptr;
    }();

    for (auto _ : state)
    {
        if (functor)
        {
            (*functor)(bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}


void FunctionPointerCall::get(benchmark::State& state)
{
    static auto* functor = []() -> bm::retStr_t(*)(bm::argStr_t)
    {
        // Must be checked: Passing an incorrect argument or return type is undefined behaviour.
        if (getMessage_lambda.is_returning<bm::retStr_t>() && getMessage_lambda.is_signature<bm::argStr_t>())
        {
            // No validation is performed internally and the function will not return nullptr on mismatch.
            return getMessage_lambda.get_functor<bm::retStr_t>().f_ptr();
        }
        std::cout << "[5] error: signature mismatch.\n";
        return nullptr;
    }();

    for (auto _ : state)
    {
        if (functor)
        {
            auto ret = (*functor)(bm::g_longStr);
            benchmark::DoNotOptimize(ret);
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
    static bm::Node nodeObj;
    static auto functor = []() -> void(bm::Node::*)(bm::argStr_t) 
    {
        // Must be checked: Passing an incorrect argument or return type is undefined behaviour.
        if (sendMessageOnNode_lambda.is_returning<void>() && sendMessageOnNode_lambda.is_signature<bm::argStr_t>())
        {
            // No validation is performed internally and the function will not return nullptr on mismatch.
            return sendMessageOnNode_lambda.get_functor<void>().f_ptr();
        }
        std::cout << "[6] error: signature mismatch.\n";
        return nullptr;
    }();
    
    for (auto _ : state)
    {
        if (functor)
        {
            sendMessageOnNode_lambda.dispatch<void>(nodeObj, bm::g_longStr);
            benchmark::DoNotOptimize(bm::g_work_done->c_str());
        }
    }
}


void ReflectedMethodCallKnownReturn::get(benchmark::State& state)
{
    static bm::Node nodeObj;
    static auto functor = []() -> bm::retStr_t(bm::Node::*)(bm::argStr_t) 
    {
        // Must be checked: Passing an incorrect argument or return type is undefined behaviour.
        if (getMessageOnNode_lambda.is_returning<bm::retStr_t>() && getMessageOnNode_lambda.is_signature<bm::argStr_t>())
        {
            // No validation is performed internally and the function will not return nullptr on mismatch.
            return getMessageOnNode_lambda.get_functor<bm::retStr_t>().f_ptr();
        }
        std::cout << "[7] error: signature mismatch.\n";
        return nullptr;
    }();
    
    for (auto _ : state)
    {
        if (functor)
        {
            auto retStr = getMessageOnNode_lambda.dispatch<bm::retStr_t>(nodeObj, bm::g_longStr);
            benchmark::DoNotOptimize(retStr);
        }
    }
}
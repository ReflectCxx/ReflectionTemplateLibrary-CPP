
#include <benchmark/benchmark.h>

#include "ReflectedCall.h"
#include "RTLibInterface.h"
#include "BenchMark.h"

namespace cxx 
{
    extern const rtl::CxxMirror& mirror();
}

namespace
{
    static rtl::Function GetMessage = cxx::mirror().getFunction("getMessage").value();
    static rtl::Function SendMessage = cxx::mirror().getFunction("sendMessage").value();

    static rtl::Method NodeGetMessage = cxx::mirror().getRecord("Node")->getMethod("getMessage").value();
    static rtl::Method NodeSendMessage = cxx::mirror().getRecord("Node")->getMethod("sendMessage").value();
    
    static rtl::RObject nodeObj = []() 
    {    
        auto Node = cxx::mirror().getRecord("Node").value();
        auto [err, robj] = Node.create<rtl::alloc::Stack>();
        if (robj.isEmpty()) {
            std::cout << "[0] nodeObj empty! \n";
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
            std::cout << "[1] error: "<< rtl::to_string(err)<<"\n";
        }
        return 0;
    };

    static auto _test1 = []()
    {
        auto err = NodeSendMessage.bind(nodeObj).call(bm::g_longStr).err;

        if (err != rtl::error::None)  {
            std::cout << "[2] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test2 = []()
    {
        auto err = GetMessage(bm::g_longStr).err;

        if (err != rtl::error::None) {
            std::cout << "[3] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        
        if (err != rtl::error::None) {
            std::cout << "[4] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };
}



void ReflectedCall::set(benchmark::State& state)
{
    static auto _=_test0();
    for (auto _: state) {

        auto error = SendMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedCall::get(benchmark::State& state)
{
    static auto _=_test2();
    for (auto _: state)
    {
        auto error = GetMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::set(benchmark::State& state)
{
    static auto _=_test1();
    for (auto _: state)
    {
        auto error = NodeSendMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::get(benchmark::State& state)
{
    static auto _=_test3();
    for (auto _: state)
    {
        auto error = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}
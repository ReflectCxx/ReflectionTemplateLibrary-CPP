
#include <benchmark/benchmark.h>
#include <rtl/rtl.h>

#include "ReflectedCall.h"
#include "BenchMark.h"


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
    static rtl::Function GetMessage;
    static rtl::Function SendMessage;

    static rtl::Method NodeGetMessage;
    static rtl::Method NodeSendMessage;
    
    static rtl::RObject nodeObj = []() 
    {    
        GetMessage = cxx::mirror().getFunction("getMessage").value();
        
        SendMessage = cxx::mirror().getFunction("sendMessage").value();

        auto Node = cxx::mirror().getRecord("Node").value();

        NodeGetMessage = Node.getMethod("getMessage").value();
        
        NodeSendMessage = Node.getMethod("sendMessage").value();
        
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
        auto err = SendMessage(bm::g_longStr).err;
        
        if (err != rtl::error::None) {
            std::cout << "[0] error: "<< rtl::to_string(err)<<"\n";
        }
        return 0;
    };


    static auto _test4 = []()
    {
        auto& hopper = (SendMessage.getFunctors()[0].m_lambda)->get<bm::argStr_t>();
        //auto err = hopper(bm::g_longStr).err;
        //if (err != rtl::error::None) {
        //    std::cout << "[4] error: " << rtl::to_string(err) << "\n";
        //}
        return hopper;
    };


    static auto _test1 = []()
    {
        auto err = NodeSendMessage(nodeObj)(bm::g_longStr).err;

        if (err != rtl::error::None)  {
            std::cout << "[1] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test2 = []()
    {
        auto err = GetMessage(bm::g_longStr).err;

        if (err != rtl::error::None) {
            std::cout << "[2] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        
        if (err != rtl::error::None) {
            std::cout << "[3] error: " << rtl::to_string(err) << "\n";
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

void ReflectedCall::new_design_set(benchmark::State& state)
{
    static const auto& hopper = _test4();
    for (auto _ : state) {

        hopper.call<bm::argStr_t>(bm::g_longStr);
        //auto ret = hopper(bm::g_longStr);
        benchmark::DoNotOptimize(bm::g_work_done->c_str());
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
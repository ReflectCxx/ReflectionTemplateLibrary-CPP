
#include "ReflectedCall.h"
#include "RTLibInterface.h"

namespace
{
    static const rtl::CxxMirror& cxx_mirror()
    {
        static auto m = rtl::CxxMirror({

            rtl::type().function("getMessage").build(bm::getMessage),

            rtl::type().function("sendMessage").build(bm::sendMessage),

            rtl::type().record<bm::Node>("Node").build(),

            rtl::type().member<bm::Node>().method("sendMessage").build(&bm::Node::sendMessage),

            rtl::type().member<bm::Node>().method("getMessage").build(&bm::Node::getMessage)
        });
        return m;
    }
    
    static rtl::Record Node = cxx_mirror().getRecord("Node").value();

    static rtl::RObject robj = Node.create<rtl::alloc::Stack>().rObject;

    static rtl::Method NodeGetMessage = Node.getMethod("getMessage").value();

    static rtl::Method NodeSendMessage = Node.getMethod("sendMessage").value();

    static rtl::Function GetMessage = cxx_mirror().getFunction("getMessage").value();

    static rtl::Function SendMessage = cxx_mirror().getFunction("sendMessage").value();
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

    static auto _test1 = []()
    {
        auto err = NodeSendMessage(robj)(bm::g_longStr).err;

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
        auto err = NodeGetMessage(robj)(bm::g_longStr).err;
        
        if (err != rtl::error::None) {
            std::cout << "[3] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };
}



void ReflectedCall::noReturn(benchmark::State& state)
{
    static auto _=_test0();
    for (auto _: state) {

        auto error = SendMessage.bind().call(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedCall::withReturn(benchmark::State& state)
{
    static auto _=_test2();
    for (auto _: state)
    {
        auto error = GetMessage.bind().call(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::noReturn(benchmark::State& state)
{
    static auto _=_test1();
    for (auto _: state)
    {
        auto error = NodeSendMessage.bind(robj).call(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::withReturn(benchmark::State& state)
{
    static auto _=_test3();
    for (auto _: state)
    {
        auto error = NodeGetMessage.bind(robj).call(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}
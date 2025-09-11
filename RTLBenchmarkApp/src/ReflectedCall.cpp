
#include "ReflectedCall.h"
#include "RTLibInterface.h"

namespace
{
    static rtl::RObject nodeObj;
    static rtl::Method NodeGetMessage;
    static rtl::Method NodeSendMessage;
    static rtl::Function GetMessage;
    static rtl::Function SendMessage;

    static auto _= []() {

        rtl::CxxMirror m = rtl::CxxMirror({

            rtl::type().function("getMessage").build(bm::getMessage),

            rtl::type().function("sendMessage").build(bm::sendMessage),

            rtl::type().record<bm::Node>("Node").build(),

            rtl::type().member<bm::Node>().method("sendMessage").build(&bm::Node::sendMessage),

            rtl::type().member<bm::Node>().method("getMessage").build(&bm::Node::getMessage)
        });

        GetMessage = m.getFunction("getMessage").value();
        
        SendMessage = m.getFunction("sendMessage").value();

        rtl::Record Node = m.getRecord("Node").value();

        nodeObj = std::move(Node.create<rtl::alloc::Stack>().rObject);
        
        NodeGetMessage = Node.getMethod("getMessage").value();
        NodeSendMessage = Node.getMethod("sendMessage").value();
        return true;
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



void ReflectedCall::noReturn(benchmark::State& state)
{
    static auto _=_test0();
    for (auto _: state) {

        auto error = SendMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedCall::withReturn(benchmark::State& state)
{
    static auto _=_test2();
    for (auto _: state)
    {
        auto error = GetMessage(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::noReturn(benchmark::State& state)
{
    static auto _=_test1();
    for (auto _: state)
    {
        auto error = NodeSendMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}


void ReflectedMethodCall::withReturn(benchmark::State& state)
{
    static auto _=_test3();
    for (auto _: state)
    {
        auto error = NodeGetMessage(nodeObj)(bm::g_longStr).err;
        benchmark::DoNotOptimize(error);
    }
}
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
    
    static rtl::Record rNode = cxx_mirror().getRecord("Node").value();

    static rtl::RObject robj = rNode.create<rtl::alloc::Stack>().rObject;
    
    static rtl::Method getMsgMethod = rNode.getMethod("getMessage").value();

    static rtl::Method sendMsgMethod = rNode.getMethod("sendMessage").value();
    
    static rtl::Function getMsg = cxx_mirror().getFunction("getMessage").value();

    static rtl::Function sendMsg = cxx_mirror().getFunction("sendMessage").value();
}


void ReflectedCall::noReturn(benchmark::State& state)
{
    static auto _ = []() {
        auto err = sendMsg.bind().call(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[0] err: "<< rtl::to_string(err)<<"\n";
        }
        return 0;
    }();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sendMsg.bind().call(bm::g_longStr));
    }
}


void ReflectedCall::noReturnMethod(benchmark::State& state)
{

    static auto _ = []() {
        auto err = sendMsgMethod.bind(robj).call(bm::g_longStr).err;
        if (err != rtl::error::None)  {
            std::cout << "[1] err: " << rtl::to_string(err) << "\n";
        }
        return 0;
    }();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(sendMsgMethod.bind(robj).call(bm::g_longStr));
    }
}


void ReflectedCall::withReturn(benchmark::State& state)
{
    static rtl::Function getMsg = cxx_mirror().getFunction("getMessage").value();
    static auto _ = []() {
        auto err = getMsg.bind().call(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[2] err: " << rtl::to_string(err) << "\n";
        }
        return 0;
    }();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMsg.bind().call(bm::g_longStr));
    }
}


void ReflectedCall::withReturnMethod(benchmark::State& state)
{
    static auto _ = []() {
        auto err = getMsgMethod.bind(robj).call(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cout << "[3] err: " << rtl::to_string(err) << "\n";
        }
        return 0;
    }();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(getMsgMethod.bind(robj).call(bm::g_longStr));
    }
}
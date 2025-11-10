
#include <iostream>
#include <benchmark/benchmark.h>
#include <rtl/access.h>

#include "BenchMark.h"
#include "ReflectedCallUnknownReturn.h"

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
    static rtl::Record class_Node = []()
    {
        std::optional<rtl::Record> Node = cxx::mirror().getRecord("Node");
        if (!Node) {
            std::cerr << "[x] error: record 'Node' not found.\n";
            std::abort();
        }
        return Node.value();
    }();

    static rtl::RObject nodeObj = []()
    {
        auto [err, robj] = class_Node.create<rtl::alloc::Stack>();
        if (robj.isEmpty()) {
            std::cerr << "[x] error: " << rtl::to_string(err) << "\n";
        }
        return std::move(robj);
    }();
}

namespace
{
    static rtl::function<rtl::Return(bm::argStr_t)> ErasedReturnFn_GetMessage = []()
    {
        std::optional<rtl::Function> optFunction = cxx::mirror().getFunction("getMessage");
        if (!optFunction) {
            std::cerr << "[0] error: function 'getMessage' not found.\n";
            std::abort();
        }
        auto function = optFunction->argsT<bm::argStr_t>().returnT<>();
        if (!function)
        {
            std::cerr << "[0] error: invalid function caller.\n";
            std::abort();
        }
        return function;
    }();

    static rtl::function<rtl::Return(bm::argStr_t)> ErasedReturnFn_SendMessage = []()
    {
        std::optional<rtl::Function> optFunction = cxx::mirror().getFunction("sendMessage");
        if (!optFunction) {
            std::cerr << "[1] error: function 'sendMessage' not found.\n";
            std::abort();
        }
        auto function = optFunction->argsT<bm::argStr_t>().returnT<>();
        if (!function)
        {
            std::cerr << "[1] error: invalid function caller.\n";
            std::abort();
        }
        return function;
    }();
}

namespace
{
    //----------------------------------------------------------------------------
    static rtl::method<bm::Node, rtl::Return(bm::argStr_t)> ErasedReturnAwareTarget_SendMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("sendMessage");
        if (!optMethod) {
            std::cerr << "[2] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<bm::Node>().argsT<bm::argStr_t>().returnT<>();
        if (!method) {
            std::cerr << "[2] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();

    static rtl::method<rtl::RObject, bm::retStr_t(bm::argStr_t)> ErasedTargetAwareReturn_SendMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("sendMessage");
        if (!optMethod) {
            std::cerr << "[3] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<>().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
        if (!method) {
            std::cerr << "[3] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();

    static rtl::method<rtl::RObject, rtl::Return(bm::argStr_t)> ErasedReturnAndTarget_SendMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("sendMessage");
        if (!optMethod) {
            std::cerr << "[4] error: method 'Node::sendMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<>().argsT<bm::argStr_t>().returnT<>();
        if (!method) {
            std::cerr << "[4] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();

    //----------------------------------------------------------------------------
    static rtl::method<bm::Node, rtl::Return(bm::argStr_t)> ErasedReturnAwareTarget_GetMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("getMessage");
        if (!optMethod) {
            std::cerr << "[5] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<bm::Node>().argsT<bm::argStr_t>().returnT<>();
        if (!method) {
            std::cerr << "[5] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();

    static rtl::method<rtl::RObject, bm::retStr_t(bm::argStr_t)> ErasedTargetAwareReturn_GetMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("getMessage");
        if (!optMethod) {
            std::cerr << "[6] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<>().argsT<bm::argStr_t>().returnT<bm::retStr_t>();
        if (!method) {
            std::cerr << "[6] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();

    static rtl::method<rtl::RObject, rtl::Return(bm::argStr_t)> ErasedReturnAndTarget_GetMessage = []()
    {
        std::optional<rtl::Method> optMethod = class_Node.getMethod("getMessage");
        if (!optMethod) {
            std::cerr << "[7] error: method 'Node::getMessage' not found.\n";
            std::abort();
        }
        auto method = optMethod->targetT<>().argsT<bm::argStr_t>().returnT<>();
        if (!method) {
            std::cerr << "[7] error: invalid method caller.\n";
            std::abort();
        }
        return method;
    }();
}

namespace
{
    static auto _test0 = []()
    {
        auto err = ErasedReturnFn_SendMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[00] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test1 = []()
    {
        auto err = ErasedReturnFn_GetMessage(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[01] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };
}

namespace
{
    static auto _test2 = []()
    {
        auto err = ErasedReturnAwareTarget_SendMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[02] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test3 = []()
    {
        auto err = ErasedReturnAwareTarget_GetMessage(bm::Node())(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[03] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test4 = []()
    {
        auto err = ErasedReturnAndTarget_SendMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[04] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test5 = []()
    {
        auto err = ErasedReturnAndTarget_GetMessage(nodeObj)(bm::g_longStr).err;
        if (err != rtl::error::None) {
            std::cerr << "[05] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test6 = []()
    {
        auto [err, returnOpt] = ErasedTargetAwareReturn_SendMessage(nodeObj)(bm::g_longStr);
        if (err != rtl::error::None) {
            std::cerr << "[06] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _test7 = []()
    {
        auto [err, returnOpt] = ErasedTargetAwareReturn_GetMessage(nodeObj)(bm::g_longStr);
        if (err != rtl::error::None) {
            std::cerr << "[07] error: " << rtl::to_string(err) << "\n";
        }
        return 0;
    };

    static auto _new_line = []() {
        std::cerr << std::endl;
        return 0;
    };
}


namespace bm_rtl
{
    void function__ErasedReturnType::set_string(benchmark::State& state)
    {
        static auto __ = _new_line();
        static auto _ = _test0();
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnFn_SendMessage(bm::g_longStr).err);
        }
    }

    void function__ErasedReturnType::get_string(benchmark::State& state)
    {
        static auto __ = _new_line();
        static auto _ = _test1();
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnFn_GetMessage(bm::g_longStr).err);
        }
    }
}


namespace bm_rtl
{
    void method____ErasedReturnType::set_string(benchmark::State& state)
    {
        static auto _ = _test2();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnAwareTarget_SendMessage(node)(bm::g_longStr));
        }
    }

    void method____ErasedReturnType::get_string(benchmark::State& state)
    {
        static auto _ = _test3();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnAwareTarget_GetMessage(node)(bm::g_longStr));
        }
    }

    void method____ErasedTargetType::set_string(benchmark::State& state)
    {
        static auto _ = _test6();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedTargetAwareReturn_SendMessage(nodeObj)(bm::g_longStr));
        }
    }

    void method____ErasedTargetType::get_string(benchmark::State& state)
    {
        static auto _ = _test7();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedTargetAwareReturn_GetMessage(nodeObj)(bm::g_longStr));
        }
    }

    void method____ErasedTargetAndReturnType::set_string(benchmark::State& state)
    {
        static auto _ = _test4();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnAndTarget_SendMessage(nodeObj)(bm::g_longStr));
        }
    }

    void method____ErasedTargetAndReturnType::get_string(benchmark::State& state)
    {
        static auto _ = _test5();
        static bm::Node node;
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(ErasedReturnAndTarget_GetMessage(nodeObj)(bm::g_longStr));
        }
    }
}
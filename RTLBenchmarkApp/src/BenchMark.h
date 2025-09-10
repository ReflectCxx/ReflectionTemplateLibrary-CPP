#pragma once

#include <benchmark/benchmark.h>

#include <optional>
#include <string>
#include <string_view>

#if defined(_MSC_VER)
#  define NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE
#endif

namespace bm
{
    using argStr_t = std::string_view;
    using retStr_t = std::string_view;

    static const char* LONG_STR = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do"
    "do aeiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis"
    "nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure"
    "dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Except"
    "eur ssint occaecat cupidatat nnon proident, sunt in culpa qui officia deserunt mollit anim id"
    "Lorem ipsum dolor sit amet laboris nisi ut aliquip ex ea commodo";
    
    static argStr_t g_longStr(LONG_STR);

    struct Node
    {
        void sendMessage(argStr_t);
        retStr_t getMessage(argStr_t);
    };

    extern void sendMessage(argStr_t);
    extern retStr_t getMessage(argStr_t);

    static std::optional<std::string> g_msg;
}
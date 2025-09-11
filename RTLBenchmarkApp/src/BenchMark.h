#pragma once

#include <string>
#include <string_view>

namespace bm
{
    using argStr_t = std::string_view;
    using retStr_t = std::string_view;
    
    struct Node
    {
        void sendMessage(argStr_t);
        retStr_t getMessage(argStr_t);
    };
}


namespace bm
{
    static argStr_t g_longStr = "Lorem ipsum"
    "dolor sit amet, consectetur adipiscing elit, sed do"
    "do aeiusmod tempor incididunt uth labore et dolore magna aliqua. Ut enim ad minim veniam, quis"
    "nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure"
    "dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Except"
    "eur ssint occaecat cupidatat nnon proident, sunt in culpa qui officia deserunt mollit anim id"
    "Lorem ipsum dolor sit amet laboris nisi ut aliquip ex ea commodo";
}


#include <optional>

#include <iostream>

#include "BenchMark.h"

extern std::size_t g_work_load;
extern std::optional<std::string> g_work_done;

namespace
{
    NOINLINE static std::string perform_work(bm::argStr_t& pMsg)
    {
        auto workStr = std::string();
        for(int i = 0; i < g_work_load; ++i)
        {
            workStr += pMsg;
        }
        return workStr;
    }
}


namespace bm
{
    NOINLINE void sendMessage(argStr_t pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        
        g_work_done = perform_work(pMsg);
    }

    NOINLINE void Node::sendMessage(argStr_t pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);

        g_work_done = perform_work(pMsg);
    }

    NOINLINE retStr_t getMessage(argStr_t pMsg)
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);

        g_work_done = perform_work(pMsg);
        return bm::retStr_t(g_work_done->c_str());
    }

    NOINLINE retStr_t Node::getMessage(argStr_t pMsg)
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);

        g_work_done = perform_work(pMsg);
        return bm::retStr_t(g_work_done->c_str());
    }
}


#include <optional>

#include <iostream>

#include "BenchMark.h"

extern std::size_t g_work_load_scale;

namespace
{
    static void work_load(bm::argStr_t& pMsg)
    {
        bm::g_msg = std::string();
        for(int i = 0; i < g_work_load_scale; ++i)
        {
            bm::g_msg->append(pMsg);
        }
    }
}


namespace bm
{
    NOINLINE void sendMessage(argStr_t pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        work_load(pMsg);
    }


    NOINLINE retStr_t getMessage(argStr_t pMsg)
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        work_load(pMsg);
        return bm::retStr_t(bm::g_msg->c_str());
    }


    NOINLINE void Node::sendMessage(argStr_t pMsg) 
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        work_load(pMsg);
    }


    NOINLINE retStr_t Node::getMessage(argStr_t pMsg)
    {
        volatile auto* p = &pMsg;
        static_cast<void>(p);
        work_load(pMsg);
        return bm::retStr_t(bm::g_msg->c_str());
    }
}

#include <any>
#include <functional>
#include "BenchMark.h"

namespace bm
{
    extern std::size_t g_work_load;
    std::string perform_work(const bm::argStr_t& pMsg)
    {
        auto workStr = std::string();
        for(int i = 0; i < bm::g_work_load; ++i)
        {
            workStr += pMsg;
        }
        return workStr;
    }
}


namespace bm
{
    extern void sendMessage(argStr_t);

    extern retStr_t getMessage(argStr_t);

    std::function<void(argStr_t&)> SendMessage = [](argStr_t& pMsg) 
    {
        bm::sendMessage(pMsg);
    };

    std::function<void(bm::Node, argStr_t&)> NodeSendMessage = [](bm::Node pNode, bm::argStr_t& pMsg) 
    {
        pNode.sendMessage(pMsg);
    };

    std::function<std::any(argStr_t&)> GetMessage = [](bm::argStr_t& pMsg)
    {
        //Testing.
        return std::any(bm::getMessage(pMsg));
        // auto retMsg = bm::getMessage(pMsg);
        // return retMsg;
    };

    std::function<retStr_t(bm::Node, argStr_t&)> NodeGetMessage = [](bm::Node pNode, bm::argStr_t& pMsg)
    {
        auto retMsg = pNode.getMessage(pMsg);
        return retMsg;
    };
}

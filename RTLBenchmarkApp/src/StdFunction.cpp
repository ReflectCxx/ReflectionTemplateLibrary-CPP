
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
    static Node node;

    extern void sendMessage(argStr_t);

    extern retStr_t getMessage(argStr_t);

    std::function<void(argStr_t&)> SendMessage = [](argStr_t& pMsg) 
    {
        bm::sendMessage(pMsg);
    };

    std::function<void(argStr_t&)> NodeSendMessage = [](bm::argStr_t& pMsg) 
    {
        node.sendMessage(pMsg);
    };

    std::function<retStr_t(argStr_t&)> GetMessage = [](bm::argStr_t& pMsg)
    {
        auto retMsg = bm::getMessage(pMsg);
        return retMsg;
    };

    std::function<retStr_t(argStr_t&)> NodeGetMessage = [](bm::argStr_t& pMsg)
    {
        auto retMsg = node.getMessage(pMsg);
        return retMsg;
    };
}

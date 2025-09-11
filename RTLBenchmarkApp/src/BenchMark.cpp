

#include <optional>
#include <iostream>
#include <functional>

#include "BenchMark.h"
#include "RTLibInterface.h"


namespace bm
{
    std::size_t g_work_load = 0;
    
    std::optional<std::string> g_work_done = std::string();

    extern std::string perform_work(const argStr_t& pMsg);
}


namespace bm
{
    void sendMessage(argStr_t pMsg) 
    {
        if(g_work_load){
            g_work_done = perform_work(pMsg);
        }
    }

    void Node::sendMessage(argStr_t pMsg) 
    {
        if(g_work_load){
            g_work_done = perform_work(pMsg);
        }
    }

    retStr_t getMessage(argStr_t pMsg)
    {
        if(g_work_load){
            g_work_done = perform_work(pMsg);
        }
        return retStr_t(g_work_done->c_str());
    }

    retStr_t Node::getMessage(argStr_t pMsg)
    {
        if(g_work_load){
            g_work_done = perform_work(pMsg);
        }
        return retStr_t(g_work_done->c_str());
    }
}


namespace cxx
{
    const rtl::CxxMirror& mirror()
    {
        static auto cxx_mirror = rtl::CxxMirror({

            rtl::type().function("getMessage").build(bm::getMessage),

            rtl::type().function("sendMessage").build(bm::sendMessage),

            rtl::type().record<bm::Node>("Node").build(),

            rtl::type().member<bm::Node>().method("sendMessage").build(&bm::Node::sendMessage),

            rtl::type().member<bm::Node>().method("getMessage").build(&bm::Node::getMessage)
        });

        return cxx_mirror;
    }
}
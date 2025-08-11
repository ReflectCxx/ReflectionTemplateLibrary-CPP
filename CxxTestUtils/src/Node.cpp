
#include "Node.h"

namespace test_utils
{
    std::size_t _moveOpsCount = 0;
    std::size_t _liveResourceCount = 0;
    std::size_t _liveNodeCount = 0;

    Node::~Node() 
    {
        _liveNodeCount--;
        if (m_deleter && m_data) {
            m_deleter(m_data);
            m_data = nullptr;
            m_deleter = nullptr;
        }
    }

    Node::Node(int pData)
        : m_data([=]() {
                _liveResourceCount++;
                return new int(pData);
            }())
        , m_deleter([](int* ptr) {
                _liveResourceCount--;
                delete ptr;
            }) {
        _liveNodeCount++;
    }

    //Node::Node(Node&& pOther) noexcept
    //    : data(pOther.data)
    //    , deleter(std::move(pOther.deleter)) {
    //    pOther.data = nullptr;
    //    pOther.deleter = nullptr;
    //    _liveNodeCount++;
    //    _moveOpsCount++;
    //}

    int Node::data() const {
        return *m_data;
    }

    bool Node::instanceCount() {
        return _liveNodeCount;
    }

    bool Node::assertResourcesReleased() {
        return (_liveResourceCount == 0);
    }

    bool Node::getMoveOpsCountAndReset() {
        std::size_t count = _moveOpsCount;
        _moveOpsCount = 0;
        return count;
    }
}


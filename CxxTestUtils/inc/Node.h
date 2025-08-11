#pragma once

#include <functional>

namespace test_utils 
{
    struct Node
    {
        ~Node();
        Node(int pData);
        Node(Node&& pOther) noexcept = delete;
        Node(const Node& pOther) = delete;  //Ensure's no copy. only move.
        Node& operator=(Node&&) = delete;
        Node& operator=(const Node&) = delete;

        int data() const;
        static bool instanceCount();
        static bool assertResourcesReleased();
        static bool getMoveOpsCountAndReset();

    private:
        int* m_data;
        std::function<void(int*)> m_deleter;
    };
}

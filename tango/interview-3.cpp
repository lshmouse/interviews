//Design a double linked list with only one pointer per node

#include <stdio.h>

template <class T>
class Node {    
public:
    Node(const T& value, const Node* prev, const Node* next) 
            : m_value(value) {
        m_prev_xor_next = (Node*)(((int)prev) ^ ((int)next));
    }

    void SetPrevAndNext(const Node* prev, const Node* next) {
        m_prev_xor_next = (Node*)(((int)prev) ^ ((int)next));
    }

    Node* GetPrevNode(const Node* next) {
        return (Node *)((int)m_prev_xor_next ^ (int)next);
    }

    Node* GetNextNode(const Node* prev) {
        return (Node *)((int)m_prev_xor_next ^ (int)prev);
    }

private:
    T m_value;
    Node* m_prev_xor_next;
};

int main() {
    Node<int> a(0, NULL, NULL);

}

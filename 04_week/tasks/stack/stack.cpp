#include <vector>
#include <stddef.h>


class Stack {
public:
    void Push(const int x);
    bool Pop();
    int& Top();
    int Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);
    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;
private:
    int m_null_value = 0;
    std::vector<int> m_stack{};
};

void Stack::Push(const int x) {
    m_stack.push_back(x);
}

bool Stack::Pop() {
    if (Empty()) {
        return false;
    }

    m_stack.pop_back();
    return true;
}

int Stack::Top() const {
    if (Empty()) {
        return m_null_value;
    }

    return m_stack.back();
}

int& Stack::Top() {
    if (Empty()) {
        return m_null_value;
    }

    return m_stack.back();
}

bool Stack::Empty() const {
    return m_stack.empty();
}

size_t Stack::Size() const {
    return m_stack.size();
}

void Stack::Clear() {
    return m_stack.clear();
}

void Stack::Swap(Stack& other) {
    m_stack.swap(other.m_stack);
}

bool Stack::operator==(const Stack& other) const {
    return m_stack == other.m_stack;
}

bool Stack::operator!=(const Stack& other) const {
    return m_stack != other.m_stack;
}

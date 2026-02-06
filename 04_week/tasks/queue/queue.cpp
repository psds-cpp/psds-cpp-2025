#include <vector>
#include <stack>
#include <stddef.h>


class Queue {
public:
    Queue() = default;
    Queue(std::stack<int> stack);
    Queue(std::vector<int> vector);
    Queue(std::initializer_list<int> values);
    Queue(const int size);
    void Push(const int x);
    bool Pop();
    int& Back();
    int Back() const;
    int& Front();
    int Front() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
private:
    int m_null_value = 0;
    std::vector<int> m_input{};
    std::vector<int> m_output{};
    std::vector<int> m_mergeVectors(const auto& input, const auto& output) const;
};

Queue::Queue(std::stack<int> stack) {
    while (!stack.empty()) {
        m_output.push_back(stack.top());
        stack.pop();
    }
}

Queue::Queue(std::vector<int> vector) {
    while (!vector.empty()) {
        m_output.push_back(vector.back());
        vector.pop_back();
    }
}

Queue::Queue(std::initializer_list<int> ilist) {
    for (const int v : ilist) {
        m_input.push_back(v);
    }
}

Queue::Queue(const int size) {
    m_input.reserve(size);
    m_output.reserve(size);
}

void Queue::Push(const int x) {
    m_input.push_back(x);
}

bool Queue::Pop() {
    if (Empty()) {
        return false;
    }

    if (m_output.empty()) {
        while (!m_input.empty()) {
            m_output.push_back(m_input.back());
            m_input.pop_back();
        }
    }

    m_output.pop_back();
    
    return true;
}

int& Queue::Back() {
    if (Empty())
        return m_null_value;

    return m_input.empty() ? m_output.front() : m_input.back();
}

int Queue::Back() const {
    if (Empty())
        return m_null_value;

    return m_input.empty() ? m_output.front() : m_input.back();
}

int& Queue::Front() {
    if (Empty())
        return m_null_value;

    return m_output.empty() ? m_input.front() : m_output.back();
}

int Queue::Front() const {
    if (Empty())
        return m_null_value;

    return m_output.empty() ? m_input.front() : m_output.back();
}

bool Queue::Empty() const {
    return m_input.empty() && m_output.empty();
}

size_t Queue::Size() const {
    return m_input.size() + m_output.size();
}

void Queue::Clear() {
    m_input.clear();
    m_output.clear();
}

void Queue::Swap(Queue& other) {
    m_input.swap(other.m_input);
    m_output.swap(other.m_output);
}

std::vector<int> Queue::m_mergeVectors(const auto& input, const auto& output) const {
    std::vector<int> merged{};
    merged.reserve(input.size() + output.size());

    for (int i = output.size() - 1; i >= 0; --i) {
        merged.push_back(output[i]);
    }

    for (size_t i = 0; i < input.size(); ++i) {
        merged.push_back(input[i]);
    }
    
    return merged;
}

bool Queue::operator==(const Queue& other) const {
    std::vector<int> this_merged = m_mergeVectors(m_input, m_output);
    std::vector<int> other_merged = m_mergeVectors(other.m_input, other.m_output);

    return this_merged == other_merged;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}
#include <vector>
#include <stack>
#include <algorithm>
#include <stddef.h>

class Queue {
public:
    Queue() = default;
    Queue(std::stack<int> stack);
    Queue(std::vector<int> vector);
    Queue(const std::initializer_list<int>& values);
    Queue(const size_t size);
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
    void m_pushInputBack();
};

Queue::Queue(std::stack<int> stack) {
    while (!stack.empty()) {
        m_output.push_back(stack.top());
        stack.pop();
    }
}

Queue::Queue(std::vector<int> vector) : m_output(std::move(vector)) {
    std::reverse(m_output.begin(), m_output.end());
}

Queue::Queue(const std::initializer_list<int>& ilist): m_input(ilist) {}

Queue::Queue(const size_t size) {
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
            m_pushInputBack();
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

void Queue::m_pushInputBack() {
    m_output.push_back(m_input.back());
    m_input.pop_back();
}

bool Queue::operator==(const Queue& other) const {
    if (this == &other) {
        return true;
    } else if (Size() != other.Size()) {
        return false;
    }

    const size_t out_size = m_output.size();
    const size_t other_out_size = other.m_output.size();
    const size_t total = Size();

    for (size_t i = 0; i < total; ++i) {
        const int& a = (i < out_size)
            ? m_output[out_size - 1 - i]
            : m_input[i - out_size];

        const int& b = (i < other_out_size)
            ? other.m_output[other_out_size - 1 - i]
            : other.m_input[i - other_out_size];

        if (a != b) return false;
    }
    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}
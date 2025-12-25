#include <vector>
#include <stack>
#include <initializer_list>
#include <iterator>
#include <algorithm>

class Queue {
public:
    Queue() {}
    Queue(size_t size);
    Queue(std::stack<int> st);
    Queue(const std::vector<int>& vec);
    Queue(std::initializer_list<int> il);

    void Push(int element);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

private:
    std::vector<int> m_input;
    std::vector<int> m_output;
};

Queue::Queue(size_t size) {
    if (size > 0) {
        m_input.reserve(size);
        m_output.reserve(size);
    }
}

Queue::Queue(std::stack<int> st) : Queue(st.size()) {
    while (!st.empty()) {
        m_output.push_back(st.top());
        st.pop();
    }
}

Queue::Queue(const std::vector<int>& vec) : Queue(vec.size()) {
    std::reverse_copy(vec.cbegin(), vec.cend(), std::back_inserter(m_output));
}

Queue::Queue(std::initializer_list<int> il) : Queue(il.size()) {
    std::reverse_copy(il.begin(), il.end(), std::back_inserter(m_output));
}

void Queue::Push(int element) {
    m_input.push_back(element);
}

bool Queue::Pop() {
    if (Empty()) {
        return false;
    }

    if (m_output.empty()) {
        std::reverse_copy(m_input.cbegin(), m_input.cend(), std::back_inserter(m_output));
        m_input.clear();
    }

    m_output.pop_back();

    return true;
}

int& Queue::Front() {
    if (m_output.empty()) {
        return m_input.front();
    }

    return m_output.back();
}

const int& Queue::Front() const {
    return (const_cast<Queue*>(this))->Front();
}

int& Queue::Back() {
    if (m_input.empty()) {
        return m_output.front();
    }

    return m_input.back();
}

const int& Queue::Back() const {
    return (const_cast<Queue*>(this))->Back();
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

bool Queue::operator==(const Queue& other) const {
    if (Size() != other.Size()) {
        return false;
    }

    std::vector<int> value1;
    std::vector<int> value2;

    value1.reserve(Size());
    value2.reserve(Size());

    std::reverse_copy(m_output.cbegin(), m_output.cend(), std::back_inserter(value1));
    std::copy(m_input.cbegin(), m_input.cend(), std::back_inserter(value1));

    std::reverse_copy(other.m_output.cbegin(), other.m_output.cend(), std::back_inserter(value2));
    std::copy(other.m_input.cbegin(), other.m_input.cend(), std::back_inserter(value2));

    return value1 == value2;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}
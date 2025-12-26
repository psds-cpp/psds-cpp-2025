#include <vector>
#include <stack>
#include <algorithm>


class Queue {
public:
    Queue();
    Queue(const std::vector<int>& input_vec);
    Queue(const std::initializer_list<int>& input_list);
    Queue(std::stack<int> input_stack);
    Queue(const int sizeQueue);

public:
    void Push(const int& num);
    bool Pop();

    int& Front();
    int& Back();
    int Front() const;
    int Back() const;

    int Size() const;
    void Clear();
    bool Empty() const;

    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

private:
    void UpdateOutVecQueue();
    friend void SwapVecs(std::vector<int>& v1, std::vector<int>& v2, size_t min_size);
    
    std::vector<int> m_in_vec = {};
    std::vector<int> m_out_vec = {};
};

Queue::Queue() = default;

Queue::Queue(const std::vector<int>& input_vec) : m_in_vec(input_vec) {};

Queue::Queue(const std::initializer_list<int>& input_list)
    : m_in_vec(static_cast<std::vector<int>>(input_list)) {
};

Queue::Queue(std::stack<int> input_stack) {
    m_in_vec.resize(input_stack.size());
    for (size_t i = m_in_vec.size(); i >= 1; --i) {
        m_in_vec[i - 1] = input_stack.top();
        input_stack.pop();
    }
};

Queue::Queue(const int sizeQueue) {
    m_in_vec.reserve(sizeQueue);
}

void Queue::UpdateOutVecQueue() {
    size_t size = m_in_vec.size();
    if (size == 0) return;
    for (size_t i = 0; i < size; ++i) {
        m_out_vec.push_back(m_in_vec[m_in_vec.size() - 1]);
        m_in_vec.pop_back();
    }
    m_in_vec.shrink_to_fit();
}

void Queue::Push(const int& num) {
    m_in_vec.push_back(num);
}

bool Queue::Pop() {
    if (m_out_vec.size() != 0) {
        m_out_vec.pop_back();
        return true;
    }
    else {
        UpdateOutVecQueue();
        if (m_out_vec.size() == 0) return false;
        m_out_vec.pop_back();
        return true;
    }
}

int& Queue::Front() {
    if (m_out_vec.size() != 0) return m_out_vec[m_out_vec.size() - 1];
    else if (m_in_vec.size() != 0) return m_in_vec[0];
    else {
        int trash = std::rand();
        int& ref_trash = trash;
        return ref_trash;
    }
}

int Queue::Front() const {
    if (m_out_vec.size() != 0) return m_out_vec[m_out_vec.size() - 1];
    else if (m_in_vec.size() != 0) return m_in_vec[0];
    return 0;
}

int& Queue::Back() {
    if (m_in_vec.size() != 0) return m_in_vec[m_in_vec.size() - 1];
    else if (m_out_vec.size() != 0) return m_out_vec[0];
    else {
        int trash = std::rand();
        int& ref_trash = trash;
        return ref_trash;
    }
}

int Queue::Back() const {
    if (m_in_vec.size() != 0) return m_in_vec[m_in_vec.size() - 1];
    else if (m_out_vec.size() != 0) return m_out_vec[0];
    return 0;
}

int Queue::Size() const {
    return m_in_vec.size() + m_out_vec.size();
}

void SwapVecs(std::vector<int>& v1, std::vector<int>& v2, size_t min_size) {
    v2.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        std::swap(v1[i], v2[i]);
    }
    v1.resize(min_size);
    v1.shrink_to_fit();
}

void Queue::Swap(Queue& other) {
    if (this == &other) return;
    
    size_t min_size_in = m_in_vec.size();
    size_t min_size_out = m_out_vec.size();

    if (min_size_in >= other.m_in_vec.size()) {
        min_size_in = other.m_in_vec.size();
        SwapVecs(m_in_vec, other.m_in_vec, min_size_in);
    }
    else {
        SwapVecs(other.m_in_vec, m_in_vec, min_size_in);;
    }

    if (min_size_out >= other.m_out_vec.size()) {
        min_size_out = other.m_out_vec.size();
        SwapVecs(m_out_vec, other.m_out_vec, min_size_out);
    }
    else {
        SwapVecs(other.m_out_vec, m_out_vec, min_size_out);;
    }
}

void Queue::Clear() {
    m_in_vec.resize(0);
    m_out_vec.resize(0);
}

bool Queue::Empty() const {
    return (m_in_vec.size() == 0 &&
        m_out_vec.size() == 0);
}

bool Queue::operator==(const Queue& other) const {
    if (this == &other) return true;

    std::vector<int> queue_this(m_in_vec.size() + m_out_vec.size());
    std::vector<int> queue_other(other.m_in_vec.size() + other.m_out_vec.size());

    if (queue_this.size() != queue_other.size()) return false;

    for (size_t i = 0; i < queue_this.size(); ++i) {
        if (i < m_out_vec.size())
            queue_this[i] = m_out_vec[m_out_vec.size() - 1 - i];
        if (i < m_in_vec.size())
            queue_this[i + m_out_vec.size()] = m_in_vec[i];

        if (i < other.m_out_vec.size())
            queue_other[i] = other.m_out_vec[other.m_out_vec.size() - 1 - i];
        if (i < other.m_in_vec.size())
            queue_other[i + other.m_out_vec.size()] = other.m_in_vec[i];
        
        if (queue_this[i] != queue_other[i]) return false;
    }
    return true;
}

bool Queue::operator!=(const Queue& other) const {
    if (this == &other) return false;

    std::vector<int> queue_this(m_in_vec.size() + m_out_vec.size());
    std::vector<int> queue_other(other.m_in_vec.size() + other.m_out_vec.size());

    if (queue_this.size() != queue_other.size()) return true;

    for (size_t i = 0; i < queue_this.size(); ++i) {
        if (i < m_out_vec.size())
            queue_this[i] = m_out_vec[m_out_vec.size() - 1 - i];
        if (i < m_in_vec.size())
            queue_this[i + m_out_vec.size()] = m_in_vec[i];

        if (i < other.m_out_vec.size())
            queue_other[i] = other.m_out_vec[other.m_out_vec.size() - 1 - i];
        if (i < other.m_in_vec.size())
            queue_other[i + other.m_out_vec.size()] = other.m_in_vec[i];
        
        if (queue_this[i] != queue_other[i]) return true;
    }
    return false;
}
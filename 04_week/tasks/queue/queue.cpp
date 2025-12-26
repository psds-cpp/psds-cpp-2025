#include <algorithm>
#include <initializer_list>
#include <vector>
#include <stack>


class Queue {
public:
    // Конструкторы (объявления)
    Queue();
    Queue(std::stack<int> st);
    Queue(std::vector<int> vec);
    Queue(std::initializer_list<int> list);
    Queue(int n);

    // Методы (объявления)
    size_t Size() const;
    bool Empty() const;
    void Push(int val);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    void Clear();
    void Swap(Queue& other);

    // Операторы (объявления)
    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

private:
    mutable std::vector<int> in;
    mutable std::vector<int> out;

    // Подготовка стека на вывод
    void prepareOut() const {
        if (out.empty()) {
            while (!in.empty()) {
                out.push_back(in.back());
                in.pop_back();
            }
        }
    }
};


// Конструкторы (реализации)

Queue::Queue() {};
Queue::Queue(std::stack<int> st) {
    while (!st.empty()) {
        this->Push(st.top());
        st.pop();
    }
    std::reverse(in.begin(), in.end());
}
Queue::Queue(std::vector<int> vec) : in(vec) {}
Queue::Queue(std::initializer_list<int> list) : in(list) {}
Queue::Queue(int n) {
    in.reserve(n);
    out.reserve(n);
}

//Методы (реализации)

size_t Queue::Size() const {
    return in.size() + out.size();
}

bool Queue::Empty() const {
    return in.empty() && out.empty();
}

void Queue::Push(int val) {
    in.push_back(val);
}

bool Queue::Pop() {
    prepareOut();
    if (out.empty())
        return false;
    out.pop_back();
    return true;
}

int& Queue::Front() {
    prepareOut();
    return out.back();
}

const int& Queue::Front() const {
    prepareOut();
    return out.back();
}

int& Queue::Back() {
    if (!in.empty())
        return in.back();
    return out.front(); 
}

const int& Queue::Back() const {
    if (!in.empty())
        return in.back();
    return out.front();
}

void Queue::Clear() {
    if (!in.empty())
        in.clear();
    if (!out.empty())
        out.clear();
}

void Queue::Swap(Queue& other) {
    std::swap(in, other.in);
    std::swap(out, other.out);
}

// Операторы (реализации)

bool Queue::operator==(const Queue& other) const {
    if ((this->in.size() + this->out.size()) != (other.in.size() + other.out.size()))
        return false;

    auto getVal = [](const Queue& q, size_t index) {
        if (index < q.out.size())
            return q.out[q.out.size() - 1 - index];
        return q.in[index - q.out.size()];
    };

    size_t total_size = this->in.size() + this->out.size();
    for (size_t i = 0; i < total_size; ++i)
        if (getVal(*this, i) != getVal(other, i))
            return false;

    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}
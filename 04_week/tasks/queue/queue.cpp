#include <vector>
#include <initializer_list>
#include <stack>

class Queue {
public:
    Queue() = default;
    Queue(const std::stack<int>& stack);
    Queue(const std::vector<int>& vector);
    Queue(std::initializer_list<int> init_list);
    Queue(size_t capacity);
    void Push(int value);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    bool operator==(const Queue& other) const {
        Queue first = *this;
        Queue second = other;
        if (first.Size() != second.Size())
            return false;
        while (!first.Empty()) {
            if (first.Front() != second.Front())
                return false;
            first.Pop();
            second.Pop();
        }
        return true;
    }
    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }
private:
    std::vector<int> in_;
    std::vector<int> out_;
};

Queue::Queue(const std::stack<int>& stack) {
    auto temp = stack;
    out_.reserve(temp.size());
    while(!temp.empty()) {
        out_.push_back(temp.top());
        temp.pop();
    }
}

Queue::Queue(const std::vector<int>& vector) {
    in_ = vector;
}

Queue::Queue(std::initializer_list<int> init_list) : in_(init_list) {}

Queue::Queue(size_t capacity) {
    in_.reserve(capacity);
    out_.reserve(capacity);
}

void Queue::Push(int value) {
    in_.push_back(value);
}

bool Queue::Pop() {
    if (out_.empty() && in_.empty())
        return false;
    if (out_.empty()) {
        while (!in_.empty()) {
            out_.push_back(in_.back());
            in_.pop_back();
        }
    }
    out_.pop_back();
    return true;
}

int& Queue::Front() {
    return const_cast<int&> (
        static_cast<const Queue&>(*this).Front()
    );
}

const int& Queue::Front() const {
    if (!out_.empty())
        return out_.back();
    return in_.front();
}

int& Queue::Back() {
    return const_cast<int&> (
        static_cast<const Queue&>(*this).Back()
        );
}

const int& Queue::Back() const {
    if (!in_.empty())
        return in_.back();
    return out_.front();
}

bool Queue::Empty() const {
    if (out_.empty() && in_.empty())
        return true;
    return false;
}

size_t Queue::Size() const {
    return (in_.size() + out_.size());
}

void Queue::Clear() {
    in_.clear();
    out_.clear();
}

void Queue::Swap(Queue &other) {
    in_.swap(other.in_);
    out_.swap(other.out_);
}

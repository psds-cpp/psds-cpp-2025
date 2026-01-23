#include <vector>
#include <stack>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class Queue {
private:
    std::vector<int> in_;
    std::vector<int> out_;

    void TransferIfNeeded() {
        if (out_.empty()) {
            while (!in_.empty()) {
                out_.push_back(in_.back());
                in_.pop_back();
            }
        }
    }

public:
    Queue() = default;

    explicit Queue(size_t size) {
        in_.reserve(size);
    }

    explicit Queue(const std::vector<int>& vec) : in_(vec) {}

    explicit Queue(std::stack<int> s) {
        while (!s.empty()) {
            out_.push_back(s.top());
            s.pop();
        }
    }

    Queue(std::initializer_list<int> il) : in_(il) {}

    Queue(const Queue& other) = default;

    Queue& operator=(const Queue& other) = default;

    Queue(Queue&& other) noexcept = default;

    Queue& operator=(Queue&& other) noexcept = default;

    ~Queue() = default;

    void Push(int value) {
        in_.push_back(value);
    }

    bool Pop() {
        if (Empty()) {
            return false;
        }
        TransferIfNeeded();
        out_.pop_back();
        return true;
    }

    int& Front() {
        if (Empty()) {
            static int dummy;
            return dummy;
        }
        if (out_.empty()) {
            return in_.front();
        }
        return out_.back();
    }

    const int& Front() const {
        if (Empty()) {
            static const int dummy = 0;
            return dummy;
        }
        if (out_.empty()) {
            return in_.front();
        }
        return out_.back();
    }

    int& Back() {
        if (Empty()) {
            static int dummy;
            return dummy;
        }
        if (in_.empty()) {
            return out_.front();
        }
        return in_.back();
    }

    const int& Back() const {
        if (Empty()) {
            static const int dummy = 0;
            return dummy;
        }
        if (in_.empty()) {
            return out_.front();
        }
        return in_.back();
    }

    bool Empty() const {
        return in_.empty() && out_.empty();
    }

    size_t Size() const {
        return in_.size() + out_.size();
    }

    void Clear() {
        in_.clear();
        out_.clear();
    }

    void Swap(Queue& other) noexcept {
        in_.swap(other.in_);
        out_.swap(other.out_);
    }

    bool operator==(const Queue& other) const {
        if (Size() != other.Size()) {
            return false;
        }
        
        Queue q1 = *this;
        Queue q2 = other;
        
        while (!q1.Empty() && !q2.Empty()) {
            if (q1.Front() != q2.Front()) {
                return false;
            }
            q1.Pop();
            q2.Pop();
        }
        return true;
    }

    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }
};
#include <vector>
#include <algorithm>

class Stack {
private:
    std::vector<int> data_;

public:
    void Push(int value) {
        data_.push_back(value);
    }

    bool Pop() {
        if (Empty()) return false;
        data_.pop_back();
        return true;
    }

    int& Top() {
        return data_.back();
    }

    const int& Top() const {
        return data_.back();
    }

    bool Empty() const {
        return data_.empty();
    }

    size_t Size() const {
        return data_.size();
    }

    void Clear() {
        data_.clear();
    }

    void Swap(Stack& other) {
        data_.swap(other.data_);
    }

    bool operator==(const Stack& other) const {
        return data_ == other.data_;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }
};


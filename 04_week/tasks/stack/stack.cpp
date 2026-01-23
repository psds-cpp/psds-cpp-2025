#include <vector>

class Stack {
public:
    Stack() = default;

    void Push(int value);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

private:
    std::vector<int> data_;};

void Stack::Push(int value) {
    data_.push_back(value);
}

bool Stack::Pop() {
    if (data_.empty()) {
        return false;
    }
    data_.pop_back();
    return true;
}

int& Stack::Top() {
    static int dummy = 0;
    return data_.empty() ? dummy : data_.back();
}

const int& Stack::Top() const {
    static const int dummy = 0;
    return data_.empty() ? dummy : data_.back();
}

bool Stack::Empty() const {
    return data_.empty();
}

size_t Stack::Size() const {
    return data_.size();
}

void Stack::Clear() {
    data_.clear();
}

void Stack::Swap(Stack& other) {
    data_.swap(other.data_);
}

bool Stack::operator==(const Stack& other) const {
    return data_ == other.data_;
}

bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}
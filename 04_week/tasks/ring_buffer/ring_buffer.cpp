#include <vector>
#include <initializer_list>
#include <algorithm>

class RingBuffer {
private:
    std::vector<int> buffer_;
    size_t start_ = 0;
    size_t size_ = 0;

    size_t NextIndex(size_t index) const {
        return (index + 1) % buffer_.size();
    }

    size_t Index(size_t logical_index) const {
        return (start_ + logical_index) % buffer_.size();
    }

public:
    explicit RingBuffer(size_t capacity = 1) {
        buffer_.resize(std::max(capacity, size_t(1)));
    }

    RingBuffer(size_t capacity, int value) {
        buffer_.resize(std::max(capacity, size_t(1)), value);
        size_ = buffer_.size();
    }

    RingBuffer(std::initializer_list<int> init) {
        buffer_ = init;
        size_ = buffer_.size();
        if (size_ == 0) { 
            buffer_.resize(1);
            size_ = 0;
        }
    }

    void Push(int value) {
        if (Full()) {
            buffer_[start_] = value;
            start_ = NextIndex(start_);
        } else {
            buffer_[Index(size_)] = value;
            ++size_;
        }
    }

    bool TryPush(int value) {
        if (Full()) return false;
        Push(value);
        return true;
    }

    void Pop() {
        if (!Empty()) {
            start_ = NextIndex(start_);
            --size_;
        }
    }

    bool TryPop(int& value) {
        if (Empty()) return false;
        value = buffer_[start_];
        Pop();
        return true;
    }

    int& operator[](size_t idx) {
        return buffer_[Index(idx)];
    }

    const int& operator[](size_t idx) const {
        return buffer_[Index(idx)];
    }

    int& Front() {
        return buffer_[Index(size_ - 1)];
    }

    int& Back() {
        return buffer_[start_];
    }

    bool Empty() const { return size_ == 0; }
    bool Full() const { return size_ == buffer_.size(); }
    size_t Size() const { return size_; }
    size_t Capacity() const { return buffer_.size(); }

    void Clear() {
        start_ = 0;
        size_ = 0;
    }

    void Resize(size_t new_capacity) {
        new_capacity = std::max(new_capacity, size_t(1));
        std::vector<int> new_buf(new_capacity);
        size_t new_size = std::min(size_, new_capacity);
        for (size_t i = 0; i < new_size; ++i) {
            new_buf[i] = (*this)[i + size_ - new_size];
        }
        buffer_ = std::move(new_buf);
        size_ = new_size;
        start_ = 0;
    }

    std::vector<int> Vector() const {
        std::vector<int> v(size_);
        for (size_t i = 0; i < size_; ++i) {
            v[i] = (*this)[i];
        }
        return v;
    }
};


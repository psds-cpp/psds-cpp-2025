#include <vector>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

class RingBuffer {
private:
    std::vector<int> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void advance(size_t& index) const {
        index = (index + 1) % capacity_;
    }

    void ensure_nonzero_capacity(size_t& capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
    }

    size_t logical_to_physical(size_t logical_index) const {
        return (head_ + logical_index) % capacity_;
    }

public:
    explicit RingBuffer(size_t capacity) {
        ensure_nonzero_capacity(capacity);
        capacity_ = capacity;
        buffer_.resize(capacity_);
    }

    RingBuffer(size_t capacity, int initial_value) : RingBuffer(capacity) {
        size_ = capacity_;
        tail_ = 0; // буфер полностью заполнен, tail указывает на head
        std::fill(buffer_.begin(), buffer_.end(), initial_value);
    }

    RingBuffer(std::initializer_list<int> init) {
        capacity_ = init.size();
        ensure_nonzero_capacity(capacity_);
        buffer_.resize(capacity_);
        size_ = init.size();
        size_t i = 0;
        for (int val : init) {
            buffer_[i++] = val;
        }
        tail_ = size_ == capacity_ ? 0 : size_;
    }

    int& operator[](size_t index) {
        return buffer_[logical_to_physical(index)];
    }

    const int& operator[](size_t index) const {
        return buffer_[logical_to_physical(index)];
    }

    int& Front() {
        return size_ == 0 ? buffer_[0] : buffer_[(tail_ + capacity_ - 1) % capacity_];
    }

    const int& Front() const {
        return size_ == 0 ? buffer_[0] : buffer_[(tail_ + capacity_ - 1) % capacity_];
    }

    int& Back() {
        return size_ == 0 ? buffer_[0] : buffer_[head_];
    }

    const int& Back() const {
        return size_ == 0 ? buffer_[0] : buffer_[head_];
    }

    bool Empty() const { return size_ == 0; }
    bool Full() const { return size_ == capacity_; }
    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity_; }

    void Push(int value) {
        if (Full()) {
            buffer_[tail_] = value;
            advance(tail_);
            head_ = tail_; 
        } else {
            buffer_[tail_] = value;
            advance(tail_);
            ++size_;
        }
    }

    bool TryPush(int value) {
        if (Full()) {
            return false;
        }
        Push(value);
        return true;
    }

    void Pop() {
        if (!Empty()) {
            advance(head_);
            --size_;
        }
    }

    bool TryPop(int& value) {
        if (Empty()) {
            return false;
        }
        value = Back();
        Pop();
        return true;
    }

    void Clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    void Resize(size_t new_capacity) {
        ensure_nonzero_capacity(new_capacity);
        if (new_capacity == capacity_) {
            return;
        }

        std::vector<int> new_buffer(new_capacity);
        size_t elements_to_copy = std::min(size_, new_capacity);
        size_t start_index = size_ > new_capacity ? size_ - new_capacity : 0;

        for (size_t i = 0; i < elements_to_copy; ++i) {
            new_buffer[i] = (*this)[start_index + i];
        }

        buffer_ = std::move(new_buffer);
        capacity_ = new_capacity;
        head_ = 0;
        size_ = elements_to_copy;
        tail_ = size_ % capacity_;
    }

    std::vector<int> Vector() const {
        std::vector<int> result;
        result.reserve(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.push_back((*this)[i]);
        }
        return result;
    }

    RingBuffer(const RingBuffer&) = default;
    RingBuffer& operator=(const RingBuffer&) = default;
    RingBuffer(RingBuffer&&) = default;
    RingBuffer& operator=(RingBuffer&&) = default;
    ~RingBuffer() = default;
};
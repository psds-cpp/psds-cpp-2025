#include <algorithm>
#include <initializer_list>
#include <vector>

class RingBuffer {
public:
    RingBuffer() : ringBuff_(1), head_(0), tail_(0), size_(0) {}
    
    RingBuffer(size_t capacity) : ringBuff_(capacity > 0 ? capacity : 1),
                                  head_(0),
                                  tail_(0),
                                  size_(0) {}

    RingBuffer(size_t capacity, int iVal) : ringBuff_(capacity > 0 ? capacity : 1, iVal),
                                            head_(capacity),
                                            tail_(0),
                                            size_(capacity > 0 ? capacity : 1) {}

    RingBuffer(std::initializer_list<int> list) : ringBuff_(list), head_(0), tail_(0), size_(list.size()) {        
        if (list.size() == 0) {
            ringBuff_.reserve(1);
            size_ = 0;
        }
    }

    void Push(int val);
    bool TryPush(int val);
    void Pop();
    bool TryPop(int& val);
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(size_t newSize);
    std::vector<int> Vector() const;
    
    int& operator[](size_t idx) {
        return ringBuff_[(tail_ + idx) % ringBuff_.capacity()];
    }

    const int& operator[](size_t idx) const {
        return ringBuff_[(tail_ + idx) % ringBuff_.capacity()];
    }

private:
    std::vector<int> ringBuff_{};
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
};

void RingBuffer::Push(int val) {
    size_t cap = ringBuff_.capacity();
    
    ringBuff_[head_] = val;
    // при head = buff.capacity(), head снова станет = 0
    head_ = (head_ + 1) % cap;

    if (size_ < cap) {
        ++size_;
    } else {
        // аналогично head
        tail_ = (tail_ + 1) % cap;
    }
}

bool RingBuffer::TryPush(int val) {
    size_t capacity = ringBuff_.capacity();

    if (size_ == capacity) {
        return false;
    }

    ringBuff_[head_] = val;
    // при head = buff.capacity(), head снова станет = 0
    head_ = (head_ + 1) % capacity;

    ++size_;

    return true;
}

void RingBuffer::Pop() {
    if (size_ > 0) {
        tail_ = (tail_ + 1) % ringBuff_.capacity();
        --size_;
    }
}

bool RingBuffer::TryPop(int& val) {    
    if (size_ == 0) {
        return false;
    }
        
    val = ringBuff_[tail_];
    tail_ = (tail_ + 1) % ringBuff_.capacity();
    --size_;
    return true;
}

int& RingBuffer::Front() {
    if (head_ == 0) {
        return ringBuff_.back();
    }
    
    return ringBuff_[head_ - 1];
}

const int& RingBuffer::Front() const {
    if (head_ == 0) {
        return ringBuff_.back();
    }
    
    return ringBuff_[head_ - 1];
}
    
int& RingBuffer::Back() {
    return ringBuff_[tail_];
}

const int& RingBuffer::Back() const {
    return ringBuff_[tail_];
}

bool RingBuffer::Empty() const {
    return size_ == 0;
}


bool RingBuffer::Full() const {
    return size_ == ringBuff_.capacity();
}

size_t RingBuffer::Size() const {
    return size_;
}

size_t RingBuffer::Capacity() const {
    return ringBuff_.capacity();
}

void RingBuffer::Clear() {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

void RingBuffer::Resize(size_t newSize) {
    if (newSize == 0) {
        newSize = 1;
    }

    if (newSize == ringBuff_.capacity()) {
        return;
    }


    std::vector<int> tempV(newSize);

    size_t elemsToCopy = std::min(size_, newSize);
    for (size_t i = 0; i < elemsToCopy; ++i) {
        tempV[i] = ringBuff_[(tail_ + size_ - elemsToCopy + i) % ringBuff_.capacity()];
    }

    ringBuff_.swap(tempV);

    tail_ = 0;
    head_ = elemsToCopy;
    size_ = elemsToCopy;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> rb_as_vector;
    size_t capacity = ringBuff_.capacity();
    rb_as_vector.reserve(capacity);
    
    for (size_t i = 0; i < size_; ++i) {
        rb_as_vector.push_back(ringBuff_[(tail_ + i) % capacity]);
    }

    return rb_as_vector;
 } 

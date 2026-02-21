#include <vector>
#include <stdexcept>
#include <algorithm>

class RingBuffer {
private:
    std::vector<int> data_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
    bool full_ = false;

    size_t n_pos(size_t pos) const noexcept;
    size_t p_pos(size_t pos) const noexcept;
    void copy_nbuffer(RingBuffer& new_buffer) const;
    void rebuild_buffer(size_t new_capacity);

public:
    // Конструкторы
    explicit RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int initial_value);
    RingBuffer(std::initializer_list<int> init);
    
    // Копирующие операции
    RingBuffer(const RingBuffer& other);
    RingBuffer& operator=(const RingBuffer& other);

    void Push(int value);
    bool TryPush(int value);
    void Pop();
    bool TryPop(int& value);
    
    // Доступ к элементам
    int operator[](size_t index) const;
    int& operator[](size_t index);
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    bool Empty() const noexcept;
    bool Full() const noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    void Clear() noexcept;
    
    // Изменение размера
    void Resize(size_t new_capacity);
    
    // Конвертация
    std::vector<int> Vector() const;
};

// Вспомогательные методы

size_t RingBuffer::n_pos(size_t pos) const noexcept {
    return (pos + 1) % data_.size();
}

size_t RingBuffer::p_pos(size_t pos) const noexcept {
    return (pos == 0) ? data_.size() - 1 : pos - 1;
}

void RingBuffer::copy_nbuffer(RingBuffer& new_buffer) const {
    if (size_ == 0) return;
    
    for (size_t i = 0; i < size_; ++i) {
        new_buffer.Push((*this)[i]);
    }
}

void RingBuffer::rebuild_buffer(size_t new_capacity) {
    std::vector<int> new_data(new_capacity);
    size_t new_size = (new_capacity < size_) ? new_capacity : size_;
    
    for (size_t i = 0; i < new_size; ++i) {
        new_data[i] = (*this)[(size_ - new_size) + i];
    }
    
    data_ = std::move(new_data);
    head_ = 0;
    tail_ = new_size % new_capacity;
    size_ = new_size;
    full_ = (new_size == new_capacity);
}

// Конструкторы

RingBuffer::RingBuffer(size_t capacity) {
    size_t actual_capacity = (capacity == 0) ? 1 : capacity;
    data_.resize(actual_capacity);
}

RingBuffer::RingBuffer(size_t capacity, int initial_value) {
    size_t actual_capacity = (capacity == 0) ? 1 : capacity;
    data_.resize(actual_capacity);
    
    for (size_t i = 0; i < actual_capacity; ++i) {
        data_[i] = initial_value;
    }
    head_ = 0;
    tail_ = 0;
    size_ = actual_capacity;
    full_ = (actual_capacity > 0);
}

RingBuffer::RingBuffer(std::initializer_list<int> init) {
    size_t capacity = init.size();
    if (capacity == 0) {
        capacity = 1;
    }
    data_.resize(capacity);
    
    for (int value : init) {
        Push(value);
    }
}

// Копирующие операции

RingBuffer::RingBuffer(const RingBuffer& other) 
    : data_(other.data_), 
      head_(other.head_), 
      tail_(other.tail_), 
      size_(other.size_),
      full_(other.full_) {}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (this != &other) {
        data_ = other.data_;
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        full_ = other.full_;
    }
    return *this;
}

// Основные операции

void RingBuffer::Push(int value) {
    if (full_) {
        data_[tail_] = value;
        tail_ = n_pos(tail_);
        head_ = tail_;
    } else {
        data_[tail_] = value;
        tail_ = n_pos(tail_);
        ++size_;
        full_ = (head_ == tail_);
    }
}

bool RingBuffer::TryPush(int value) {
    if (full_) {
        return false;
    }
    Push(value);
    return true;
}

void RingBuffer::Pop() {
    if (Empty()) {
        return;
    }
    head_ = n_pos(head_);
    --size_;
    full_ = false;
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) {
        return false;
    }
    value = data_[head_];
    Pop();
    return true;
}

// Доступ к элементам

int RingBuffer::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[(head_ + index) % data_.size()];
}

int& RingBuffer::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[(head_ + index) % data_.size()];
}

int& RingBuffer::Front() {
    if (size_ == 0) {
        // UB согласно условию
        return data_[head_];
    }
    return data_[p_pos(tail_)];
}

const int& RingBuffer::Front() const {
    if (size_ == 0) {
        // UB согласно условию
        return data_[head_];
    }
    return data_[p_pos(tail_)];
}

int& RingBuffer::Back() {
    if (size_ == 0) {
        // UB согласно условию
        return data_[head_];
    }
    return data_[head_];
}

const int& RingBuffer::Back() const {
    if (size_ == 0) {
        // UB согласно условию
        return data_[head_];
    }
    return data_[head_];
}

// Состояние буфера

bool RingBuffer::Empty() const noexcept {
    return !full_ && (head_ == tail_);
}

bool RingBuffer::Full() const noexcept {
    return full_;
}

size_t RingBuffer::Size() const noexcept {
    return size_;
}

size_t RingBuffer::Capacity() const noexcept {
    return data_.size();
}

void RingBuffer::Clear() noexcept {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
    full_ = false;
}

// Изменение размера

void RingBuffer::Resize(size_t new_capacity) {
    if (new_capacity == 0) {
        new_capacity = 1;
    }
    
    if (new_capacity == data_.size()) {
        return;
    }

    rebuild_buffer(new_capacity);
}

// Конвертация

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> result;
    result.reserve(size_);
    
    for (size_t i = 0; i < size_; ++i) {
        result.push_back((*this)[i]);
    }
    
    return result;
}
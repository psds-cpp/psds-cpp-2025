#include "simple_vector.hpp"

SimpleVector::SimpleVector(const size_t size) : data_(new int[size]()), size_(size), capacity_(size) {}

SimpleVector::SimpleVector(const size_t size, const int value) : data_(new int[size]()), size_(size), capacity_(size) {
    std::ranges::fill(begin(), end(), value);
}

SimpleVector::SimpleVector(const std::initializer_list<int> list) : data_(new int[list.size()]), size_(list.size()), capacity_(list.size()) {
    std::ranges::move(list, begin());
}

SimpleVector::SimpleVector(const SimpleVector& other) : data_(new int[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    std::ranges::copy(other, begin());
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        delete[] data_;
        data_ = new int[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        std::ranges::copy(other, begin());
    }
    return *this;
}

SimpleVector::SimpleVector(SimpleVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

SimpleVector::~SimpleVector() {
    delete[] data_;
}

void SimpleVector::Swap(SimpleVector& other) {
    if (this == &other) return;
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& SimpleVector::operator[](const size_t index) {
    return data_[index];
}

const int& SimpleVector::operator[](const size_t index) const {
    return data_[index];
}

size_t SimpleVector::Size() const {
    return size_;
}

size_t SimpleVector::Capacity() const {
    return capacity_;
}

bool SimpleVector::Empty() const {
    return size_ == 0;
}

int* SimpleVector::Data() {
    return data_;
}

const int* SimpleVector::Data() const {
    return data_;
}

void SimpleVector::PushBack(const int value) {
    if (size_ == capacity_) {
        const size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }
    data_[size_++] = value;
}

void SimpleVector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

int* SimpleVector::Insert(const int* pos, int value) {
    if (pos < data_ || pos > (data_ + size_)) {
        return data_ + size_;
    }

    size_t index = pos - data_;
    auto after_range = std::ranges::subrange(begin() + index, end());
    if (size_ == capacity_) {
        const size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        const auto new_data = new int[new_capacity];

        auto before_range = std::ranges::subrange(begin(), begin() + index);
        std::ranges::copy(before_range, new_data);
        new_data[index] = value;
        std::ranges::copy(after_range, new_data + index + 1);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    } else {
        std::ranges::copy_backward(after_range, end() + 1);
        data_[index] = value;
    }

    ++size_;
    return data_ + index;
}

int* SimpleVector::Erase(const int* pos) {
    if (pos < data_ || pos >= (data_ + size_)) {
        return data_ + size_;
    }

    const size_t index = pos - data_;
    auto after_range = std::ranges::subrange(begin() + index + 1, end());
    std::ranges::copy(after_range, begin() + index);

    --size_;
    return data_ + index;
}

void SimpleVector::Clear() {
    size_ = 0;
}

void SimpleVector::Resize(const size_t new_size, const int value) {
    if (new_size == size_) return;

    if (new_size >= size_) {
        if (new_size > capacity_) {
            Reserve(new_size);
        }

        std::ranges::fill(end(), begin() + new_size, value);
    }
    size_ = new_size;
}

void SimpleVector::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) return;

    auto* new_data = new int[new_capacity];
    std::ranges::copy(*this, new_data);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

int* SimpleVector::begin() const {
    return data_;
}

int* SimpleVector::end() const {
    return data_ + size_;
}

bool SimpleVector::operator==(const SimpleVector& other) const {
    return std::ranges::equal(*this, other);
}

bool SimpleVector::operator!=(const SimpleVector& other) const {
    return !(*this == other);
}

inline void swap(SimpleVector& first, SimpleVector& second) noexcept {
    first.Swap(second);
}
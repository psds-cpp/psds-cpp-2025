#include <cstring>
#include <initializer_list>
#include <utility>

class SimpleVector {
public:
    SimpleVector();
    SimpleVector(size_t size, int value);
    SimpleVector(std::initializer_list<int> list);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other);
    ~SimpleVector();
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    size_t Size() const noexcept { return size_; }
    size_t Capacity() const noexcept { return capacity_; }
    bool Empty() const noexcept {return size_ == 0; }
    const int* Data() const noexcept { return data_; }
    int& operator[](size_t index) const;
    bool operator==(const SimpleVector& other) const;
    void Swap(SimpleVector& other);
    void PushBack(int value);
    void PopBack();
    void Reserve(size_t cap);
    int* Insert(size_t pos, int value);
    int* Insert(const int* ptr, int value);
    int* Erase(size_t pos);
    int* Erase(const int* ptr);
    void Resize(size_t size, int value);
    void Clear();
    int* begin() const { return data_; }
    int* end() const { return data_ + size_; }

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

SimpleVector::SimpleVector():
    data_(nullptr),
    size_(0),
    capacity_(0) {}

SimpleVector::SimpleVector(size_t size, int value = 0):
    data_(new int[size]),
    size_(size),
    capacity_(size) {
    for(size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

SimpleVector::SimpleVector(std::initializer_list<int> list):
    data_(new int[list.size()]),
    size_(list.size()),
    capacity_(list.size()) {
    for(size_t i = 0; i < size_; ++i) {
        data_[i] = std::data(list)[i];
    }
}

SimpleVector::SimpleVector(const SimpleVector& other):
    data_(new int[other.size_]),
    size_(other.size_),
    capacity_(other.size_) {
    for(size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

SimpleVector::SimpleVector(SimpleVector&& other):
    data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

SimpleVector::~SimpleVector() {
    delete[] data_;
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if(this->data_ != other.data_) {
        delete[] data_;
        data_ = new int[other.size_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for(size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if(this->data_ != other.data_) {
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

int& SimpleVector::operator[](size_t index) const {
    return data_[index];
}

bool SimpleVector::operator==(const SimpleVector& other) const {
    if(size_ != other.size_) return false;
    return std::memcmp(data_, other.data_, size_ * sizeof(int)) == 0;
}

void SimpleVector::Swap(SimpleVector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void SimpleVector::Reserve(size_t cap) {
    if(cap <= capacity_) {
        return;
    }
    int* tmp = data_;
    data_ = new int[cap];
    capacity_ = cap;
    if(tmp != nullptr) {
        for(size_t i = 0; i < size_; ++i) {
            data_[i] = tmp[i];
        }
    }
    delete[] tmp;
}

void SimpleVector::PushBack(int value) {
    if(size_ == capacity_){
        size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        Reserve(new_cap);
    }
    data_[size_++] = value;
}

void SimpleVector::PopBack() {
    size_ -= size_ == 0 ? 0 : 1;
}

int* SimpleVector::Insert(size_t pos, int value) {
    if(pos > size_) {
        return data_ + size_;
    }
    if(size_ == capacity_){
        Reserve(capacity_ * 2);
    }
    for(size_t i = size_; i > pos; --i) {
        data_[i] = data_[i - 1];
    }
    data_[pos] = value;
    ++size_;
    return data_ + pos;
}

int* SimpleVector::Insert(const int* ptr, int value) {
    if (ptr < data_ || ptr > data_ + size_) {
        return data_ + size_;
    }
    size_t pos = ptr - data_;
    return Insert(pos, value);
}

int* SimpleVector::Erase(size_t pos) {
    if(pos > size_) {
        return data_ + size_;
    }
    for(size_t i = pos; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
    return data_ + pos;
}

int* SimpleVector::Erase(const int* ptr) {
    if (ptr < data_ || ptr > data_ + size_) {
        return data_ + size_;
    }
    size_t pos = ptr - data_;
    return Erase(pos);
}

void SimpleVector::Resize(size_t size, int value = 0) {
    if(size_ == size) {
        return;
    }
    if(size < size_) {
        size_ = size;
        return;
    }
    if(size > capacity_) {
        Reserve(capacity_ * 2);
    }
    for(size_t i = size_; i < size; ++i) {
        data_[i] = value;
    }
    size_ = size;
}

void SimpleVector::Clear() {
    size_ = 0;
}


void swap(SimpleVector& a, SimpleVector& b) {
    a.Swap(b);
}
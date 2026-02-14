#include <algorithm>
#include <cstddef>
#include <cstring>
#include <initializer_list>

class SimpleVector {
public:
    SimpleVector() = default;

    SimpleVector(size_t size) : begin_(new int[size]{0}), end_(begin_ + size), capacity_(end_) {}
    
    SimpleVector(size_t size, int value) : begin_(new int[size]), end_(begin_ + size), capacity_(end_) {
        std::fill(begin_, end_, value);
    }
    
    SimpleVector(std::initializer_list<int> list) : begin_(new int[list.size()]),
                                                    end_(std::copy(list.begin(), list.end(), begin_)),
                                                    capacity_(end_) {}

    SimpleVector(const SimpleVector& other) {        
        if (other.Empty()) {
            begin_ = end_ = capacity_ = nullptr;
            return;
        }

        size_t capacity = other.Capacity();
        begin_ = new int[capacity];
        end_ = std::copy(other.begin_, other.end_, begin_);
        capacity_ = begin_ + capacity;
    }

    SimpleVector(SimpleVector&& other) : end_(other.end_), capacity_(other.capacity_) {
        if (begin_) {
            delete[] begin_;
        }

        begin_ = other.begin_; 
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.capacity_ = nullptr;
    }
    
    ~SimpleVector() {
        delete [] begin_;
        begin_ = end_ = capacity_ = nullptr;        
    }

    SimpleVector& operator=(const SimpleVector& other) {
        if (&other == this) {
            return *this;
        }

        if (begin_) {
            delete[] begin_;
        }

        if (other.Empty()) {
            begin_ = end_ = capacity_ = nullptr;
            return *this;
        }

        size_t capacity = other.Capacity();
        begin_ = new int[capacity];
        end_ = std::copy(other.begin_, other.end_, begin_);
        capacity_ = begin_ + capacity;
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& other) {
        if (&other == this) {
            return *this;
        }

        if (begin_) {
            delete[] begin_;
        }
        
        begin_ = other.begin_;
        end_ = other.end_;
        capacity_ = other.capacity_;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.capacity_ = nullptr;
        return *this;
    }

    int& operator[](size_t idx) {
        return begin_[idx];
    }

    const int& operator[](size_t idx) const {
        return begin_[idx];
    }

    void Swap(SimpleVector& other);
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;
    const int* Data() const;
    const int* Begin() const;
    const int* End() const;
    void PushBack(int value);
    void PopBack();
    int* Insert(size_t pos, int value);
    int* Insert(const int* elem, int value);
    int* Erase(size_t pos);
    int* Erase(const int* value);
    void Clear();
    void Resize(size_t size, int value);    
    void Reserve(size_t capacity);
    
private:
    int* begin_ = nullptr;
    int* end_ = nullptr;
    int* capacity_ = nullptr;

    void ChangeCapacity(size_t capacity, int value, bool init_with_value);
};

// Тут подошл бы обычный InreaseCapacity, который был бы проще, но меня переклинило
// и я вместо ТЗ смотрел на описание реализации std::vector, думая, что нужно делать
// shrink_to_fit
void SimpleVector::ChangeCapacity(size_t capacity, int value = 0, bool init_with_value = false) {
    size_t size = std::min(Size(), capacity);
    int* newSimpleVector = new int[capacity];

    if (begin_) {
        end_ = std::copy(begin_, begin_ + size, newSimpleVector);
        delete[] begin_;
    }
    
    begin_ = newSimpleVector;
    end_ = begin_ + size;
    capacity_ = begin_ + capacity;

    if (init_with_value && capacity > size) {
        std::fill(end_, capacity_, value);
        end_ = capacity_;
    }
}

bool operator==(const SimpleVector& lhs, const SimpleVector& rhs) {
    if (lhs.Size() != rhs.Size()) {
        return false;
    }

    return std::equal(lhs.Begin(), lhs.End(), rhs.Begin());
}

bool operator!=(const SimpleVector& lhs, const SimpleVector& rhs) {
    return !(lhs == rhs);
}

void SimpleVector::Swap(SimpleVector& other) {
    // Запрета на std::swap нет, используем >:)
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(capacity_, other.capacity_);
}

size_t SimpleVector::Size() const noexcept {
    return end_ - begin_;
}

size_t SimpleVector::Capacity() const noexcept {
    return capacity_ - begin_;
}

bool SimpleVector::Empty() const noexcept {
    return end_ == begin_ ? true : false;
}

const int* SimpleVector::Data() const {
    return begin_;
}

const int* SimpleVector::Begin() const {
    return begin_;
}

const int* SimpleVector::End() const {
    return end_;
}

void SimpleVector::PushBack(int value) {
    if (end_ != capacity_) {
        *end_ = value;
        ++end_;
        return;
    }

    if (Empty()) {
        ChangeCapacity(1, value, true);
        return;
    }

    ChangeCapacity(Capacity() * 2);

    *end_ = value;
    ++end_;
}

void SimpleVector::PopBack() {
    if (end_ != begin_) {
        --end_;
    }
}

int* SimpleVector::Insert(size_t pos, int value) {
    if (pos > Size()) {
        return end_;
    }
    
    if (begin_ + pos == end_) {
        PushBack(value);
        return end_;
    }

    if (end_ == capacity_) {
        ChangeCapacity(Capacity() * 2);
    }

    std::copy_backward(begin_ + pos, end_, end_ + 1);
    begin_[pos] = value;
    ++end_;
    return begin_ + pos;    
}

int* SimpleVector::Insert(const int* elem, int value) {
    if (!elem) {
        return end_;
    }
    
    return Insert(elem - begin_, value);    
}

int* SimpleVector::Erase(size_t pos) {
    if (pos >= Size()) {
        return end_;
    }    

    std::copy(begin_ + pos + 1, end_, begin_ + pos);
    --end_;
    return begin_ + pos;    
}

int* SimpleVector::Erase(const int* elem) {
    if (!elem) {
        return end_;
    }

    return Erase(elem - begin_);
}

void SimpleVector::Clear() {
    end_ = begin_;
}

void SimpleVector::Resize(size_t size, int value = 0) {
    if (size == Size()) {
        return; 
    }

    if (size < Size()) {
        end_ = begin_ + size;
        return;
    }

    ChangeCapacity(size, value, true);
}

void SimpleVector::Reserve(size_t capacity) {
    if (capacity <= Capacity()) {
        return;
    }

    ChangeCapacity(capacity);
}

auto begin(const SimpleVector& sVect) {
    return sVect.Begin();
}

auto end(const SimpleVector& sVect) {
    return sVect.End();
}

void swap(SimpleVector& sVect1, SimpleVector& sVect2) {
    sVect1.Swap(sVect2);
}

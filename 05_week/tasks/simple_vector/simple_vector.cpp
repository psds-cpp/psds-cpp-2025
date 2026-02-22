#include <initializer_list>

class SimpleVector {
public:
    const int* begin() const;
    const int* end() const;
    int* begin();
    int* end();
    SimpleVector() = default;
    SimpleVector(size_t size, int value = 0);
    SimpleVector(std::initializer_list<int> list);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other);
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other);
    ~SimpleVector();
    void Swap(SimpleVector& other);
    int& operator[](size_t i);
    const int& operator[](size_t i) const;
    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    const int* Data() const;
    void PushBack(int number);
    void PopBack();
    int* Insert(const int* position, int number);
    int* Erase(const int* position);
    void Clear();
    void Resize(size_t size, int value = 0);
    void Reserve(size_t new_capacity);
    bool operator==(const SimpleVector& other) const;
    bool operator!=(const SimpleVector& other) const;
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
const int* SimpleVector::begin() const {
    return data_;
}
const int* SimpleVector::end() const {
    return data_ + size_;
}
int* SimpleVector::begin() {
    return data_;
}
int* SimpleVector::end() {
    return data_ + size_;
}
SimpleVector::SimpleVector(size_t size,int value) :
    size_(size),
    capacity_(size) {
    data_ = new int[size_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}
SimpleVector::SimpleVector(std::initializer_list<int> list) {
    size_ = list.size();
    capacity_ = list.size();
    data_ = new int[list.size()];
    size_t i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        data_[i++] = *it;
    }
}
SimpleVector::SimpleVector(const SimpleVector& other) :
    size_(other.size_),
    capacity_(other.capacity_) {
    data_ = new int[size_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[size_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}
SimpleVector::SimpleVector(SimpleVector&& other) :
    data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}
SimpleVector& SimpleVector::operator=(SimpleVector&& other) {
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
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}
void SimpleVector::Swap(SimpleVector& other) {
    if (this != &other) {
        SimpleVector buffer = std::move(*this);
        (*this) = std::move(other);
        other = std::move(buffer);
    }
}
int& SimpleVector::operator[](size_t i) {
    return const_cast<int&>(static_cast<const SimpleVector&>(*this)[i]);
}
const int& SimpleVector::operator[](size_t i) const {
    return (i < size_) ? data_[i] : data_[size_];
}
size_t SimpleVector::Size() const {
    return size_;
}
size_t SimpleVector::Capacity() const {
    return capacity_;
}
bool SimpleVector::Empty() const {
    return (size_ == 0);
}
const int* SimpleVector::Data() const {
    return data_;
}
void SimpleVector::PushBack(int number) {
    if (capacity_ <= size_) { // Если вместимости не хватает расширяем память
        capacity_ = (capacity_ == 0) ? 1 : (capacity_ * 2);
        int* new_data = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) { // КОпируем старые элементы
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    data_[size_] = number;
    ++size_;
}
void SimpleVector::PopBack() {
    if (size_ != 0) {
        --size_;
    }
}
int* SimpleVector::Insert(const int* position, int number) {
    if (position == nullptr) return end();
    size_t index = position - begin();
    if (index > size_) return end(); // Возвращаем конец при некорректном индексе
    if (capacity_ <= size_) {
        capacity_ = (capacity_ == 0) ? 1 : (capacity_ * 2);
        int* new_data = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = number;
    ++size_;
    return data_ + index;
}
int* SimpleVector::Erase(const int* position) {
    if (position == nullptr) return end();
    size_t index = position - begin();
    if (index >= size_) return end();
    for (size_t i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
    return (index < size_) ? (data_ + index) : end();
}
void SimpleVector::Clear() {
    size_ = 0;
}
void SimpleVector::Resize(size_t size, int value) {
    if (size > capacity_) { // Если вместимости не хватает - расширяем память
        capacity_ = size;
        int* new_data = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    for (size_t i = size_; i < size; ++i) { // Добавляем новые элементы если size > size_
        data_[i] = value;
    }
    size_ = size; // Обновляем размер
}
void SimpleVector::Reserve(size_t new_capacity) {
    if (capacity_ < new_capacity) {
        capacity_ = new_capacity;
        int* new_data = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) { // КОпируем старые элементы
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
}
bool SimpleVector::operator==(const SimpleVector& other) const {
    if (size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}
bool SimpleVector::operator!=(const SimpleVector& other) const {
    return !((*this) == other);
}
void swap(SimpleVector& lhs, SimpleVector& rhs) {
    lhs.Swap(rhs);
}

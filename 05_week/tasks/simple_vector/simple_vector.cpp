#include <algorithm>
#include <cstddef>
#include <cstring>
#include <initializer_list>

class SimpleVector {
public:
    // Конструкторы (объявления)
    SimpleVector();
    SimpleVector(size_t size);
    SimpleVector(size_t size, int value);
    SimpleVector(std::initializer_list<int> arr);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    ~SimpleVector();

    // Методы (объявления)
    void Swap(SimpleVector& other) noexcept;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    const int* Data() const;
    void PushBack(int value);
    void PopBack();
    int* Insert(size_t index, int value);
    int* Insert(const int* ptr, int value);
    int* Erase(size_t index);
    int* Erase(const int* ptr);
    void Clear();
    void Resize(size_t size, int value = 0);
    void Reserve(size_t capacity);
    int* begin();
    int* end();
    const int* begin() const;
    const int* end() const;

    // Операторы (объявления)
    bool operator==(const SimpleVector& other) const;
    bool operator!=(const SimpleVector& other) const;

private:
    int* data;
    size_t size;
    size_t capacity;
};

// Конструкторы (реализации)
SimpleVector::SimpleVector() : data(nullptr), size(0), capacity(0) {}
SimpleVector::SimpleVector(size_t size) : SimpleVector(size, 0) {}
SimpleVector::SimpleVector(size_t size, int value) : data(new int[size]), size(size), capacity(size) {
    std::fill(data, data + size, value);
}
SimpleVector::SimpleVector(std::initializer_list<int> arr) : size(arr.size()), capacity(arr.size()) {
    data = new int[capacity];
    std::copy(arr.begin(), arr.end(), data);
}
SimpleVector::SimpleVector(const SimpleVector& other) : size(other.size), capacity(other.capacity) {
    data = new int[capacity];
    std::copy(other.begin(), other.end(), data);
}
SimpleVector::SimpleVector(SimpleVector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        SimpleVector temp(other);
        Swap(temp);
    }
    return *this;
}
SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}
SimpleVector::~SimpleVector() {
    delete[] data;
    size = 0;
    capacity = 0;
}

// Методы (реализации)
void SimpleVector::Swap(SimpleVector& other) noexcept {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}
int& SimpleVector::operator[](size_t index) {
    return data[index];
}
const int& SimpleVector::operator[](size_t index) const {
    return data[index];
}
size_t SimpleVector::Size() const {
    return size;
}
size_t SimpleVector::Capacity() const {
    return capacity;
}
bool SimpleVector::Empty() const {
    return size == 0;
}
const int* SimpleVector::Data() const {
    return data;
}
void SimpleVector::PushBack(int value) {
    if (size == capacity) {
        Reserve(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

void SimpleVector::PopBack() {
    if (size > 0) {
        --size;
    }
}
int* SimpleVector::Insert(const int* ptr, int value) {
    if (ptr < begin() || ptr > end()) {
        return end();
    }
    size_t offset = ptr - begin();
    if (size == capacity) {
        Reserve(capacity == 0 ? 1 : capacity * 2);
    }
    int* target = data + offset;
    std::copy_backward(target, data + size, data + size + 1);
    *target = value;
    ++size;
    return target;
}
int* SimpleVector::Insert(size_t index, int value) {
    return SimpleVector::Insert(data + index, value);
}
int* SimpleVector::Erase(const int* pos) {
    if (pos < begin() || pos >= end()) {
        return end();
    }
    size_t offset = pos - begin();
    int* target = data + offset;
    std::copy(target + 1, data + size, target);
    --size;
    return target;
}
int* SimpleVector::Erase(size_t index) {
    return SimpleVector::Erase(data + index);
}
void SimpleVector::Clear() {
    size = 0;
}
void SimpleVector::Resize(size_t new_size, int value) {
    if (new_size < size) {
        size = new_size;
    } 
    else if (new_size > size) {
        Reserve(new_size);
        std::fill(data + size, data + new_size, value);
        size = new_size;
    }
}
void SimpleVector::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity) {
        return;
    }
    int* new_data = new int[new_capacity];
    if (data) {
        std::copy(data, data + size, new_data);
        delete[] data;
    }
    data = new_data;
    capacity = new_capacity;
}
int* SimpleVector::begin() {
    return data;
}
int* SimpleVector::end() {
    return data + size;
}
const int* SimpleVector::begin() const {
    return data;
}
const int* SimpleVector::end() const {
    return data + size;
}

// Операторы (реализации)
bool SimpleVector::operator==(const SimpleVector& other) const {
    if (size != other.size) {
        return false;
    }
    return std::equal(begin(), end(), other.begin());
}

bool SimpleVector::operator!=(const SimpleVector& other) const {
    return !(*this == other);
}

// Внешняя функция swap для STL
void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}
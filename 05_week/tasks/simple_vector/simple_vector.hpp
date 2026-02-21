#pragma once

#include <initializer_list>
#include <algorithm>

class SimpleVector {
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    SimpleVector() = default;
    SimpleVector(size_t size);
    SimpleVector(size_t size, int value);
    SimpleVector(std::initializer_list<int> list);

    SimpleVector(const SimpleVector& other);
    SimpleVector& operator=(const SimpleVector& other);

    SimpleVector(SimpleVector&& other) noexcept;
    SimpleVector& operator=(SimpleVector&& other) noexcept ;

    ~SimpleVector();

    void Swap(SimpleVector& other);
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    int* Data();
    const int* Data() const;
    void PushBack(int value);
    void PopBack();
    int* Insert(const int* pos, int value);
    int* Erase(const int* pos);
    void Clear();
    void Resize(size_t new_size, int value = 0);
    void Reserve(size_t new_capacity);

    int* begin() const;
    int* end() const;

    bool operator==(const SimpleVector& other) const;
    bool operator!=(const SimpleVector& other) const;
};

void swap(SimpleVector& first, SimpleVector& second) noexcept;

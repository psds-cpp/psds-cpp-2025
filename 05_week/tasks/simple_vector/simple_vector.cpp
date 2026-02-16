#include <iostream>
#include <cstring>

class SimpleVector {
public:
    SimpleVector();
    SimpleVector(size_t size);
    SimpleVector(size_t size, int num);
    SimpleVector(const std::initializer_list<int>& lst);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;
    ~SimpleVector();

    int& operator[](size_t idx) const;
    bool operator==(const SimpleVector& right) const noexcept;
    bool operator!=(const SimpleVector& right) const noexcept;
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    
    void Swap(SimpleVector& right) noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;
    const int* Data() const noexcept;
    void PushBack(int input);
    void PopBack();
    void Clear() noexcept;
    void Resize(size_t new_size, int num);
    void Reserve(size_t new_cap);
    int* Insert(size_t idx, int num);
    int* Insert(const int* pos, int num);
    int* Erase(size_t idx);
    int* Erase(const int* pos);

    int* begin() const;
    int* end() const;

private:
    size_t m_capacity;
    size_t m_size;
    int* m_data;
};

SimpleVector::SimpleVector() :
    m_capacity(0), 
    m_size(0),
    m_data(new int[]{}){} 

SimpleVector::SimpleVector(size_t size) : 
    m_capacity(size), 
    m_size(size),
    m_data(new int[size]{}) {}

SimpleVector::SimpleVector(size_t size, int num) :
    SimpleVector(size) {
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = num;
    }
}

SimpleVector::SimpleVector(const std::initializer_list<int>& lst) :
    m_capacity(lst.size()),
    m_size(lst.size()),
    m_data(new int[m_size]) {
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = *(lst.begin() + i);
    }
}

SimpleVector::SimpleVector(const SimpleVector& other) :
    m_capacity(other.m_capacity),
    m_size(other.m_size), 
    m_data(new int[m_size]) {
    std::memcpy(m_data, other.m_data, m_size * sizeof(int));
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {     
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        delete[] m_data;
        m_data = new int[m_size];
        std::memcpy(m_data, other.m_data, m_size * sizeof(int));
    }
    return *this;
}

SimpleVector::SimpleVector(SimpleVector&& other) noexcept :
    m_capacity(other.m_capacity),
    m_size(other.m_size), 
    m_data(other.m_data) {
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_data = nullptr;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other){   
        m_capacity = other.m_capacity;
        m_size = other.m_size; 
        delete[] m_data;
        m_data = other.m_data;
        other.m_capacity = 0;
        other.m_size = 0;
        other.m_data = nullptr;
    }
    return *this;
}

SimpleVector::~SimpleVector() {
    delete[] m_data;
    m_data = nullptr;
}

int& SimpleVector::operator[](size_t idx) const {
    return *(m_data + idx);
}

bool SimpleVector::operator==(const SimpleVector& right) const noexcept {
    if (this == &right) return true;

    if (m_size == right.m_size) {
        for (size_t i = 0; i < m_size; ++i) {
            if ((*this)[i] != right[i]) return false;
        }
        return true;
    }
    return false;
}

bool SimpleVector::operator!=(const SimpleVector& right) const noexcept {
    return !(*this == right);
}

void SimpleVector::Swap(SimpleVector& right) noexcept {
    if (this != &right) {
        std::swap(m_capacity, right.m_capacity);
        std::swap(m_size, right.m_size);
        std::swap(m_data, right.m_data);
    }
}

size_t SimpleVector::Size() const noexcept {
    return m_size;
}

size_t SimpleVector::Capacity() const noexcept {
    return m_capacity;
}

bool SimpleVector::Empty() const noexcept {
    return m_size == 0;
}

const int* SimpleVector::Data() const noexcept {
    return m_data;
}

void SimpleVector::PushBack(int num) {
    if (m_capacity == m_size) {
        size_t new_cap = 2 * m_capacity;
        if (new_cap == 0) ++new_cap; 
        Reserve(new_cap);
    }
    m_data[m_size++] = num;
}

void SimpleVector::PopBack() {
    if (!Empty()) --m_size; 
}

void SimpleVector::Clear() noexcept {
    m_size = 0;
}

void SimpleVector::Reserve(size_t new_cap) {
    if (new_cap > m_capacity) {
        m_capacity = new_cap;
        int* new_address = new int[m_capacity];
        if (m_data != nullptr) {
            std::memcpy(new_address, m_data, m_size * sizeof(int));
            delete[] m_data;
        }
        m_data = new_address;
    }    
}

void SimpleVector::Resize(size_t new_size, int num = 0) {
    if (new_size > m_capacity) {
        Reserve(new_size);
        for(size_t i = m_size; i < new_size; ++i) {
            m_data[i] = num;
        }
    }
    m_size = new_size;
}

int* SimpleVector::Insert(size_t idx, int num) {
    if (idx > m_size) return &m_data[m_size];
    if (m_size == m_capacity) {
        size_t new_cap = 2 * m_capacity;
        if (new_cap == 0) ++new_cap;
        Reserve(new_cap);
    }
    for (size_t i = m_size; i > idx; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[idx] = num;
    ++m_size;
    return &m_data[idx];
}

int* SimpleVector::Insert(const int* pos, int num) {
    size_t idx = std::distance(Data(), pos);
    return Insert(idx, num);
}

int* SimpleVector::Erase(size_t idx) {
    if (idx >= m_size) return &m_data[m_size];
    for (size_t i = idx; i < m_size - 1; ++i) {
        std::swap(m_data[i], m_data[i + 1]);
    }
    PopBack();
    return &m_data[idx];
}

int* SimpleVector::Erase(const int* pos) {
    size_t idx = std::distance(Data(), pos);
    return Erase(idx);
}

int* SimpleVector::begin() const {
    return m_data;
}

int* SimpleVector::end() const {
    return m_data + m_size;
}

void swap(SimpleVector& lft, SimpleVector& rht) {
    lft.Swap(rht);
}



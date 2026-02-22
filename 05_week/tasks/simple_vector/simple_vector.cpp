#include <utility>
#include <algorithm>
#include <stddef.h>

class SimpleVector {
public:
    ~SimpleVector();
    SimpleVector() = default;
    SimpleVector(size_t size, int fill_value = 0);
    SimpleVector(const std::initializer_list<int>& ilist);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    int& operator[](size_t pos);
    int operator[](size_t pos) const;
    bool operator==(const SimpleVector& other) const;
    bool operator!=(const SimpleVector& other) const;
    bool operator>=(const SimpleVector& other) const;
    bool operator>(const SimpleVector& other) const;
    bool operator<=(const SimpleVector& other) const;
    bool operator<(const SimpleVector& other) const;
    void Swap(SimpleVector& other);
    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    const int* Data() const;
    void PushBack(int x);
    void PopBack();
    int* Insert(size_t dest, int src);
    int* Insert(const int* dest_ptr, int src);
    int* Erase(size_t dest);
    int* Erase(const int* dest_ptr);
    void Clear();
    void Resize(size_t size, int fill_value = 0);
    void Reserve(size_t capacity);
    int* begin();
    const int* begin() const;
    int* end();
    const int* end() const;
private:
    void m_copy(const SimpleVector& other);
    void m_move(SimpleVector&& other);
    void m_checkCapacity(size_t required);
    void m_reallocateData(size_t new_capacity);
    void m_incrementSize();
    size_t m_size = 0;
    size_t m_capacity = 0;
    int* m_data = nullptr;
};

void SimpleVector::m_copy(const SimpleVector& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new int[m_capacity];
    std::copy(other.begin(), other.end(), m_data);
}

void SimpleVector::m_move(SimpleVector&& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

void SimpleVector::m_reallocateData(size_t new_capacity) {
    int* temp = new int[new_capacity] ();
    std::copy(begin(), end(), temp);
    delete[] m_data;
    m_data = temp;
    m_capacity = new_capacity;
}

void SimpleVector::m_checkCapacity(size_t required) {
    if (required <= m_capacity) { return; }
    if (m_capacity == 0) { m_capacity = 1; }
    else { m_capacity *= 2; }
}

void SimpleVector::m_incrementSize() {
    m_checkCapacity(m_size + 1);
    m_reallocateData(m_capacity);
    ++m_size;
}

SimpleVector::~SimpleVector() {
    delete[] m_data;
}

SimpleVector::SimpleVector(size_t size, int fill_value) : m_size(size), m_capacity(size), m_data(new int[size] ()) {
    std::fill(begin(), end(), fill_value);
}

SimpleVector::SimpleVector(const std::initializer_list<int>& ilist)
: m_size(ilist.size()), m_capacity(m_size), m_data(new int[m_size] ()) {
    std::copy(ilist.begin(), ilist.end(), m_data);
}

SimpleVector::SimpleVector(const SimpleVector& other) {
    m_copy(other);
}

SimpleVector::SimpleVector(SimpleVector&& other) noexcept {
    m_move(std::move(other));
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this == &other) { return *this; }
    delete[] m_data;
    m_copy(other);
    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this == &other) { return *this; }
    delete[] m_data;
    m_move(std::move(other));
    return *this;
}

int& SimpleVector::operator[](size_t pos) {
    return m_data[pos];
}

int SimpleVector::operator[](size_t pos) const {
    return m_data[pos];
}

bool SimpleVector::operator==(const SimpleVector& other) const {
    if (this == &other) { return true; }
    else if (Size() != other.Size()) { return false; }
    return std::equal(begin(), end(), other.begin(), other.end());
}

bool SimpleVector::operator!=(const SimpleVector& other) const {
    return !(*this == other);
}

bool SimpleVector::operator<(const SimpleVector& other) const {
    return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
}

bool SimpleVector::operator<=(const SimpleVector& other) const {
    return !(other < *this);
}

bool SimpleVector::operator>(const SimpleVector& other) const {
    return other < *this;
}

bool SimpleVector::operator>=(const SimpleVector& other) const {
    return !(*this < other);
}

void SimpleVector::Swap(SimpleVector& other) {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
}

size_t SimpleVector::Size() const {
    return m_size;
}

size_t SimpleVector::Capacity() const {
    return m_capacity;
}

bool SimpleVector::Empty() const {
    return m_size == 0;
}

const int* SimpleVector::Data() const {
    return m_data;
}

void SimpleVector::PushBack(int x) {
    m_incrementSize();
    m_data[m_size - 1] = x;
}

void SimpleVector::PopBack() {
    if (Empty()) { return; }
    m_size -= 1;
}

int* SimpleVector::Insert(size_t dest, int src) {
    if (dest > m_size) { return end(); }
    m_incrementSize();
    for (size_t i = m_size - 1; i > dest; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[dest] = src;
    return m_data + dest;
}

int* SimpleVector::Insert(const int* dest_ptr, int src) {
    size_t dest = dest_ptr - begin();
    return Insert(dest, src);
}

int* SimpleVector::Erase(size_t dest) {
    if (Empty() || dest >= m_size) { return end(); }
    for (size_t i = dest; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
    return begin() + dest;
}

int* SimpleVector::Erase(const int* dest_ptr) {
    size_t dest = dest_ptr - begin();
    return Erase(dest);
}

void SimpleVector::Clear() {
    if (Empty()) { return; }
    m_size = 0;
}

void SimpleVector::Resize(size_t size, int fill_value) {
    if (m_size == size) { return; }
    if (m_size > size) {
        m_size = size;
        return;
    }
    if (size > m_capacity) {
        m_reallocateData(size);
    }
    std::fill(begin() + m_size, begin() + size, fill_value);
    m_size = size;
}

void SimpleVector::Reserve(size_t capacity) {
    if (m_capacity >= capacity) { return; }
    m_reallocateData(capacity);
}

int* SimpleVector::begin() {
    return m_data;
}

const int* SimpleVector::begin() const {
    return m_data;
}

int* SimpleVector::end() {
    return m_data + m_size;
}

const int* SimpleVector::end() const {
    return m_data + m_size;
}

void swap(SimpleVector& lhs, SimpleVector& rhs) {
    lhs.Swap(rhs);
}

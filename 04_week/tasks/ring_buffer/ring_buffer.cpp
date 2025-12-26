#include <vector>
#include <stddef.h>
#include <utility>


class RingBuffer {
public:
    RingBuffer(const size_t size);
    RingBuffer(const size_t size, const int val);
    RingBuffer(const std::initializer_list<int> ilist);
    RingBuffer(const RingBuffer& other);
    void Push(const int item);
    bool TryPush(const int item);
    void Pop();
    bool TryPop(int& pop_value);
    int& Front();
    int Front() const;
    int& Back();
    int Back() const;
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(const size_t size);
    std::vector<int> Vector() const;
    int& operator[](const size_t idx);
    int operator[](const size_t idx) const;
    RingBuffer& operator=(const RingBuffer& other);
private:
    int m_null_value = 0;
    size_t m_begin = 0;
    size_t m_end = 0;
    size_t m_size = 0;
    std::vector<int> m_buffer{};
    size_t m_check_zero_size(const size_t size) const;
    void m_pop_core();
    void m_push_back_core(const int item);
    void m_copy_core(const RingBuffer& other);
    int m_last() const;
};

size_t RingBuffer::m_check_zero_size(const size_t size) const {
    return (size == 0) ? 1 : size;
}

int RingBuffer::m_last() const {
    return (m_end == 0) ? Capacity() - 1 : m_end - 1;
}

RingBuffer::RingBuffer(size_t size) {
    m_buffer.reserve(m_check_zero_size(size));
}

RingBuffer::RingBuffer(const size_t size, const int val) {
    m_buffer.reserve(m_check_zero_size(size));
    for (size_t i = 0; i < Capacity(); ++i) {
        m_buffer.push_back(val);
    }
    m_size = m_buffer.size();
    m_end = m_buffer.size();
}

RingBuffer::RingBuffer(const std::initializer_list<int> ilist) : m_buffer(ilist) {
    if (m_buffer.empty()) {
        m_buffer.reserve(1);
    }
    m_size = m_buffer.size();
    m_end = m_buffer.size();
}

void RingBuffer::m_copy_core(const RingBuffer& other) {
    m_begin = other.m_begin;
    m_end = other.m_end;
    m_size = other.m_size;
    m_buffer = other.m_buffer;
    m_buffer.reserve(other.Capacity());
}

RingBuffer::RingBuffer(const RingBuffer& other) {
    m_copy_core(other);
}

inline void RingBuffer::m_push_back_core(const int item) {
    if (m_buffer.size() == Capacity()) {
        m_buffer[m_end] = item;
        if (m_size != m_buffer.size()) {
            ++m_size;
        }
        else {
            m_begin = (m_begin + 1) % Capacity(); 
        }
    }
    else {
        m_buffer.push_back(item);
        ++m_size;
    }
    m_end = (m_end + 1) % Capacity();
}

void RingBuffer::Push(const int item) {
    m_push_back_core(item);
}

bool RingBuffer::TryPush(const int item) {
    if (Full()) {
        return false;
    }
    else {
        m_push_back_core(item);
        return true;
    }
}

inline void RingBuffer::m_pop_core() {
    m_begin = (m_begin + 1) % Capacity();
    --m_size;
}

void RingBuffer::Pop() {
    if (Size() == 0)
        return;

    m_pop_core();
}

bool RingBuffer::TryPop(int& pop_value) {
    if (Size() == 0)
        return false;

    pop_value = m_buffer[m_begin];

    m_pop_core();

    return true;
}

int& RingBuffer::Front() {
    if (Size() == 0)
        return m_null_value;

    return m_buffer[m_last()];
}

int RingBuffer::Front() const {
    if (Size() == 0)
        return m_null_value;

    return m_buffer[m_last()];
}

int& RingBuffer::Back() {
    if (Size() == 0)
        return m_null_value;

    return m_buffer[m_begin];
}

int RingBuffer::Back() const {
    if (Size() == 0)
        return m_null_value;

    return m_buffer[m_begin];
}

bool RingBuffer::Empty() const {
    return Size() == 0;
}

bool RingBuffer::Full() const {
    return Capacity() == Size();
}

size_t RingBuffer::Size() const {
    return m_size;
}

size_t RingBuffer::Capacity() const {
    return m_buffer.capacity();
}

void RingBuffer::Clear() {
    m_buffer.clear();
    m_size = 0;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> vector_buffer;
    vector_buffer.reserve(Size());

    if (m_end <= m_begin) {
        size_t left_size = m_end;
        size_t right_size = Size() - m_begin;

        size_t i = m_begin;

        while (i - m_begin < right_size) {
            vector_buffer.push_back(m_buffer[i++]);
        }

        i = 0;
        while (i < left_size) {
            vector_buffer.push_back(m_buffer[i++]);
        }
    }
    else {
        for (size_t i = 0; i < Size(); ++i) {
            vector_buffer.push_back(m_buffer[i]);
        }
    }

    return vector_buffer;
}

void RingBuffer::Resize(const size_t size) {
    size_t new_size = m_check_zero_size(size);

    if (new_size == Capacity()) {
        return;
    }

    std::vector<int> new_buffer;
    new_buffer.reserve(new_size);

    std::vector<int> vector_buffer = Vector();

    for (
        size_t i = (Size() > new_size) ? Size() - new_size : 0;
        new_buffer.size() != new_buffer.capacity() && i < Size();
        ++i
    ) {
        new_buffer.push_back(vector_buffer[i]);
    }

    m_buffer = std::move(new_buffer);
    m_begin = 0;
    m_size = m_buffer.size();
    m_end = Size();
}

int& RingBuffer::operator[](const size_t idx) {
    return m_buffer[(m_begin + idx) % Capacity()];
}

int RingBuffer::operator[](const size_t idx) const {
    return m_buffer[(m_begin + idx) % Capacity()];
}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (this == &other) {
        return *this;
    }

    m_copy_core(other);
    return *this;
}

 #include <cmath>
#include <cstddef>
#include <vector> 

class RingBuffer {
public:
    // Конструкторы (объявления)
    RingBuffer(size_t n);
    RingBuffer(size_t n, int val);
    RingBuffer(std::initializer_list<int> list);

    // Методы (объявления)
    bool Empty() const; 
    bool Full() const;  
    size_t Size() const;
    size_t Capacity() const;
    void Push(int val);
    bool TryPush(int val);
    void Pop();
    bool TryPop(int& val);
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    void Clear();
    void Resize(size_t n);
    std::vector<int> Vector() const;

    // Операторы (объявсления)
    int& operator[](size_t ind);
    const int& operator[](size_t ind) const;

private:
    std::vector<int> buf;
    size_t begin = 0;
    size_t curSize = 0;
};

// Конструкторы (реализации)

RingBuffer::RingBuffer(size_t n) : buf(std::max<size_t>(1, n)), begin(0), curSize(0) {}

RingBuffer::RingBuffer(size_t n, int val) : buf(std::max<size_t>(1, n), val) {
    curSize = buf.size();
    begin = 0;
}

RingBuffer::RingBuffer(std::initializer_list<int> list) : buf(list), begin(0), curSize(list.size()) {
    if (buf.empty())
        buf.resize(1);
}

// Методы (реализации)

size_t RingBuffer::Size() const {
    return curSize;
}

size_t RingBuffer::Capacity() const {
    return buf.size();
}

bool RingBuffer::Empty() const {
    return curSize == 0;
}

bool RingBuffer::Full() const {
    return curSize == buf.size();
}

void RingBuffer::Push(int val) {
    if (Full()) {
        buf[begin] = val;
        begin = (begin + 1) % buf.size();
    } else {
        buf[(begin + curSize) % buf.size()] = val;
        curSize++;
    }
}

bool RingBuffer::TryPush(int val) {
    if (Full())
        return false;
    Push(val);
    return true;
}

void RingBuffer::Pop() {
    if (!Empty()) {
        begin = (begin + 1) % buf.size();
        curSize--;
    }
}

bool RingBuffer::TryPop(int& val) {
    if (Empty())
        return false;
    val = Back();
    Pop();
    return true;
}

int& RingBuffer::Front() {
    return buf[(begin + curSize - 1) % buf.size()];
}

const int& RingBuffer::Front() const {
    return buf[(begin + curSize - 1) % buf.size()];
}

int& RingBuffer::Back() {
    return buf[begin];
}

const int& RingBuffer::Back() const {
    return buf[begin];
}

void RingBuffer::Clear() {
    begin = 0;
    curSize = 0;
}

void RingBuffer::Resize(size_t n) {
    if (n == 0)
        n = 1;

    std::vector<int> newBuf(n);
    size_t cntCopy = std::min(curSize, n);
    size_t start = curSize > n ? (curSize - n) : 0;
    
    for (size_t i = 0; i < cntCopy; ++i)
        newBuf[i] = (*this)[start + i];
    
    buf = std::move(newBuf);
    begin = 0;
    curSize = cntCopy;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> res(curSize);

    for (size_t i = 0; i < curSize; ++i)
        res[i] = (*this)[i];

    return res;
}

// Операторы (реализации)

int& RingBuffer::operator[](size_t ind) {
    return buf[(begin + ind) % buf.size()];
}

const int& RingBuffer::operator[](size_t ind) const {
    return buf[(begin + ind) % buf.size()];
}
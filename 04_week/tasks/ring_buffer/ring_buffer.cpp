#include <vector>
#include <stdexcept> //Осваиваю throw вместо простого return что-то
/*
Необходимо реализовать кольцевой буфер фиксированного размера, построенный на контейнере вектора интов
//Нельзя `std::queue`, `std::deque`, `std::list`
При добавлении в заполненный буфер перезаписывается самый старый элемент.
Может хранить либо позиции начала, конца и размер буфера, либо указатели на 
соответствующие позиции.
//Нельзя сконструировать буфер нулевого размера, минимально 1
//Методы определяем вне класса, исключение - приватные вспомогательные методы.
- Конструктор от вместимости буфера
- Конструктор от вместимости буфера и начального значения, заполняет весь буфер
- Конструктор от `std::initializer_list`, вместимость соответствует размеру контейнера.
//Исходя из прошлых ошибок по оформлению теперь использую name_ для обозначения переменных класса, для явности пренадлежности
// Постарался побольше использовать тернарные операторы так где это оправданно.
*/

class RingBuffer {
public:
    explicit RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int initialValue);
    RingBuffer(std::initializer_list<int> init);
    
    void Push(int value);
    bool TryPush(int value);
    
    bool Pop();
    bool TryPop(int& value);
    
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    
    void Clear();
    void Resize(size_t newCapacity);
        
    std::vector<int> Vector() const;
        
    bool operator==(const RingBuffer& other) const;
    bool operator!=(const RingBuffer& other) const;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;   

private:
    std::vector<int> buffer_;
    size_t oldestElement_ = 0;
    size_t indexNextElem_ = 0;
    size_t currentCountElem_ = 0;
    //Для удобства добавил следующие конструкции:
    size_t NextIndex(size_t index) const {
        return (index + 1) % buffer_.capacity();
    }
    
    size_t PhysicalIndex(size_t logical) const {
        return (oldestElement_ + logical) % buffer_.capacity();
        }

    void ValidateIndex(size_t index) const {
        if (index >= currentCountElem_) throw std::out_of_range("out of range");
    }
        
    void ValidateNotEmpty() const {
    if (Empty()) throw std::logic_error("Buff is empty");
    }
};

RingBuffer::RingBuffer(size_t capacity) {
    capacity = capacity ? capacity : 1; // минимум 1 по тз
    buffer_.reserve(capacity);
    buffer_.resize(capacity);
    oldestElement_ = 0;
    indexNextElem_ = 0;
    currentCountElem_ = 0;
}

RingBuffer::RingBuffer(size_t capacity, int initialValue) 
    : RingBuffer(capacity) {  //жесточайшее делегирование и лень)
    if (capacity > 0) {
        for (size_t i = 0; i < capacity; ++i) {
            Push(initialValue);
        }
    } else {
        buffer_[0] = initialValue;
        indexNextElem_ = 1 % buffer_.capacity();
        currentCountElem_ = 1;
    }
}

RingBuffer::RingBuffer(std::initializer_list<int> init) {
    size_t capacity = init.size() ? init.size() : 1;
    buffer_.reserve(capacity);
    buffer_.resize(capacity);
    oldestElement_ = 0;
    indexNextElem_ = 0;
    currentCountElem_ = 0;
    for (int value : init) Push(value); //Добавил range based, так как будто бы уютнее смотрится
}

void RingBuffer::Push(int value) {
    if (Full()) {
        buffer_[indexNextElem_] = value;
        oldestElement_ = NextIndex(oldestElement_);
        indexNextElem_ = NextIndex(indexNextElem_);
    } else {
        buffer_[indexNextElem_] = value;
        indexNextElem_ = NextIndex(indexNextElem_);
        ++currentCountElem_;
    }
}

bool RingBuffer::TryPush(int value) {
    if (Full()) return false;
    buffer_[indexNextElem_] = value;
    indexNextElem_ = NextIndex(indexNextElem_);
    ++currentCountElem_;
    return true;
}

bool RingBuffer::Pop() {
    if (Empty()) return false;
    oldestElement_ = NextIndex(oldestElement_);
    --currentCountElem_;
    return true;
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) return false;
    value = buffer_[oldestElement_];
    Pop();
    return true;
}

int& RingBuffer::operator[](size_t index) {
    ValidateIndex(index);
    return buffer_[PhysicalIndex(index)];
}

const int& RingBuffer::operator[](size_t index) const {
    ValidateIndex(index);
    return buffer_[PhysicalIndex(index)];
}

int& RingBuffer::Front() {
    ValidateNotEmpty();
    size_t frontIndex = indexNextElem_ ? indexNextElem_ - 1 : buffer_.capacity() - 1;
    return buffer_[frontIndex];
}

const int& RingBuffer::Front() const {
    ValidateNotEmpty();
    size_t frontIndex = indexNextElem_ ? indexNextElem_ - 1 : buffer_.capacity() - 1;
    return buffer_[frontIndex];
}

int& RingBuffer::Back() {
    ValidateNotEmpty();
    return buffer_[oldestElement_];
}

const int& RingBuffer::Back() const {
    ValidateNotEmpty();
    return buffer_[oldestElement_];
}

bool RingBuffer::Empty() const {
    return currentCountElem_ == 0;
}

bool RingBuffer::Full() const {
    return currentCountElem_ == buffer_.capacity();
}

size_t RingBuffer::Size() const {
    return currentCountElem_;
}

size_t RingBuffer::Capacity() const {
    return buffer_.capacity();
}

void RingBuffer::Clear() {
    oldestElement_ = indexNextElem_ = currentCountElem_ = 0;
}

void RingBuffer::Resize(size_t newCapacity) {
    newCapacity = newCapacity ? newCapacity : 1;
    if (newCapacity == buffer_.capacity()) return;
    
    size_t newCount = currentCountElem_ < newCapacity ? currentCountElem_ : newCapacity;
    std::vector<int> newBuffer = {};
    newBuffer.reserve(newCapacity);
    newBuffer.resize(newCapacity);
    
    for (size_t i = 0; i < newCount; ++i) {
        newBuffer[i] = (*this)[currentCountElem_ - newCount + i];
    }
    
    buffer_ = std::move(newBuffer);
    oldestElement_ = 0;
    indexNextElem_ = newCount % newCapacity;
    currentCountElem_ = newCount;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> result;
    result.reserve(currentCountElem_);
    for (size_t i = 0; i < currentCountElem_; ++i) result.push_back((*this)[i]);
    return result;
}

bool RingBuffer::operator==(const RingBuffer& other) const {
    if (currentCountElem_ != other.currentCountElem_ || buffer_.capacity() != other.buffer_.capacity())
        return false;
    for (size_t i = 0; i < currentCountElem_; ++i)
        if ((*this)[i] != other[i]) return false;
    return true;
}

bool RingBuffer::operator!=(const RingBuffer& other) const {
    return !(*this == other);
}
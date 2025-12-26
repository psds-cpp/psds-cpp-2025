#include <vector>



class RingBuffer {
public:

    // ---- Конструкторы -----
    explicit RingBuffer(size_t capacity); // Конструктор от емкости
    RingBuffer(size_t capacity, int initialValue);  // Конструткор от емкасти и начального значения
    RingBuffer(std::initializer_list<int> init);    // конструктор по размеру контейнера 
    
    // ---- Методы -----
    void Push(int value);
    bool TryPush(int value);
    
    bool Pop();
    bool TryPop(int& value);
    
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    bool Empty() const {return countElem == 0;}
    bool Full() const {return countElem == buf.capacity();}
    size_t Size() const{return countElem;}
    size_t Capacity() const{return buf.capacity();}
    
    void Clear() {prevElem = nextElem = countElem = 0;}
    void Resize(size_t newCapacity);
        
    std::vector<int> Vector() const;
        
    bool operator==(const RingBuffer& other) const;
    bool operator!=(const RingBuffer& other) const;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;   

private:
    std::vector<int> buf;
    size_t prevElem = 0;
    size_t nextElem = 0;
    size_t countElem = 0; // счетчик текущего элемента
    

    size_t NextIndex(size_t i) const {
        if((i + 1) >= buf.capacity())     return 0;
        return i+1;
    }


};

RingBuffer::RingBuffer(size_t capacity) {
    if(capacity == 0) capacity = 1; // Емкость 0 не должна быть 
    buf.reserve(capacity);
    buf.resize(capacity);
    prevElem = 0;
    nextElem = 0;
    countElem = 0;
}

RingBuffer::RingBuffer(size_t capacity, int initialValue) { 

    if(capacity == 0) capacity = 1; // Емкость 0 не должна быть 
    buf.reserve(capacity);
    buf.resize(capacity);
    prevElem = 0;
    nextElem = 0;
    countElem = 0;
    for (size_t i = 0; i < capacity; ++i) Push(initialValue);

}

RingBuffer::RingBuffer(std::initializer_list<int> init) {
    
    size_t capacity = init.size();
        if(capacity == 0) capacity = 1; // Емкость 0 не должна быть 
    
    buf.reserve(capacity);
    buf.resize(capacity);
    prevElem = 0;
    nextElem = 0;
    countElem = 0;
 
    for (int value : init) Push(value); 
}

void RingBuffer::Push(int value) {
    if (Full()) {
        buf[nextElem] = value;
        prevElem = NextIndex(prevElem);
        nextElem = NextIndex(nextElem);
    } else {
        buf[nextElem] = value;
        nextElem = NextIndex(nextElem);
        ++countElem;
    }
}

bool RingBuffer::TryPush(int value) {
    if (Full()) return false;
    buf[nextElem] = value;
    nextElem = NextIndex(nextElem);
    ++countElem;
    return true;
}

bool RingBuffer::Pop() {
    if (Empty()) return false;
    prevElem = NextIndex(prevElem);
    --countElem;
    return true;
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) return false;
    value = buf[prevElem];
    Pop();
    return true;
}

int& RingBuffer::operator[](size_t i) {
  if(i >= countElem)  return buf[countElem];
  return buf[((i + prevElem)%buf.capacity())];

}

const int& RingBuffer::operator[](size_t i) const {
 if(i >= countElem)  return buf[countElem];
  return buf[((i + prevElem)%buf.capacity())]; 
}

int& RingBuffer::Front() {
    if(nextElem == 0)    return buf[buf.capacity() - 1];
    return  buf[nextElem - 1];
}

const int& RingBuffer::Front() const {
    if(nextElem == 0)    return buf[buf.capacity() - 1];
    return  buf[nextElem - 1];
}

int& RingBuffer::Back() {
    return buf[prevElem];
}

const int& RingBuffer::Back() const {
    return buf[prevElem];
}

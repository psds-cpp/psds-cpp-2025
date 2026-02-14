#include <vector>
#include <initializer_list>

class RingBuffer {
public:
    RingBuffer(size_t size);
    RingBuffer(size_t size, int value);
    RingBuffer(std::initializer_list<int> init_list);
    void Push(int value);
    bool TryPush(int value);
    void Pop();
    bool TryPop(int& value);
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(size_t size);
    std::vector<int> Vector();

private:
    std::vector<int> data;
    size_t head;
    size_t tail;
    size_t elementCount = 0;
};

RingBuffer::RingBuffer(size_t size) {
    data.resize((size == 0) ? 1 : size); // Вместимость буфера != 0
    head = 0;
    tail = 0;
}

RingBuffer::RingBuffer(size_t size, int value) {
    data.resize((size == 0) ? 1 : size);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = value;
        ++elementCount;
    }
    head = 0;
    tail = (elementCount - 1);
}

RingBuffer::RingBuffer(std::initializer_list<int> init_list)
    : data(init_list) {
    if (data.empty())
        data.resize(1);
    elementCount = init_list.size();
    head = 0;
    tail = (elementCount == 0) ? 0 : (elementCount - 1);
}

bool RingBuffer::Empty() const {
    return (elementCount == 0);
}

size_t RingBuffer::Capacity() const {
    return data.size();
}

bool RingBuffer::Full() const {
    return (elementCount == data.size());
}

size_t RingBuffer::Size() const {
    return elementCount;
}

bool RingBuffer::TryPush(int value) {
    if (Full()) return false;

    if (!Empty()) {
        tail = (tail + 1) % Capacity();
    }
    data[tail] = value;
    ++elementCount;
    return true;
}

void RingBuffer::Push(int value) {
    if (!TryPush(value)) {
        tail = (tail + 1) % Capacity(); // голова упирается в хвост - нужно двигать их вместе
        head = (head + 1) % Capacity();
        data[tail] = value;
    }
}

void RingBuffer::Pop() {
    if (Empty()) return; // Вызов от пустой очереди корректная операция
    head = (head + 1) % Capacity();
    --elementCount;
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) return false;
    value = data[head];
    Pop();
    return true;
}

const int& RingBuffer::operator[](size_t index) const {
    if (index > Capacity()) return data[tail]; // При выходе за диапазон возвращает хвост? (в ТЗ нет указаний на это тсчет)
    return data[(index + head) % Capacity()];
}

int& RingBuffer::operator[](size_t index) {
    return const_cast<int&>(
        static_cast<const RingBuffer&>(*this)[index]
        );
}

const int& RingBuffer::Front() const {
    return data[tail];
}

int& RingBuffer::Front() {
    return const_cast<int&>(
        static_cast<const RingBuffer&>(*this).Front()
        );
}

const int& RingBuffer::Back() const {
    return data[head];
}

int& RingBuffer::Back() {
    return const_cast<int&>(
        static_cast<const RingBuffer&>(*this).Back()
        );
}

void RingBuffer::Clear() {
    head = 0;
    tail = 0;
    elementCount = 0;
}

void RingBuffer::Resize(size_t size) {
    std::vector<int> buffer((size == 0) ? 1 : size);
    size_t count_size = std::min(buffer.size(), Size()); // кол-во элементов сохранилось (Size()), либо уменьшилось до size
    for (size_t i = 0; i < count_size; ++i) {
        size_t indexShift = ((i + tail - (count_size - 1)) + Capacity()) % Capacity(); // смещение индекса при копировании элементов в измененный буффер
        buffer[i] = data[indexShift];
    }
    elementCount = count_size;
    data = buffer;
    head = 0;
    tail = count_size - 1;
}

std::vector<int> RingBuffer::Vector() {
    std::vector<int> buffer(Size());
    for (size_t i = 0; i < Size(); ++i) {
        buffer[i] = (*this)[i];
    }
    return buffer;
}

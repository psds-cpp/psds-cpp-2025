#include <vector>
#include <initializer_list>
#include <algorithm>

class RingBuffer {
private:
    std::vector<int> buffer;
    size_t start = 0;  
    size_t end = 0;   
    size_t count = 0;  
public:
    RingBuffer(size_t capacity)
        : buffer(capacity == 0 ? 1 : capacity), start(0), end(0), count(0) {}
    RingBuffer(size_t capacity, int value)
        : buffer(capacity == 0 ? 1 : capacity, value), start(0), end(0), count(buffer.size()) {}
    RingBuffer(std::initializer_list<int> list)
        : buffer(list.size() == 0 ? 1 : list.size()), start(0), end(list.size() % (list.size() == 0 ? 1 : list.size())), count(list.size()) 
    {
        if (!list.size()) {
            end = 0;
            count = 0;
        } else {
            size_t i = 0;
            for (int v : list) {
                buffer[i++] = v;}
        }
    }
    void Push(int value) {
        buffer[end] = value;
        end = (end + 1) % buffer.size();
        if (count < buffer.size()) {
            ++count;
        } else {
            start = (start + 1) % buffer.size();}
    }
    bool TryPush(int value) {
        if (Full()) return false;
        buffer[end] = value;
        end = (end + 1) % buffer.size();
        ++count;
        return true;}
    void Pop() {
        if (Empty()) return;
        start = (start + 1) % buffer.size();
        --count;}
    bool TryPop(int &value) {
        if (Empty()) return false;
        value = buffer[start];
        start = (start + 1) % buffer.size();
        --count;
        return true;}
    int& operator[](size_t index) {
        return buffer[(start + index) % buffer.size()];}
    const int& operator[](size_t index) const {
        return buffer[(start + index) % buffer.size()];}
    int& Front() { return buffer[(end + buffer.size() - 1) % buffer.size()]; }
    const int& Front() const { return buffer[(end + buffer.size() - 1) % buffer.size()]; }
    int& Back() { return buffer[start]; }
    const int& Back() const { return buffer[start]; }
    bool Empty() const { return count == 0; }
    bool Full() const { return count == buffer.size(); }
    size_t Size() const { return count; }
    size_t Capacity() const { return buffer.size(); }
    void Clear() {
        start = 0;
        end = 0;
        count = 0;}
    void Resize(size_t new_capacity) {
        if (new_capacity == 0) new_capacity = 1;
        std::vector<int> new_buffer(new_capacity);
        size_t new_count = std::min(count, new_capacity);
        for (size_t i = 0; i < new_count; ++i) {
            new_buffer[i] = (*this)[count - new_count + i];}
        buffer = std::move(new_buffer);
        start = 0;
        count = new_count;
        end = new_count % buffer.size();}
    std::vector<int> Vector() const {
        std::vector<int> result(count);
        for (size_t i = 0; i < count; ++i) {
            result[i] = (*this)[i];}
        return result;}
    RingBuffer(const RingBuffer& other)
        : buffer(other.buffer), start(other.start), end(other.end), count(other.count) {}
    RingBuffer& operator=(const RingBuffer& other) {
        if (this != &other) {
            buffer = other.buffer;
            start = other.start;
            end = other.end;
            count = other.count;}
        return *this;}
};

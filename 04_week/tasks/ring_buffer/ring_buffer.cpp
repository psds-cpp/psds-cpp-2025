#include <vector>
#include <initializer_list>


class RingBuffer {
public:
    RingBuffer() = default;
    //
    RingBuffer(size_t size);
    RingBuffer(size_t capacity, int value);
    RingBuffer(const std::initializer_list<int> list);
    // Добавляет элемент в буфер, может перезаписывать
    void Push(int value);
    // Пытается добавить элемент без перезаписи, true - успех
    bool TryPush(int value);
    // Убирает самый старый элемент из буфера
    void Pop();
    // Пытается извлечь самый старый элемент и возвращает убранное значение через параметр метода
    bool TryPop(int& poped);
    // Обеспечивает доступ на запись и чтение к самому новому элементу буфера
    int& Front();
    // Обеспечивает доступ на запись и чтение к самому старому элементу буфера
    int& Back();
    // Обеспечивает доступ на запись и чтение к самому новому элементу буфера
    const int& Front() const;
    // Обеспечивает доступ на запись и чтение к самому старому элементу буфера
    const int& Back() const;
    // Возвращает результат проверки буфера на отсутствие элементов 
    bool Empty() const;
    // Возвращает результат проверки буфера на заполненность
    bool Full() const;
    // Возвращает количество элементов в буфере
    size_t Size() const;
    // Возвращает размер буфера
    size_t Capacity() const;
    // Очищает буфер, позиции начала и конца соответствуют нулевому элементу
    void Clear();
    // Изменяет вместимость буфера
    void Resize(size_t size);
    // Возвращает `std::vector<int>` - линейное представление буфера
    std::vector<int> Vector() const;
    // Доступ по индексу
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

private:
    std::vector<int> data_ = {-1};
    // Кол-во элементов в буфере
    size_t size_ = 0;
    // Итератор на последний элемент
    std::vector<int>::iterator end_ = data_.end();
    std::vector<int>::iterator begin_ = data_.begin();
};

RingBuffer::RingBuffer(size_t size) : data_(size + 1), size_(0), end_(data_.begin()), begin_(data_.begin()) {
    begin_ += size + 1 >= 2 ? 1 : 0;
}

RingBuffer::RingBuffer(size_t size, int value) : data_(size+1, value), size_(size), end_(data_.end() - 1), begin_(data_.begin()) {
    if(size == 0){
        data_.push_back(value);
        size_ = 1;
        end_ = data_.end() - 1;
        begin_ = end_;
    }
    begin_ += size + 1 >= 2 ? 1 : 0;
}

RingBuffer::RingBuffer(const std::initializer_list<int> list) : size_(list.size()), end_(data_.begin()), begin_(data_.begin()) {
    data_.insert(data_.end(), list.begin(), list.end());
    end_ = data_.end() - 1;
    begin_ = data_.begin() + 1;
}

void RingBuffer::Push(int value) {
    if(end_ + 1 == data_.end()){
        end_ = data_.begin() + 1;
        *end_ = value;
    }
    else *(++end_) = value;

    if(begin_ != end_ || size_ == 0){
        ++size_;
        return;
    }
    if(size_ != 1){
        begin_ = begin_ + 1 == data_.end() ? data_.begin() + 1 : begin_ + 1;
    }
}
bool RingBuffer::TryPush(int value) {
    if(size_ == data_.size() - 1){
        return false;
    }
    else *(++end_) = value;

    if(begin_ != end_ || size_ == 0){
        ++size_;
        return true;
    }
    if(size_ != 1){
        begin_ = begin_ + 1 == data_.end() ? data_.begin() + 1 : begin_ + 1;
    }
    return true;
}
void RingBuffer::Pop() {
    if(size_ == 0) return;
    --size_;
    begin_ = begin_ + 1 == data_.end() ? data_.begin() + 1 : begin_ + 1;
}
bool RingBuffer::TryPop(int& poped) {
    if(size_ == 0) return false;
    --size_;
    poped = *begin_;
    begin_ = begin_ + 1 == data_.end() ? data_.begin() + 1 : begin_ + 1;
    return true;
}

int& RingBuffer::Front() {
    return *end_;
}
int& RingBuffer::Back() {
    return *begin_;
}
const int& RingBuffer::Front() const {
    return *end_;
}
const int& RingBuffer::Back() const {
    return *begin_;
}
bool RingBuffer::Empty() const {
    return size_ == 0 ? true : false;
}
bool RingBuffer::Full() const {
    if(data_.size() == 1) return false;
    return data_.size() - 1 == size_ ? true : false;
}
size_t RingBuffer::Size() const {
    return size_;
}
size_t RingBuffer::Capacity() const {
    return data_.size() != 1 ? data_.size() - 1 : 1;
}
void RingBuffer::Clear() {
    size_ = 0;
    end_ = data_.begin();
    begin_ = data_.begin() + 1;
}
void RingBuffer::Resize(size_t size) {
    if(size == size_) return;
    if(size == 0) {
        Clear();
        size_ = 1;
        return;
    }
    std::vector<int> New = Vector();
    if(size < size_){
        data_ = std::vector<int>(New.end() - size, New.end());
        data_.insert(data_.begin(), 0);
    }
    else{
        New.insert(New.begin(), 0);
        New.resize(size + 1);
        data_ = New;
    }

    size_ = size < size_ ? size : size_;
    begin_ = data_.begin() + 1;
    end_ = begin_ + size_ - 1;
}
std::vector<int> RingBuffer::Vector() const {
    std::vector<int> res;
    res.reserve(size_);
    std::vector<int>::const_iterator it = begin_;
    while(true){
        res.push_back(*it);
        if(it == end_) break;
        if(it + 1 == data_.end()) it = data_.begin() + 1;
        else ++it;
    }
    return res;
}

int& RingBuffer::operator[](size_t index) {
    if(size_t dif = data_.end() - begin_; dif <= index){
        return *(data_.begin() + index - dif + 1);
    }
    return *(begin_ + index);
}
const int& RingBuffer::operator[](size_t index) const {
    if(size_t dif = data_.end() - begin_; dif <= index){
        return *(data_.begin() + index - dif + 1);
    }
    return *(begin_ + index);
}
#include <algorithm>
#include <initializer_list>

class SimpleVector {
public:
    // Конструктор по умолчанию
    SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}

    // Конструктор, принимающий размер и заполняющий нулями
    explicit SimpleVector(size_t size) : size_(size), capacity_(size) {
        data_ = new int[capacity_]();
    }

    // Конструктор, принимающий размер и значение для заполнения
    SimpleVector(size_t size, int value) : size_(size), capacity_(size) {
        data_ = new int[capacity_];
        std::fill(data_, data_ + size_, value);
    }

    // Конструктор от initializer_list
    SimpleVector(std::initializer_list<int> init) 
        : size_(init.size()), capacity_(init.size()) {
        data_ = new int[capacity_];
        std::copy(init.begin(), init.end(), data_);
    }

    // Конструктор копирования
    SimpleVector(const SimpleVector& other) 
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Конструктор перемещения
    SimpleVector(SimpleVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Оператор присваивания копированием
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            SimpleVector tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    // Оператор присваивания перемещением
    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Деструктор
    ~SimpleVector() {
        delete[] data_;
    }

    // Метод Swap
    void Swap(SimpleVector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Операторы индексирования
    int& operator[](size_t index) {
        return data_[index];
    }

    const int& operator[](size_t index) const {
        return data_[index];
    }

    // Метод Size
    size_t Size() const {
        return size_;
    }

    // Метод Capacity
    size_t Capacity() const {
        return capacity_;
    }

    // Метод Empty
    bool Empty() const {
        return size_ == 0;
    }

    // Метод Data (константный)
    const int* Data() const {
        return data_;
    }

    // Метод PushBack
    void PushBack(int value) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    // Метод PopBack
    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    // Метод Insert
    int* Insert(const int* pos, int value) {
        if (pos < data_ || pos > data_ + size_) {
            return data_ + size_;
        }
        
        size_t index = pos - data_;
        
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        
        // Сдвигаем элементы вправо
        for (size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        
        data_[index] = value;
        ++size_;
        
        return data_ + index;
    }

    // Метод Erase
    int* Erase(const int* pos) {
        if (pos < data_ || pos >= data_ + size_) {
            return data_ + size_;
        }
        
        size_t index = pos - data_;
        
        // Сдвигаем элементы влево
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        
        --size_;
        
        return data_ + index;
    }

    // Метод Clear
    void Clear() {
        size_ = 0;
    }

    // Метод Resize
    void Resize(size_t new_size, int value = 0) {
        if (new_size == size_) {
            return;
        }
        
        if (new_size < size_) {
            size_ = new_size;
            return;
        }
        
        if (new_size > capacity_) {
            Reserve(new_size);
        }
        
        // Заполняем новые элементы значением value
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = value;
        }
        
        size_ = new_size;
    }

    // Метод Reserve
    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        
        int* new_data = new int[new_capacity];
        if (data_) {
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // Методы для range-based for
    int* begin() {
        return data_;
    }

    const int* begin() const {
        return data_;
    }

    int* end() {
        return data_ + size_;
    }

    const int* end() const {
        return data_ + size_;
    }

    // Операторы сравнения
    bool operator==(const SimpleVector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const SimpleVector& other) const {
        return !(*this == other);
    }

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

// Внешняя функция swap
inline void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}
#include <algorithm>
#include <cstddef>
#include <initializer_list>

class SimpleVector {
public:
    SimpleVector() = default;

    SimpleVector(size_t size) : begin_(new int[size]{0}), end_(begin_ + size), capacity_(end_) {}
    
    SimpleVector(std::initializer_list<int> list) : begin_(new int[list.size()]),
                                                    end_(std::copy(list.begin(), list.end(), begin_)),
                                                    capacity_(end_) {}

    SimpleVector(const SimpleVector& other) : begin_(new int[other.Size()]),
                                        end_(std::copy(other.begin_, other.end_, begin_)),
                                        capacity_(other.end_) {}

    SimpleVector(SimpleVector&& other) : begin_(other.begin_), end_(other.end_), capacity_(other.capacity_) {
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.capacity_ = nullptr;
    }
    
    ~SimpleVector() {
        delete [] begin_;
        begin_ = end_ = capacity_ = nullptr;        
    }

    SimpleVector& operator=(const SimpleVector& other) {
        begin_ = new int[other.Size()];
        end_ = std::copy(other.begin_, other.end_, begin_);
        capacity_ = end_;
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& other) {
        begin_ = other.begin_;
        end_ = other.end_;
        capacity_ = other.capacity_;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.capacity_ = nullptr;
        return *this;
    }

    int& operator[](size_t idx){
        return begin_[idx];
    }

    void Swap(SimpleVector& other);
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;
    const int* Data() const;
    void PushBack(int value);
    void PopBack();
    
    
    
private:
    int* begin_ = nullptr;
    int* end_ = nullptr;
    int* capacity_ = nullptr;
};

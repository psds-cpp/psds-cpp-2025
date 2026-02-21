#include <string>


class UniquePtr {
private:
    std::string* ptr_;
public:
    // Дефолтный конструктор
    UniquePtr() : ptr_(nullptr) {};

    // Конструктор от сырого указателя
    explicit UniquePtr(std::string* s_ptr) : ptr_(s_ptr) {};

    // Запрет копирования
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Конструктор перемещения
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    
    //Оператор перемещения
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~UniquePtr() {
        delete ptr_;
    }

    // Операторы ->, * и bool()
    std::string& operator*() const { return *ptr_; }

    std::string* operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }
    
    // Методы
    std::string* Get();

    std::string* Release();

    void Reset(std::string* st);

    void Reset();

    void Swap(UniquePtr& other);

};

// Реализация методов
std::string* UniquePtr::Get() {
    return ptr_;
}

std::string* UniquePtr::Release() {
    std::string* temp_ptr = ptr_;
    ptr_ = nullptr;
    return temp_ptr;
}

void UniquePtr::Reset(std::string* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

void UniquePtr::Reset() {
    Reset(nullptr);
}

void UniquePtr::Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
}

// Функции
UniquePtr MakeUnique(std::string& st) {
    return UniquePtr(new std::string(st));
}

UniquePtr MakeUnique(std::string&& st) {
    return UniquePtr(new std::string(std::move(st)));
}

void Swap(UniquePtr& lhs, UniquePtr& rhs) {
    lhs.Swap(rhs);
}
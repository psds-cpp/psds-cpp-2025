#include <string>

// Хранит счётчики 
struct ControlCount 
{
    size_t shared_count;
    size_t weak_count;
    std::string* ptr_cc;

    explicit ControlCount(std::string* p) : shared_count(1), weak_count(0), ptr_cc(p) {}

    ~ControlCount() { delete ptr_cc; }
};


class SharedPtr {
private:
std::string* ptr_;
ControlCount* control;

public:
// Дефолтный конструктор
SharedPtr() : ptr_(nullptr), control(nullptr) {}

// Конструктор от сырого указателя
explicit SharedPtr(std::string* p) : ptr_(p), control(nullptr) {
    if (ptr_) {
        control = new ControlCount(ptr_);
    }
};

//  Конструктор копирования
SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), control(other.control) {
    if (control) {
        ++control->shared_count;
    } 
}

// Конструктор перемещения
SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), control(other.control) {
    other.ptr_ = nullptr;
    other.control = nullptr;
}

// Деструктор
~SharedPtr() {   
    if (!control) { return; }
    --control->shared_count;

    if (control->shared_count > 0) { return; }
    delete ptr_;
    ptr_ = nullptr;

    if (control->weak_count > 0) { return; }
    delete control;
}

// Оператор присвоения при копировании
SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
        if (control) { 
            --control->shared_count; 
            if (!control->shared_count) {
                delete ptr_;
                if (!control->weak_count) {
                    delete control;
                }
            }
        }

        ptr_ = other.ptr_;
        control = other.control;
        if (control) {
            ++control->shared_count;
        }
    }
    return *this;
}

// Оператор присвоения при перемещении
SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        if (control) { 
            --control->shared_count; 
            if (!control->shared_count) {
                delete ptr_;
                if (!control->weak_count) {
                    delete control;
                }
            }
        }

        ptr_ = other.ptr_;
        control = other.control;
        other.ptr_ = nullptr;
        other.control = nullptr;
    }
    return *this;
}


};



class WeakPtr {

};
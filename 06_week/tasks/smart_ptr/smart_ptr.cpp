#include <string>
#include <utility>

struct control {
    size_t strong = 0;
    size_t weak = 0;

    control(size_t st = 0, size_t wk = 0):
        strong(st),
        weak(wk) {}
};

class SharedPtr {
public:
    SharedPtr();
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr(std::string* ptr);
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    ~SharedPtr();
    std::string* operator->();
    std::string& operator*();
    operator bool() const noexcept;
    operator std::string*() const noexcept;
    std::string* Get() const noexcept;
    size_t UseCount() const noexcept;
    void Reset(std::string* ptr);
    void Swap(SharedPtr& other);
    bool operator==(SharedPtr& other) const;
    friend class WeakPtr;

private:
    std::string* ptr_;
    control* ctrl_ptr_;
    void Free();

};

class WeakPtr {
public:
    WeakPtr();
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other);
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other);
    ~WeakPtr();
    std::string* operator->();
    std::string& operator*();
    operator bool() const noexcept;
    size_t UseCount() const noexcept;
    bool Expired() const noexcept;

private:
    std::string* ptr_;
    control* ctrl_ptr_;
};


void SharedPtr::Free() {
    if(ctrl_ptr_->strong == 0) {
        delete ptr_;
        if(ctrl_ptr_->weak == 0) {
            delete ctrl_ptr_;
        }
    }
    ptr_ = nullptr;
    ctrl_ptr_ = nullptr;
}

SharedPtr::SharedPtr():
    ptr_(nullptr),
    ctrl_ptr_(new control) {}

SharedPtr::SharedPtr(const SharedPtr& other):
    ptr_(other.ptr_),
    ctrl_ptr_(other.ctrl_ptr_) {
    ++(ctrl_ptr_->strong);
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept:
    ptr_(other.ptr_),
    ctrl_ptr_(other.ctrl_ptr_) {
    other.ptr_ = nullptr;
    other.ctrl_ptr_ = new control;
}

SharedPtr::SharedPtr(std::string* ptr):
    ptr_(ptr),
    ctrl_ptr_(new control(1)) {}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if(this->ptr_ != other.ptr_) {
        --(ctrl_ptr_->strong);
        Free();
        ptr_ = other.ptr_;
        ctrl_ptr_ = other.ctrl_ptr_;
        ++(ctrl_ptr_->strong);
    }
    return *this;
}
SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if(this->ptr_ != other.ptr_) {
        --(ctrl_ptr_->strong);
        Free();
        ptr_ = other.ptr_;
        ctrl_ptr_ = other.ctrl_ptr_;
        other.ptr_ = nullptr;
        other.ctrl_ptr_ = new control;
    }
    return *this;
}
SharedPtr::~SharedPtr() {
    ctrl_ptr_->strong -= ctrl_ptr_->strong == 0 ? 0 : 1;
    Free();
}

std::string* SharedPtr::operator->() { 
    return ptr_;
}

std::string& SharedPtr::operator*() {
    return *ptr_;
}

SharedPtr::operator bool() const noexcept {
    return ptr_ != nullptr;
}

SharedPtr::operator std::string*() const noexcept {
    return ptr_;
}

std::string* SharedPtr::Get() const noexcept {
    return ptr_;
}

size_t SharedPtr::UseCount() const noexcept {
    return ctrl_ptr_->strong;
}

void SharedPtr::Reset(std::string* ptr = nullptr) {
    ctrl_ptr_->strong -= ctrl_ptr_->strong == 0 ? 0 : 1;
    Free();
    ptr_ = ptr;
    ctrl_ptr_ = new control;
    ctrl_ptr_->strong += ptr ? 1 : 0;
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ctrl_ptr_, other.ctrl_ptr_);
}

bool SharedPtr::operator==(SharedPtr& other) const {
    return ptr_ == other.ptr_;
}
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
friend class WeakPtr;

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

private:
    std::string* ptr_;
    control* ctrl_ptr_;
};

class WeakPtr {
public:
    WeakPtr();
    WeakPtr(std::string* ptr);
    WeakPtr(SharedPtr& other);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    ~WeakPtr();
    std::string* operator->();
    std::string& operator*();
    operator bool() const noexcept;
    operator std::string*() const noexcept;
    void Reset(std::string* ptr);
    void Swap(WeakPtr& other);
    size_t UseCount() const noexcept;
    bool Expired() const noexcept;
    SharedPtr Lock() const;

private:
    std::string* ptr_;
    control* ctrl_ptr_;
};

SharedPtr MakeShared(const std::string& str);
SharedPtr MakeShared(std::string&& str);
void Swap(SharedPtr& a, SharedPtr& b);
void Swap(WeakPtr& a, WeakPtr& b);

//============= SharedPtr =================

void SharedPtr::Reset(std::string* ptr = nullptr) {
    if(ctrl_ptr_) {
        --(ctrl_ptr_->strong);
        if(ctrl_ptr_->strong == 0) {
            delete ptr_;
            if(ctrl_ptr_->weak == 0) {
                delete ctrl_ptr_;
            }
        }
    }
    ptr_ = ptr;
    ctrl_ptr_ = ptr ? new control(1) : nullptr;
}

SharedPtr::SharedPtr():
    ptr_(nullptr),
    ctrl_ptr_(nullptr) {}

SharedPtr::SharedPtr(const SharedPtr& other):
    ptr_(other.ptr_),
    ctrl_ptr_(other.ctrl_ptr_) {
    ++(ctrl_ptr_->strong);
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept:
    ptr_(std::exchange(other.ptr_, nullptr)),
    ctrl_ptr_(std::exchange(other.ctrl_ptr_, nullptr)) {}

SharedPtr::SharedPtr(std::string* ptr):
    ptr_(ptr),
    ctrl_ptr_(new control(1)) {}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if(this->ptr_ != other.ptr_) {
        Reset();
        ptr_ = other.ptr_;
        ctrl_ptr_ = other.ctrl_ptr_;
        ++(ctrl_ptr_->strong);
    }
    return *this;
}
SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if(this->ptr_ != other.ptr_) {
        Reset();
        ptr_ = std::exchange(other.ptr_, nullptr);
        ctrl_ptr_ = std::exchange(other.ctrl_ptr_, nullptr);
    }
    return *this;
}
SharedPtr::~SharedPtr() {
    Reset();
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
    return ctrl_ptr_ ? ctrl_ptr_->strong : 0;
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ctrl_ptr_, other.ctrl_ptr_);
}

bool SharedPtr::operator==(SharedPtr& other) const {
    return ptr_ == other.ptr_;
}

//============= WeakPtr =================

void WeakPtr::Reset(std::string* ptr = nullptr) {
    if(ctrl_ptr_) {
        --(ctrl_ptr_->weak);
        if(ctrl_ptr_->strong == 0 && ctrl_ptr_->weak == 0) {
            delete ctrl_ptr_;
        }
    }
    ptr_ = ptr;
    ctrl_ptr_ = ptr ? new control(0, 1) : nullptr;
}

WeakPtr::WeakPtr():
    ptr_(nullptr),
    ctrl_ptr_(nullptr) {}

WeakPtr::WeakPtr(std::string* ptr):
    ptr_(ptr),
    ctrl_ptr_(new control(0, 1)) {}

WeakPtr::WeakPtr(SharedPtr& sp):
    ptr_(sp.ptr_),
    ctrl_ptr_(sp.ctrl_ptr_) {
    ++(ctrl_ptr_->weak);
}

WeakPtr::WeakPtr(const WeakPtr& other):
    ptr_(other.ptr_),
    ctrl_ptr_(other.ctrl_ptr_) {
    ++(ctrl_ptr_->weak);
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept:
    ptr_(std::exchange(other.ptr_, nullptr)),
    ctrl_ptr_(std::exchange(other.ctrl_ptr_, nullptr)) {}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if(this->ptr_ != other.ptr_) {
        Reset();
        ptr_ = other.ptr_;
        ctrl_ptr_ = other.ctrl_ptr_;
        ++(ctrl_ptr_->weak);
    }
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if(this->ptr_ != other.ptr_) {
        Reset();
        ptr_ = std::exchange(other.ptr_, nullptr);
        ctrl_ptr_ = std::exchange(other.ctrl_ptr_, nullptr);
    }
    return *this;
}

WeakPtr::~WeakPtr() {
    Reset();
}

std::string* WeakPtr::operator->() {
    return ptr_;
}

std::string& WeakPtr::operator*() {
    return *ptr_;
}

WeakPtr::operator bool() const noexcept {
    return ptr_ != nullptr;
}

WeakPtr::operator std::string*() const noexcept {
    return ptr_;
}

void WeakPtr::Swap(WeakPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ctrl_ptr_, other.ctrl_ptr_);
}

size_t WeakPtr::UseCount() const noexcept {
    return ctrl_ptr_ ? ctrl_ptr_->strong : 0;
}

bool WeakPtr::Expired() const noexcept {
    return !ctrl_ptr_ ? true : (ctrl_ptr_->strong == 0);
}

SharedPtr WeakPtr::Lock() const {
    SharedPtr sp;
    sp.ptr_ = Expired() ? nullptr : ptr_;
    sp.ctrl_ptr_ = Expired() ? nullptr : ctrl_ptr_;
    if(sp.ctrl_ptr_) {
        ++(ctrl_ptr_->strong);
    }
    return sp;
}

//================== Внешние функции ================

SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& a, SharedPtr& b) {
    a.Swap(b);
}

void Swap(WeakPtr& a, WeakPtr& b) {
    a.Swap(b);
}
#include <string>
#include <utility>

class UniquePtr {
public:
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr& other) = delete;
    UniquePtr();
    UniquePtr(std::string* ptr);
    UniquePtr(UniquePtr&& other);
    ~UniquePtr();
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    std::string* Get() const { return ptr_; }
    std::string* Release();
    void Reset(std::string* new_ptr);
    void Swap(UniquePtr& other);
    operator bool() const noexcept;
    std::string* operator->() { return ptr_; }
    std::string& operator*() { return *ptr_; }

private:
    std::string* ptr_;
};

UniquePtr::UniquePtr():
    ptr_(nullptr) {}

UniquePtr::UniquePtr(std::string* ptr):
    ptr_(ptr) {}

UniquePtr::UniquePtr(UniquePtr&& other):
    ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

UniquePtr::~UniquePtr() {
    delete ptr_;
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if(ptr_ != other.ptr_) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

std::string* UniquePtr::Release() {
    std::string* res = ptr_;
    ptr_ = nullptr;
    return res;
}

void UniquePtr::Reset(std::string* new_ptr = nullptr){
    delete ptr_;
    ptr_ = new_ptr;
}

void UniquePtr::Swap(UniquePtr& other){
    std::swap(ptr_, other.ptr_);
}

UniquePtr::operator bool() const noexcept {
    return ptr_ != nullptr;
}

UniquePtr MakeUnique(std::string& data) {
    return UniquePtr(new std::string(data));
}

UniquePtr MakeUnique(std::string&& data) {
    return UniquePtr(new std::string(std::move(data)));
}

void Swap(UniquePtr& a, UniquePtr& b) {
    a.Swap(b);
}
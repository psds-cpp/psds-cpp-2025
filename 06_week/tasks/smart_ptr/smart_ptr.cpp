#include <cstddef>
#include <string>
#include <sys/types.h>
#include <utility>

struct ControlBlock {
    size_t sharedCnt = 0;
    size_t weakCnt = 0;
};

// SharedPtr

class SharedPtr {
public:
    SharedPtr();
    SharedPtr(std::string* str);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr(std::string* str, ControlBlock* block);
    ~SharedPtr();

    std::string& operator*();
    const std::string& operator*() const;
    explicit operator bool() const;
    std::string* operator->();
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    std::string* Get() const;
    ControlBlock* GetBlock() const;
    size_t UseCount() const;
    void Reset();
    void Reset(std::string* str);
    void Swap(SharedPtr& other);

private:
    std::string* data;
    ControlBlock* block;
};

SharedPtr::SharedPtr() : data(nullptr), block(nullptr) {}

SharedPtr::SharedPtr(std::string* str) : data(str), block(new ControlBlock()) {
    ++block->sharedCnt;
}

SharedPtr::SharedPtr(const SharedPtr& other) : data(other.data), block(other.block) {
    ++block->sharedCnt;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept : data(other.data), block(other.block) {
    other.data = nullptr;
    other.block = nullptr;
}

SharedPtr::SharedPtr(std::string* str, ControlBlock* block) : data(str), block(block) {
    ++block->sharedCnt;
}

SharedPtr::~SharedPtr() {
    if (block) {
        --block->sharedCnt;
        if (block->sharedCnt == 0) {
            delete data;
            data = nullptr;
            if (block->weakCnt == 0) {
                delete block;
            }
        }
        block = nullptr;
    }
}

std::string& SharedPtr::operator*() {
    return *data;
}

const std::string& SharedPtr::operator*() const {
    return *data;
}

SharedPtr::operator bool() const {
    return data != nullptr;
}

std::string* SharedPtr::operator->() {
    return data;
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        SharedPtr::~SharedPtr();
        data = other.data;
        block = other.block;
        ++block->sharedCnt;
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        SharedPtr::~SharedPtr();
        data = other.data;
        block = other.block;
        other.data = nullptr;
        other.block = nullptr;
    }
    return *this;
}

std::string* SharedPtr::Get() const {
    return data;
}

ControlBlock* SharedPtr::GetBlock() const {
    return block;
}

size_t SharedPtr::UseCount() const {
    return (block == nullptr) ? 0 : block->sharedCnt;
}

void SharedPtr::Reset() {
    SharedPtr::~SharedPtr();
}

void SharedPtr::Reset(std::string* str) {
    SharedPtr::~SharedPtr();
    data = str;
    block = new ControlBlock();
    ++block->sharedCnt;
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(data, other.data);
    std::swap(block, other.block);
}

// WeakPtr

class WeakPtr {
public:
    WeakPtr();
    WeakPtr(const SharedPtr& ptr);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    ~WeakPtr();

    WeakPtr operator=(const WeakPtr& other);
    WeakPtr operator=(WeakPtr&& other) noexcept;
    
    size_t UseCount() const;
    void Reset();
    void Swap(WeakPtr& other);
    bool Expired() const;
    SharedPtr Lock();

private:
    std::string* data;
    ControlBlock* block;
};

WeakPtr::WeakPtr() : data(nullptr), block(nullptr) {}

WeakPtr::WeakPtr(const SharedPtr& ptr) : data(ptr.Get()), block(ptr.GetBlock()) {
    ++block->weakCnt;
}

WeakPtr::WeakPtr(const WeakPtr& other) : data(other.data), block(other.block) {
    if (block) {
        ++block->weakCnt;
    }
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept : data(other.data), block(other.block) {
    other.data = nullptr;
    other.block = nullptr;
}

WeakPtr::~WeakPtr() {
    if (block) {
        --block->weakCnt;
        if (block->sharedCnt == 0 && block->weakCnt == 0) {
            delete block;
        }
        block = nullptr;
    }
}

WeakPtr WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {
        WeakPtr::~WeakPtr();
        data = other.data;
        block = other.block;
        ++block->weakCnt;
    }
    return *this;
}

WeakPtr WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        WeakPtr::~WeakPtr();
        data = other.data;
        block = other.block;
        other.data = nullptr;
        other.block = nullptr;
    }
    return *this;
}

size_t WeakPtr::UseCount() const {
    return (block == nullptr) ? 0 : block->sharedCnt;
}

void WeakPtr::Reset() {
    WeakPtr::~WeakPtr();
}

void WeakPtr::Swap(WeakPtr& other) {
    std::swap(data, other.data);
    std::swap(block, other.block);
}

bool WeakPtr::Expired() const {
    return !block || block->sharedCnt == 0;
}

SharedPtr WeakPtr::Lock() {
    if (!Expired()) {
        return SharedPtr(data, block);
    }
    return SharedPtr();
}

// Доп методы

SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) noexcept {
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& ptr1, SharedPtr& ptr2) {
    ptr1.Swap(ptr2);
}

void Swap(WeakPtr& ptr1, WeakPtr& ptr2) {
    ptr1.Swap(ptr2);
}
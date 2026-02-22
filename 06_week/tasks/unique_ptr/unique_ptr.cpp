#include <string>
#include <algorithm>


class UniquePtr {
public:
    ~UniquePtr();
    UniquePtr();
    UniquePtr(std::string* str);
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other);
    std::string* Get();
    std::string* Release();
    void Reset(std::string* new_str = nullptr);
    void Swap(UniquePtr& other);
    operator bool() const;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other);
    std::string* operator->() const;
    std::string& operator*() const;
private:
    std::string* m_ptr = nullptr;
};

UniquePtr::~UniquePtr() {
    delete m_ptr;
}

UniquePtr::UniquePtr() {}

UniquePtr::UniquePtr(std::string *str) : m_ptr(str) {}

UniquePtr::UniquePtr(UniquePtr&& other) : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;
}

std::string* UniquePtr::Get() {
    return m_ptr;
}

std::string* UniquePtr::Release() {
    std::string* temp = m_ptr;
    m_ptr = nullptr;
    return temp;
}

void UniquePtr::Reset(std::string* new_str) {
    delete m_ptr;
    m_ptr = new_str;
}

void UniquePtr::Swap(UniquePtr& other) {
    std::swap(m_ptr, other.m_ptr);
}

UniquePtr::operator bool() const {
    return static_cast<bool>(m_ptr);
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) {
    if (this == &other) { return *this; }
    delete m_ptr;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}

std::string* UniquePtr::operator->() const {
    return m_ptr;
}

std::string& UniquePtr::operator*() const {
    return *m_ptr;
}

UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

void Swap(UniquePtr& lhs, UniquePtr& rhs) {
    lhs.Swap(rhs);
}
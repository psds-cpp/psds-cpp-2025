#include <string>
#include <algorithm>

struct Counter {
    size_t shared_cnt = 0;
    size_t weak_cnt = 0;
};

class SharedPtr {
public:
    ~SharedPtr();
    SharedPtr();
    SharedPtr(std::string* str);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other);
    std::string* Get();
    void Reset(std::string* new_str = nullptr);
    void Swap(SharedPtr& other);
    size_t UseCount() const;
    operator bool() const;
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other);
    std::string* operator->() const;
    std::string& operator*() const;
    friend class WeakPtr;
private:
    void m_decrementCounter();
    std::string* m_res = nullptr;
    Counter* m_counter = nullptr;
};

class WeakPtr {
public:
    ~WeakPtr();
    WeakPtr();
    WeakPtr(const SharedPtr& ptr);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other);
    SharedPtr Lock() const;
    void Reset(std::string* new_str = nullptr);
    void Swap(WeakPtr& other);
    size_t UseCount() const;
    bool Expired() const;
    operator bool() const;
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other);
    WeakPtr& operator=(const SharedPtr& ptr);
private:
    void m_decrementCounter();
    std::string* m_res = nullptr;
    Counter* m_counter = nullptr;
};

void SharedPtr::m_decrementCounter() {
    if (!m_counter) { return; }
    if (m_counter->shared_cnt != 0) {
        m_counter->shared_cnt -= 1;
        if (m_counter->shared_cnt == 0) { delete m_res; }
    }
    if (m_counter->shared_cnt == 0 && m_counter->weak_cnt == 0) { delete m_counter; }
}

SharedPtr::~SharedPtr() {
    m_decrementCounter();
}

SharedPtr::SharedPtr() {}

SharedPtr::SharedPtr(std::string* str) : m_res(str), m_counter(new Counter{1, 0}) {}

SharedPtr::SharedPtr(const SharedPtr& other) : m_res(other.m_res), m_counter(other.m_counter) {
    m_counter->shared_cnt += 1;
}

SharedPtr::SharedPtr(SharedPtr&& other) : m_res(other.m_res), m_counter(other.m_counter) {
    other.m_res = nullptr;
    other.m_counter = nullptr;
}

std::string* SharedPtr::Get() {
    return m_res;
}

void SharedPtr::Reset(std::string* new_str) {
    m_decrementCounter();
    m_counter = !new_str ? nullptr : new Counter{1, 0};
    m_res = new_str;
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(m_res, other.m_res);
    std::swap(m_counter, other.m_counter);
}

size_t SharedPtr::UseCount() const {
    return !m_counter ? 0 : m_counter->shared_cnt;
}

SharedPtr::operator bool() const {
    return static_cast<bool>(m_res);
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this == &other) { return *this; }
    m_decrementCounter();
    m_res = other.m_res;
    m_counter = other.m_counter;
    m_counter->shared_cnt += 1;
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) {
    if (this == &other) { return *this; }
    m_decrementCounter();
    m_res = other.m_res;
    m_counter = other.m_counter;
    other.m_res = nullptr;
    other.m_counter = nullptr;
    return *this;
}

std::string* SharedPtr::operator->() const {
    return m_res;
}

std::string& SharedPtr::operator*() const {
    return *m_res;
}

void WeakPtr::m_decrementCounter() {
    if (!m_counter) { return; }
    m_counter->weak_cnt -= 1;
    if (m_counter->shared_cnt == 0 && m_counter->weak_cnt == 0) { delete m_counter; }
}

WeakPtr::~WeakPtr() {
    m_decrementCounter();
}

WeakPtr::WeakPtr() {}

WeakPtr::WeakPtr(const SharedPtr& ptr) : m_res(ptr.m_res), m_counter(ptr.m_counter) {
    m_counter->weak_cnt += 1;
}

WeakPtr::WeakPtr(const WeakPtr& other) : m_res(other.m_res), m_counter(other.m_counter) {
    m_counter->weak_cnt += 1;
}

WeakPtr::WeakPtr(WeakPtr&& other) : m_res(other.m_res), m_counter(other.m_counter) {
    other.m_res = nullptr;
    other.m_counter = nullptr;
}

SharedPtr WeakPtr::Lock() const {
    SharedPtr ptr;
    if (Expired()) { return ptr; }
    ptr.m_res = m_res;
    ptr.m_counter = m_counter;
    m_counter->shared_cnt += 1;
    return ptr;
}

void WeakPtr::Reset(std::string* new_str) {
    m_decrementCounter();
    m_counter = !new_str ? nullptr : new Counter{0, 1};
    m_res = new_str;
}

void WeakPtr::Swap(WeakPtr& other) {
    std::swap(m_res, other.m_res);
    std::swap(m_counter, other.m_counter);
}

size_t WeakPtr::UseCount() const {
    return !m_counter ? 0 : m_counter->shared_cnt;
}

bool WeakPtr::Expired() const {
    return !m_counter ? true : m_counter->shared_cnt == 0;
}

WeakPtr::operator bool() const {
    return static_cast<bool>(m_res);
}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this == &other) { return *this; }
    m_decrementCounter();
    m_res = other.m_res;
    m_counter = other.m_counter;
    m_counter->weak_cnt += 1;
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) {
    if (this == &other) { return *this; }
    m_decrementCounter();
    m_res = other.m_res;
    m_counter = other.m_counter;
    other.m_res = nullptr;
    other.m_counter = nullptr;
    return *this;
}

WeakPtr& WeakPtr::operator=(const SharedPtr& ptr) {
    m_decrementCounter();
    m_res = ptr.m_res;
    m_counter = ptr.m_counter;
    m_counter->weak_cnt += 1;
    return *this;
}

SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& lhs, SharedPtr& rhs) {
    lhs.Swap(rhs);
}

void Swap(WeakPtr& lhs, WeakPtr& rhs) {
    lhs.Swap(rhs);
}

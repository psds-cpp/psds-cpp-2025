#include <string>
#include <memory>
#include <algorithm>

struct Node {
    Node();
    Node(const std::string& data, Node* prev = nullptr, Node* next = nullptr);
    Node(std::string&& data, Node* prev = nullptr, Node* next = nullptr);
    std::string data = "";
    Node* prev = nullptr;
    Node* next = nullptr;
};

class SimpleList {
public:
    ~SimpleList();
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other);
    void Swap(SimpleList& other);
    size_t Size() const;
    bool Empty() const;
    void PushBack(const std::string& data);
    void PushBack(std::string&& data);
    void PopBack();
    void PushFront(const std::string& data);
    void PushFront(std::string&& data);
    void PopFront();
    std::string& Back();
    std::string& Back() const;
    std::string& Front();
    std::string& Front() const;
    void Clear();
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other);
private:
    void m_unlink(Node* node);
    void m_link(std::string&& data, Node* target);
    void m_link(const std::string& data, Node* target);
    void m_copy(const SimpleList& other);
    size_t m_size = 0;
    Node* m_dummy;
};

Node::Node() : prev(this), next(this) {}

Node::Node(const std::string& data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}

Node::Node(std::string&& data, Node* prev, Node* next) : data(std::move(data)), prev(prev), next(next) {}

void SimpleList::m_unlink(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --m_size;
}

void SimpleList::m_link(const std::string& data, Node* target) {
    Node* new_node = new Node(data, target, target->next);
    target->next->prev = new_node;
    target->next = new_node;
    ++m_size;
}

void SimpleList::m_link(std::string&& data, Node* target) {
    Node* new_node = new Node(std::move(data), target, target->next);
    target->next->prev = new_node;
    target->next = new_node;
    ++m_size;
}

void SimpleList::m_copy(const SimpleList& other) {
    const Node* other_cursor = other.m_dummy;
    while (other_cursor->next != other.m_dummy) {
        other_cursor = other_cursor->next;
        PushBack(other_cursor->data);
    }
}

SimpleList::~SimpleList() {
    Clear();
    delete m_dummy;
}

SimpleList::SimpleList() : m_dummy(new Node()) {}

SimpleList::SimpleList(const SimpleList& other) : m_dummy(new Node()) {
    m_copy(other);
}

SimpleList::SimpleList(SimpleList&& other) : m_size(other.m_size), m_dummy(other.m_dummy) {
    other.m_size = 0;
    other.m_dummy = new Node();
}

void SimpleList::Swap(SimpleList& other) {
    std::swap(m_size, other.m_size);
    std::swap(m_dummy, other.m_dummy);
}

size_t SimpleList::Size() const {
    return m_size;
}

bool SimpleList::Empty() const {
    return m_size == 0;
}

void SimpleList::PushBack(const std::string& data) {
    m_link(data, m_dummy->prev);
}

void SimpleList::PushBack(std::string&& data) {
    m_link(std::move(data), m_dummy->prev);
}

void SimpleList::PopBack() {
    if (m_dummy->prev == m_dummy) { return; }
    m_unlink(m_dummy->prev);
}

void SimpleList::PushFront(const std::string& data) {
    m_link(data, m_dummy);
}

void SimpleList::PushFront(std::string&& data) {
    m_link(std::move(data), m_dummy);
}

void SimpleList::PopFront() {
    if (m_dummy->next == m_dummy) { return; }
    m_unlink(m_dummy->next);
}

std::string& SimpleList::Back() {
    return m_dummy->prev->data;
}

std::string& SimpleList::Back() const {
    return m_dummy->prev->data;
}

std::string& SimpleList::Front() {
    return m_dummy->next->data;
}

std::string& SimpleList::Front() const {
    return m_dummy->next->data;
}

void SimpleList::Clear() {
    while (m_size > 0) {
        PopBack();
    }
}

SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this == &other) { return *this; }
    Clear();
    m_copy(other);
    return *this;
}

SimpleList& SimpleList::operator=(SimpleList&& other) {
    if (this == &other) { return *this; }
    Clear();
    delete m_dummy;
    m_size = other.m_size;
    m_dummy = other.m_dummy;
    other.m_size = 0;
    other.m_dummy = new Node();
    return *this;
}

void Swap(SimpleList& lhs, SimpleList& rhs) {
    lhs.Swap(rhs);
}

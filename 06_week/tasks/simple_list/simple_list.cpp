#include <cstddef>
#include <memory>
#include <string>

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    std::string data;
};

class SimpleList {
public:
    // Конструкторы (объявления)
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other) noexcept;
    ~SimpleList();

    // Методы (объявления)
    void Swap(SimpleList& other);
    void Swap(SimpleList& first, SimpleList& second);
    size_t Size() const;
    bool Empty() const;
    void PushBack(std::string str);
    void PopBack();
    void PushFront(std::string str);
    void PopFront();
    const std::string& Front() const;
    std::string& Front();
    const std::string& Back() const;
    std::string& Back();
    void Clear();

private:
    Node* front;
    Node* back;
    size_t size;

    void Unlink(Node* ptr) {
        if (!ptr || ptr == front || ptr == back) {
            return;
        }
        --size;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
    }
    void Link(Node* node, Node* ptr) {
        ++size;
        Node* temp = ptr->next;
        
        node->next = temp;
        node->prev = ptr;
        
        ptr->next = node;
        temp->prev = node;
    }
};

// Конструкторы (реализации)
SimpleList::SimpleList() : size(0) {
    front = new Node();
    back = new Node();
    front->next = back;
    back->prev = front;
}
SimpleList::SimpleList(const SimpleList& other) : SimpleList() {
    Node* cur = other.front->next;
    while (cur != other.back) {
        PushBack(cur->data);
        cur = cur->next;
    }
}
SimpleList::SimpleList(SimpleList&& other) noexcept : SimpleList() {
    if (this != &other) {
        this->Swap(other);
    }
}
SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        SimpleList temp(other);
        this->Swap(temp);
    }
    return *this;
}
SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if (this != &other) {
        Clear();
        this->Swap(other);
    }
    return *this;
}
SimpleList::~SimpleList() {
    Clear();
    delete front;
    delete back;
}

// Методы (реализации)
void SimpleList::Swap(SimpleList& other) {
    std::swap(front, other.front);
    std::swap(back, other.back);
    std::swap(size, other.size);
}

void SimpleList::Swap(SimpleList& first, SimpleList& second) {
    first.Swap(second);
}

size_t SimpleList::Size() const {
    return size;
}

bool SimpleList::Empty() const {
    return size == 0;
}

void SimpleList::PushBack(std::string str) {
    Node* newNode = new Node();
    newNode->data = std::move(str);
    Link(newNode, back->prev);
} 

void SimpleList::PopBack() {
    if (!Empty()) {
        Unlink(back->prev);
    }
}

void SimpleList::PushFront(std::string str) {
    Node* newNode = new Node();
    newNode->data = std::move(str);
    Link(newNode, front);
} 

void SimpleList::PopFront() {
    if (!Empty()) {
        Unlink(front->next); 
    }
}

const std::string& SimpleList::Front() const {
    return front->next->data;
}

std::string& SimpleList::Front() {
    return front->next->data;
}

const std::string& SimpleList::Back() const {
    return back->prev->data;
}

std::string& SimpleList::Back() {
    return back->prev->data;
}

void SimpleList::Clear() {
    while (Size() > 0) {
        PopBack();
    }
    size = 0;
}

void Swap(SimpleList& first, SimpleList& second) {
    first.Swap(second);
}
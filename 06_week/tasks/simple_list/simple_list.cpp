#include <memory>
#include <stdexcept>
#include <utility>   // std::exchange

class SimpleList {
    struct Node {
        std::string value;
        
        Node* prev;
        Node* next;

        Node() = delete; // подстраховка для корректной инициализации фиктивного узла
        Node(const std::string& val) 
            : value(val), prev(this), next(this) 
        {}
        Node(std::string&& val) 
            : value(std::move(val)), prev(this), next(this) 
        {}
    };

public:
    struct Iterator { 
        Node* head; 
        Node* cur; 
        
        Iterator(Node* h, Node* c) noexcept : head(h), cur(c) {} 
        std::string& operator*() const noexcept { return cur->value; } 
        std::string* operator->() const noexcept { return std::addressof(cur->value); } 
        Iterator& operator++() noexcept { cur = cur->next; return *this; } 
        Iterator operator++(int) noexcept { Iterator tmp = *this; ++*this; return tmp; } 
        bool operator==(const Iterator& o) const noexcept { return cur == o.cur; } 
        bool operator!=(const Iterator& o) const noexcept { return cur != o.cur; } 
    };

    struct ConstIterator { 
        const Node* head; 
        const Node* cur; 
        
        ConstIterator(const Node* h, const Node* c) noexcept : head(h), cur(c) {} 
        const std::string& operator*() const noexcept { return cur->value; } 
        const std::string* operator->() const noexcept { return std::addressof(cur->value); } 
        ConstIterator& operator++() noexcept { cur = cur->next; return *this; } 
        ConstIterator operator++(int) noexcept { ConstIterator tmp = *this; ++*this; return tmp; } 
        bool operator==(const ConstIterator& o) const noexcept { return cur == o.cur; } 
        bool operator!=(const ConstIterator& o) const noexcept { return cur != o.cur; } 
    };

public:
    SimpleList() = default;

    SimpleList(const SimpleList& other);
    SimpleList& operator=(const SimpleList& other);

    SimpleList(SimpleList&& other) noexcept;
    SimpleList& operator=(SimpleList&& other) noexcept;

    ~SimpleList();

    void PushBack(const std::string& value);    // std::string s("ex"); PushBack(s);
    void PushBack(std::string&& value);         // PushBack("ex"); PushBack(std::string("ex"));

    void PushFront(const std::string& value);
    void PushFront(std::string&& value);

    void PopBack();
    void PopFront();

    std::string& Front();
    const std::string& Front() const;

    std::string& Back();
    const std::string& Back() const;

    size_t Size() const noexcept;
    bool Empty() const noexcept;

    void Swap(SimpleList& other);
    void Swap(SimpleList& lhs, SimpleList& rhs);

    void Clear();

    friend Iterator begin(SimpleList& v) noexcept;
    friend Iterator end(SimpleList& v) noexcept ;
    friend ConstIterator begin(const SimpleList& v) noexcept;
    friend ConstIterator end(const SimpleList& v) noexcept;
    
private:
    static Node* MakeDefaultNode() { return new Node{{}}; }

    /* Link / unlink для модели с nullptr
    void Unlink(Node* node) 
    {
        if (node->prev)
            node->prev->next = node->next;

        if (node->next)
            node->next->prev = node->prev;

        delete node;
    }

    void Link(Node* pos, Node* node, bool before) 
    {
        if (before) {
            if (pos->prev)
                pos->prev->next = node;
                
            node->prev = pos->prev;
            node->next = pos;
            
            pos->prev = node;
        } else {
            if (pos->next)
                pos->next->prev = node;

            node->prev = pos;
            node->next = pos->next;

            pos->next = node;
        }
    } //*/

    void Unlink(Node* node) 
    { 
        node->prev->next = node->next; 
        node->next->prev = node->prev; 
        --size_;

        delete node;
    }

    void Link(Node* pos, Node* node, bool before = false) 
    {
        if (before) { // pos->prev -> node -> pos
            pos->prev->next = node;
                
            node->prev = pos->prev;
            node->next = pos;
            
            pos->prev = node;
        } else {     // pos -> node -> pos->next
            pos->next->prev = node;

            node->prev = pos;
            node->next = pos->next;

            pos->next = node;
        }
        ++size_;
    }

    void PushBack(Node* node)
    {
        Link(head_->prev, node);
    }

    void PushFront(Node* node)
    {
        Link(head_->next, node, true);
    }

private:
    /**
     * @brief Указатель на фиктивный узел
     *
     * Не хранит данные.
     * 
     * - Его @c next указывает на первый элемент.
     * - Его @c prev указывает на последний элемент.
     *
     * @note В пустом списке 
     * head_->next == head_ и head_->prev == head_.
     */
    Node* head_ = MakeDefaultNode();

    size_t size_ = 0;
};

void Swap(SimpleList& lhs, SimpleList& rhs)
{
    lhs.Swap(rhs);
}

SimpleList::Iterator begin(SimpleList& v) noexcept 
{ 
    return SimpleList::Iterator(v.head_, v.head_->next);
} 
SimpleList::Iterator end(SimpleList& v) noexcept 
{ 
    return SimpleList::Iterator(v.head_, v.head_);
} 
SimpleList::ConstIterator begin(const SimpleList& v) noexcept 
{ 
    return SimpleList::ConstIterator(v.head_, v.head_->next); 
} 
SimpleList::ConstIterator end(const SimpleList& v) noexcept 
{ 
    return SimpleList::ConstIterator(v.head_, v.head_); 
}

// --------------------
//
// --------------------

SimpleList::SimpleList(const SimpleList& other) 
    : SimpleList()
{
    for (const std::string& value : other)
        PushBack(value);
}

SimpleList& SimpleList::operator=(const SimpleList& other) 
{
    if (this != std::addressof(other)) {
        SimpleList temp(other);
        Swap(temp);
    }
    return *this;
}

SimpleList::SimpleList(SimpleList&& other) noexcept
    : head_(std::exchange(other.head_, MakeDefaultNode()))
    , size_(std::exchange(other.size_, 0))
{
    
}

SimpleList& SimpleList::operator=(SimpleList&& other) noexcept
{
    if (this != std::addressof(other)) {
        Clear();
        Swap(other);
    }
    return *this;
}

SimpleList::~SimpleList() 
{
    Clear();
    delete head_;
}

void SimpleList::Swap(SimpleList& other)
{
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
}

size_t SimpleList::Size() const noexcept
{
    return size_;
}

bool SimpleList::Empty() const noexcept 
{
    return Size() == 0;
}

void SimpleList::PushBack(const std::string& value) 
{
    auto* node = new Node{value};
    PushBack(node);
}

void SimpleList::PushBack(std::string&& value) 
{
    auto* node = new Node{std::move(value)};
    PushBack(node);
}

void SimpleList::PushFront(const std::string& value) 
{
    auto* node = new Node{value};
    PushFront(node);
}

void SimpleList::PushFront(std::string&& value) 
{
    auto* node = new Node{std::move(value)};
    PushFront(node);
}

void SimpleList::PopBack() 
{
    if (!Empty())
        Unlink(head_->prev);
}

void SimpleList::PopFront() 
{
    if (!Empty())
        Unlink(head_->next);
}

auto SimpleList::Back() -> std::string&
{
    if (Empty()) 
        throw std::out_of_range("Back() called on empty list");

    return head_->prev->value;
}

auto SimpleList::Back() const -> const std::string&
{
    if (Empty()) 
        throw std::out_of_range("Back() called on empty list");

    return head_->prev->value;
}

auto SimpleList::Front() -> std::string&
{
    if (Empty()) 
        throw std::out_of_range("Front() called on empty list");

    return head_->next->value;
}

auto SimpleList::Front() const -> const std::string&
{
    if (Empty()) 
        throw std::out_of_range("Front() called on empty list");

    return head_->next->value;
}

void SimpleList::Clear() 
{
    while (!Empty()) 
        PopFront();
}
#include <algorithm>
#include <initializer_list>
#include <vector>
#include <stack>


class Stack {
public:
    // Конструкторы (объявления)
    Stack();
    Stack(const Stack& other);

    // Методы (объявления)
    size_t Size() const;
    bool Empty() const;
    void Push(int val);
    bool Pop();
    int& Top();
    const int& Top() const;
    void Clear();
    void Swap(Stack& other);

    // Операторы (объявления)
    Stack& operator=(const Stack& other);
    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

private:
    std::vector<int> st;
};


// Конструкторы (реализации)

Stack::Stack() {};
Stack::Stack(const Stack& other) : st(other.st) {}

//Методы (реализации)

size_t Stack::Size() const {
    return st.size();
}

bool Stack::Empty() const {
    return st.empty();
}

void Stack::Push(int val) {
    st.push_back(val);
}

bool Stack::Pop() {
    if (st.empty())
        return false;
    st.pop_back();
    return true;
}

int& Stack::Top() {
    return st.back();
}

const int& Stack::Top() const {
    return st.back();
}

void Stack::Clear() {
    if (!st.empty())
        st.clear();
}

void Stack::Swap(Stack& other) {
    std::swap(st, other.st);
}

// Операторы (реализации)

Stack& Stack::operator=(const Stack& other) {
    if (this == &other)
        return *this;
    this->st = other.st;
    return *this;
}

bool Stack::operator==(const Stack& other) const {
    if (this->st.size() != other.st.size())
        return false;

    for (size_t i = 0; i < this->Size(); ++i)
        if (this->st[i] != other.st[i])
            return false;

    return true;
}

bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}
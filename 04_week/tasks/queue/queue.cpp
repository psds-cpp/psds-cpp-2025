#include <vector>
#include <stack>
#include <stdexcept>
#include <algorithm>

class Queue {
private:
    std::vector<int> in;   
    std::vector<int> out;   

    // Вспомогательный метод для перекладывания элементов
    void PrepareOut();

public:
    // Конструкторы
    Queue() = default;
    explicit Queue(size_t capacity);
    explicit Queue(const std::vector<int>& vec);
    explicit Queue(const std::stack<int>& st);
    Queue(std::initializer_list<int> list);
    
    //Методы
    void Push(int value);
    bool Pop();
    
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    
    // Операторы сравнения
    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
};

// Вспомогательный метод для перекладывания элементов
void Queue::PrepareOut() {
    if (out.empty() && !in.empty()) {
        while (!in.empty()) {
            out.push_back(in.back());
            in.pop_back();
        }
    }
}

// Конструктор от размера с резервированием памяти
Queue::Queue(size_t capacity) {
    in.reserve(capacity / 2 + 1);
    out.reserve(capacity / 2 + 1);
}

// Конструктор от вектора
Queue::Queue(const std::vector<int>& vec) {
    for (int value : vec) {
        Push(value);
    }
}

// Конструктор от стека
Queue::Queue(const std::stack<int>& st) {
    std::stack<int> temp = st;
    std::vector<int> tempVec;
    
    while (!temp.empty()) {
        tempVec.push_back(temp.top());
        temp.pop();
    }
    
    for (auto it = tempVec.rbegin(); it != tempVec.rend(); ++it) {
        Push(*it);
    }
}

// Конструктор от initializer_list
Queue::Queue(std::initializer_list<int> list) {
    for (int value : list) {
        Push(value);
    }
}

// добавляет элемент в конец очереди
void Queue::Push(int value) {
    in.push_back(value);
}

// убирает элемент из начала очереди
bool Queue::Pop() {
    if (Empty()) {
        return false;
    }
    
    PrepareOut();
    out.pop_back();
    return true;
}

// обеспечивает доступ на запись и чтение к элементу в начале очереди (неконстантная версия)
int& Queue::Front() {
    PrepareOut();
    return out.back();  
}

// обеспечивает доступ на запись и чтение к элементу в начале очереди (константная версия)
const int& Queue::Front() const {
    // Используем const_cast для вызова PrepareOut на временном объекте
    Queue* mutableThis = const_cast<Queue*>(this);
    mutableThis->PrepareOut();
    return out.back(); 
}

// обеспечивает доступ на запись и чтение к элементу в конце очереди (неконстантная версия)
int& Queue::Back() {
    if (!in.empty()) {
        return in.back();
    }
    return out.front(); 
}

// обеспечивает доступ на запись и чтение к элементу в конце очереди (константная версия)
const int& Queue::Back() const {
    if (!in.empty()) {
        return in.back();
    }
    return out.front();  
}

// возвращает результат проверки очереди на отсутствие элементов  
bool Queue::Empty() const {
    return in.empty() && out.empty();
}

// возвращает количество элементов в очереди
size_t Queue::Size() const {
    return in.size() + out.size();
}

// очищает очередь
void Queue::Clear() {
    in.clear();
    out.clear();
}

// меняется элементами с другой очередью (без копирования)
void Queue::Swap(Queue& other) {
    in.swap(other.in);
    out.swap(other.out);
}

// Оператор сравнения на равенство
bool Queue::operator==(const Queue& other) const {
    if (Size() != other.Size()) {
        return false;
    }
    //копии для сравнения
    Queue q1 = *this;
    Queue q2 = other;
    
    while (!q1.Empty()) {
        if (q1.Front() != q2.Front()) {
            return false;
        }
        q1.Pop();
        q2.Pop();
    }
    return true;
}

// Оператор сравнения на неравенство
bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}
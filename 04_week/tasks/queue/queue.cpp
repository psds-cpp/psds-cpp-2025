#include <vector>
#include <stack>
#include <algorithm>


class Queue {
    std::vector<int> input;
    std::vector<int> output;

public:
    Queue(){};
    Queue(std::vector<int> vector);
    Queue(std::stack<int> stack);
    Queue(const std::initializer_list<int>& list);
    Queue(const size_t& size);

    void Push(const int& value);

    bool Pop();

    int& Front();
    const int& Front() const;

    int& Back();
    const int& Back() const;

    bool Empty() const;

    int Size() const;

    void Clear();

    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
};


Queue::Queue(std::vector<int> vector) : output(std::move(vector)) {
    std::reverse(output.begin(), output.end());
}

Queue::Queue(std::stack<int> stack) {
    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }
}

Queue::Queue(const std::initializer_list<int>& list) : output(list) {
    std::reverse(output.begin(), output.end());
}

Queue::Queue(const size_t& size){
    input.reserve(size);
}

void Queue::Push(const int& value){
    input.push_back(value);
}

bool Queue::Pop(){
    if (input.empty() && output.empty()){
        return false;
    }

    if (output.empty()){
        output.reserve(input.size());
        while (!input.empty()){
            output.push_back(input.back());
            input.pop_back();
        }
    }
    
    output.pop_back();
    return true;
}

int& Queue::Front(){
    if (output.empty()){
        return input.front();
    } else {
        return output.back();
    }
}

const int& Queue::Front() const {
    if (output.empty()){
        return input.front();
    } else {
        return output.back();
    }
}

int& Queue::Back(){
    if (input.empty()){
        return output.front();
    } else {
        return input.back();
    }
}

const int& Queue::Back() const {
    if (input.empty()){
        return output.front();
    } else {
        return input.back();
    }
}

bool Queue::Empty() const {
    return (input.empty()) && (output.empty());
}

int Queue::Size() const {
    return input.size() + output.size();
}

void Queue::Clear(){
    input.clear();
    output.clear();
}

void Queue::Swap(Queue& other){
    std::swap(input, other.input);
    std::swap(output, other.output);
}

bool Queue::operator==(const Queue& other) const {
    // Быстрая проверка на размер
    if ((input.size() + output.size()) != (other.input.size() + other.output.size())) {
        return false;
    }

    // Вспомогательная функция для получения элемента по индексу в "виртуальном" векторе
    auto getElement = [](const Queue& q, size_t index) {
        // Сначала идут элементы из output в обратном порядке
        if (index < q.output.size()) {
            return q.output[q.output.size() - 1 - index];
        }
        // Затем элементы из input в прямом порядке
        return q.input[index - q.output.size()];
    };

    // Поэлементное сравнение без выделения памяти
    size_t totalSize = input.size() + output.size();
    for (size_t i = 0; i < totalSize; ++i) {
        if (getElement(*this, i) != getElement(other, i)) {
            return false;
        }
    }

    return true;
}

bool Queue::operator!=(const Queue& other) const {
    if (*this == other){
        return false;
    }
    return true;
}
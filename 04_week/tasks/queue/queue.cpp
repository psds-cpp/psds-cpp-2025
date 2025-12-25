#include <vector>
#include <stack>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cassert>

class Queue {
private:
    std::vector<int> input_stack;
    std::vector<int> output_stack;

    // Перекладывает элементы из input_stack в output_stack
    void TransferElements() {
        while (!input_stack.empty()) {
            output_stack.push_back(input_stack.back());
            input_stack.pop_back();
        }
    }

public:
    // Конструктор по умолчанию
    Queue() = default;

    // Конструктор от std::stack<int>
    Queue(std::stack<int> s) {
        // Извлекаем элементы из стека в обратном порядке
        std::vector<int> temp;
        while (!s.empty()) {
            temp.push_back(s.top());
            s.pop();
        }
        // Теперь добавляем в правильном порядке в output_stack
        for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
            output_stack.push_back(*it);
        }
    }

    // Конструктор от std::vector<int>
    Queue(const std::vector<int>& vec) {
        output_stack = vec;
        std::reverse(output_stack.begin(), output_stack.end());
    }

    // Конструктор от std::initializer_list<int>
    Queue(std::initializer_list<int> init_list) {
        output_stack.assign(init_list.begin(), init_list.end());
        std::reverse(output_stack.begin(), output_stack.end());
    }

    // Конструктор от размера очереди
    explicit Queue(size_t capacity) {
        input_stack.reserve(capacity / 2 + 1);
        output_stack.reserve(capacity / 2 + 1);
    }

    // Добавляет элемент в конец очереди
    void Push(int value) {
        input_stack.push_back(value);
    }

    // Убирает элемент из начала очереди
    bool Pop() {
        if (Empty()) {
            return false;
        }

        if (output_stack.empty()) {
            TransferElements();
        }

        output_stack.pop_back();
        return true;
    }

    // Доступ на чтение и запись к элементу в начале очереди
    int& Front() {
        if (Empty()) {
            // Для безопасности добавим assert
            assert(!Empty() && "Queue is empty");
        }

        if (output_stack.empty()) {
            TransferElements();
        }

        return output_stack.back();
    }

    // Константная версия Front
    const int& Front() const {
        if (Empty()) {
            assert(!Empty() && "Queue is empty");
        }
        
        // Если output_stack пуст, значит все элементы в input_stack
        // и первый элемент очереди - первый элемент input_stack
        if (output_stack.empty()) {
            // input_stack.front() - O(1), не меняет объект
            return input_stack.front();
        }
        
        // Иначе первый элемент - последний в output_stack
        return output_stack.back();
    

    // Доступ на чтение и запись к элементу в конце очереди
    int& Back() {
        if (Empty()) {
            assert(!Empty() && "Queue is empty");
        }

        if (!input_stack.empty()) {
            return input_stack.back();
        } else {
            return output_stack.front();
        }
    }

    // Константная версия Back
    const int& Back() const {
        if (Empty()) {
            assert(!Empty() && "Queue is empty");
        }

        if (!input_stack.empty()) {
            return input_stack.back();
        } else {
            return output_stack.front();
        }
    }

    // Проверка очереди на отсутствие элементов
    bool Empty() const {
        return input_stack.empty() && output_stack.empty();
    }

    // Возвращает количество элементов в очереди
    size_t Size() const {
        return input_stack.size() + output_stack.size();
    }

    // Очищает очередь
    void Clear() {
        input_stack.clear();
        output_stack.clear();
    }

    // Меняется элементами с другой очередью
    void Swap(Queue& other) {
        if (this != &other) {
            input_stack.swap(other.input_stack);
            output_stack.swap(other.output_stack);
        }
    }

    // Оператор сравнения на равенство
    bool operator==(const Queue& other) const {
        if (Size() != other.Size()) {
            return false;
        }

        if (Empty() && other.Empty()) {
            return true;
        }

        // Создаем копии для безопасного сравнения
        Queue copy1 = *this;
        Queue copy2 = other;

        while (!copy1.Empty() && !copy2.Empty()) {
            if (copy1.Front() != copy2.Front()) {
                return false;
            }
            copy1.Pop();
            copy2.Pop();
        }

        return copy1.Empty() && copy2.Empty();
    }

    // Оператор сравнения на неравенство
    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }
};
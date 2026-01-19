#include <vector>


class Stack {
private:
    std::vector<int> stack;
public:
    //Объявление методов
    void Push(int val);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& stack2);
    friend bool operator==(const Stack& lhs, const Stack& rhs);
    friend bool operator!=(const Stack& lhs, const Stack& rhs);
};

//Реализация методов
void Stack::Push(int val){
    stack.push_back(val);
}

bool Stack::Pop(){
    if (stack.empty()){
        return false;
    } else{
        stack.pop_back();
        return true;
    }
}

int& Stack::Top(){
    return stack.back();
}
//Перегрузка Top
const int& Stack::Top() const{
    return stack.back();
}

bool Stack::Empty() const{
    return stack.empty();
}

size_t Stack::Size() const{
    return stack.size();
}

void Stack::Clear(){
    stack.clear();
}

void Stack::Swap(Stack& stack2){
    stack.swap(stack2.stack);
}

//Операторы
bool operator==(const Stack& lhs, const Stack& rhs){
    return lhs.stack == rhs.stack;
}

bool operator!=(const Stack& lhs, const Stack& rhs){
    return lhs.stack != rhs.stack;
}
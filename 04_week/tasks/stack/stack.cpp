#include <vector>


class Stack {
  public:
    // методы:
    
    void Push(int newData); // Добавление нэлемента в стек
    
    bool Pop(void); // удаление элемента с верхушки стека
    
    int& Top();   // Доступ к элементу на вершине стека
    
    const int& Top() const; // Доступ к элементу на вершине стека
    
    bool Empty() const; // Проверка отсутсвия элементов на вершине
    
    size_t Size() const;      // Размер стека
    
    void Clear();       // Очистка стека
    
    void Swap(Stack& other);  // меняем местами элементы
    
    // определение для ==
    bool operator==(const Stack& x) const {return data == x.data;}
    
    // определение для !=
    bool operator!=(const Stack& x) const {return !(data == x.data);}
    
  private:
    std::vector<int> data;  //   данные

};



// в Методах для Stack используем методы для vector

void Stack::Push(int newData){
  data.push_back(newData);
}

bool Stack::Pop(void){
  if(data.empty())  return false;
  data.pop_back();
  return true;
}
    
int& Stack::Top(){ 
  return data.back();
}
    
const int& Stack::Top() const{ 
  return data.back();
}

bool Stack::Empty() const{
  return data.empty();
}

size_t Stack::Size() const{
  return data.size();
}

void Stack::Clear() {
  data.clear();
}

void Stack::Swap(Stack& other){
  data.swap(other.data);
}
    

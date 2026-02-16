/*
  Представление строки
  Необходимо реализовать класс StringView, представляющий упрощенную реализацию std::string_view. В отличие от std::string данный класс не владеет строкой (ресурсами), а хранит лишь размер и указатель на начало строки. Это позволяет быстро создавать представление строки, копировать и создавать подстроки. Важно понимать, что поскольку StringView не владеет строкой, а лишь наблюдает за оригинальной строкой, то при изменении оригинала представление тоже изменится. При этом сам класс StringView не может изменять строку, за которой наблюдает.
  
  Класс предоставляет следующий функционал:
  
  Конструктор от std::string, позиции начала подстроки (по умолчанию 0) и длину наблюдаемой подстроки (по умолчанию аналог std::string::npos). Длину подстроки следует обрезать, если она превышает длину строки. Если начало превышает длину, то следует создать StringView с параметрами по умолчанию
  Конструктор от C-строки
  Конструктор от C-строки и длины
  Оператор [] - доступ на чтение символа
  Метод Data - возвращает указатель на начало наблюдаемой строки
  Метод Front - доступ на чтение к первому символу.
  Метод Back - доступ на чтение к последнему символу.
  Методы Size, Length - возвращают длину наблюдаемой строки
  Метод Empty - проверяет на пустоту
  Метод RemovePrefix - убирает заданное количество символов из начала представления
  Метод RemoveSuffix - убирает заданное количество символов с конца представления
  Метод Substr - может принимать позицию начала поиска и количество элементов и возвращает StringView. В случае, когда подстрока начала поиска превышает длину строки, следует вернуть пустое представление
  Метод Find - принимает символ или StringView и позицию начала поиска (по умолчанию 0), возвращает позицию начала совпадения элемента (или аналог std::string::npos)
  Метод ToString - создает std::string на основе представления
  Примечание
  Запрещено использовать std::string_view в реализации
  Передавать std::string по значению в первый конструктор очень плохая идея
  Получить длину C-строки можно с помощью функции strlen.
  Не забудьте про константность методов
*/


#include <cstring>
#include <string>


class StringView {

private:
    const char* data_;
    size_t size_;

public:
    inline static const size_t npos = static_cast<size_t>(-1);

    StringView() : data_(nullptr), size_(0) {}    // Конструктор по умолчанию


/*
  Конструктор от std::string, позиции начала подстроки (по умолчанию 0) и длину наблюдаемой подстроки (по умолчанию аналог std::string::npos). 
  Длину подстроки следует обрезать, если она превышает длину строки. Если начало превышает длину, то следует создать StringView с параметрами по умолчанию
*/
  StringView(const std::string& str, size_t pos = 0, size_t len = npos) {  // -1 т.к. цитата "Константа объявлена как -1. Это связано с тем, что size_t — тип беззнакового целого числа, и -1 — наибольшее возможное представимое значение для этого типа."
      if(str.size() <= pos)  // проверка, что длина строки больше чем позиция начала.
      {
          data_ = nullptr;
          size_ = 0;
          return;
      }
      
      data_ = str.data() + pos;
    
      size_t maxLen = str.size() - pos;
      if ((len == npos) || (len > maxLen)) size_ = maxLen;  // вышли, обризаем длину
      else  size_ = len;
  }

//Конструктор от C-строки
 StringView(const char* str){
      if (str == nullptr) {  // проверка на пустую строку
        data_ = nullptr;
        size_ = 0;
        return;
      }
      
      data_ = str;
      size_ = std::strlen(str);  // расчет схдлины строки средством strlen
 }
  

//Конструктор от C-строки и длины
 StringView(const char* str, size_t len){
      if (str == nullptr) {  // проверка на пустую строку
        data_ = nullptr;
        size_ = 0;
        return;
      }  
      // проверки на 0ю длину строки нет т.к. 0 - валидная длина.
      data_ = str;
      size_ = len;  
 }

//Оператор [] - доступ на чтение символа
char operator[](size_t pos) const { return data_[pos]; }

//Метод Data - возвращает указатель на начало наблюдаемой строки
const char* Data() const { return data_; }

// Метод Front - доступ на чтение к первому символу.
char Front() const { return data_[0]; }

//  Метод Back - доступ на чтение к последнему символу.
char Back() const { return data_[size_ -1]; }

//   Методы Size, Length - возвращают длину наблюдаемой строки
    size_t Size() const { return size_;}
    size_t Length() const { return size_; }

//   Метод Empty - проверяет на пустоту
    bool Empty() const {
       if(size_ == 0) return true;
       return false;
    }

//   Метод RemovePrefix - убирает заданное количество символов из начала представления 
    void RemovePrefix(size_t len) {  // по идее тут надо проверить кооректность, а именно что длина должна быть меньше size_ len 
        if (len >= size_) {
            data_ = nullptr;
            size_ = 0;
        } 
        else {
            data_ += len;
            size_ -= len;
        }
    }

//   Метод RemoveSuffix - убирает заданное количество символов с конца представления
    void RemoveSuffix(size_t len) { 
        if (len >= size_) {
            data_ = nullptr;
            size_ = 0;
        } 
        else    size_ -= len;
        
    }

//   Метод Substr - может принимать позицию начала поиска и количество элементов и возвращает StringView. В случае, когда подстрока начала поиска превышает длину строки, следует вернуть пустое представление
    StringView Substr(size_t pos = 0, size_t len = npos) const {
        if (pos >= size_) { return StringView(); }  // В случае, когда подстрока начала поиска превышает длину строки, следует вернуть пустое представление
        
        size_t newSize = size_ - pos;
        if ((len != npos) && (len < newSize)) newSize = len;
        
        return StringView(data_ + pos, newSize);
    }
//   Метод Find - принимает символ или StringView и позицию начала поиска (по умолчанию 0), возвращает позицию начала совпадения элемента (или аналог std::string::npos)

   size_t Find(char symb, size_t pos = 0) const {
     
        for (size_t i = pos; i < size_; ++i) {
            if (data_[i] == symb) return i;
        }
     
        
        return npos;  //не совпало
    }
// переопределение Find ддля строки
    size_t Find(const StringView& str, size_t pos = 0) const {
        if ((pos >= size_) || ((pos + str.size_) >= size_)) return npos;
      
        if(str.Empty()) {
          if(pos == 0)  return 0;
          return npos;
        }

        size_t i = pos;    // индекс проверяемой позиции
        size_t j = 0;      // счетчик совпадений

        while(i < size_)  // првоеряемая должна быть меньше размера строки
        {
          if(str.data_[j] == data_[i])  j++;  // элементы совпали, инкриментируем счетчик совпадений
          else                         j = 0;

          if(j == str.size_)  return i-j+1;  // длина строки совпала с количеством совпадений, значит нашли совпадение
          
          i++;
        }
        
        return npos;
    }

    // Преобразование в std::string
    std::string ToString() const {
        if (data_ == nullptr || size_ == 0) {
            return std::string();
        }
        return std::string(data_, size_);
    }

};

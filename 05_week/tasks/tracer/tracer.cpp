/*
  Трассировщик
Необходимо реализовать класс Tracer, подсчитывающий вызовы своих конструкторов, операторов присваивания и деструктора.

В качестве данных внутри класса должна храниться имя std::string и идентификатор.

В классе присутствуют следующие счетчики, доступные извне:

count - общее количество созданных объектов (используется для генерации id)
default_ctor - количество вызовов конструктора по умолчанию
str_ctor - количество вызовов конструктора от строки
copy_ctor - количество вызовов конструктора копирования
move_ctor - количество вызовов конструктора перемещения
copy_assign - количество вызовов оператора копирующего присваивания
move_assign - количество вызовов оператора перемещающего присваивания
dtor - количество вызовов деструктора
alive - количество живых объектов в данный момент
Правила изменения идентификатора (id):

присваивается при создании и НЕ меняется в течение жизни объекта
каждый новый объект получает уникальный id (увеличивающийся счетчик)
при использовании операторов не изменяется
Класс предоставляет следующий функционал:

Конструктор по умолчанию - создает объект с именем obj_{id} ("obj_1")
Конструктор от строки std::string - создает объект с именем {name}_{id}
Конструктор копирования - копирует имя, но создает id
Конструктор перемещения - перемещает имя, но создает id
Оператор присваивания копированием - копирует имя, не изменяет id
Оператор перемещения копированием - перемещает имя, не изменяет id
Деструктор - изменяет свои счетчики
Метод Id - возвращает идентификатор объекта
Метод Name - возвращает константную ссылку на имя.
Метод Data - возвращает указатель на данные строки.
Метод ResetStats - сбрасывает на 0 все счетчики
Примечание
Для удобства отладки можно написать функции, выводящие на экран статистики и логирующие действия.
*/

#include <string>



class Tracer {
private:
  size_t id_;
  std::string name_;
   

public:
  // static для переменных, тогда при вызове значение будет известно предыдущее значение. 
  static size_t count; //- общее количество созданных объектов (используется для генерации id)
  static size_t default_ctor; // - количество вызовов конструктора по умолчанию
  static size_t str_ctor; // - количество вызовов конструктора от строки
  static size_t copy_ctor; // - количество вызовов конструктора копирования
  static size_t move_ctor; // - количество вызовов конструктора перемещения
  static size_t copy_assign; // - количество вызовов оператора копирующего присваивания
  static size_t move_assign; // - количество вызовов оператора перемещающего присваивания
  static size_t dtor; // - количество вызовов деструктора
  static size_t alive; // - количество живых объектов в данный момент

  Tracer(): id_(++count), name_ ("obj_" + (std::to_string(count))){
      ++default_ctor;
      ++alive;
  }

  Tracer(const std::string data) : id_(++count), name_ (data +"_" + (std::to_string(count))){
      ++default_ctor;
      ++alive;
  }

  Tracer(const Tracer& data) : id_(++count), name_(data.name_) {
      ++copy_ctor;
      ++alive;
  }

  Tracer(Tracer&& other) : id_(++count), name_(std::move(data.name_)){
        ++move_ctor;
        ++alive;
    }
    
    Tracer& operator=(const Tracer& data) {  // копирует имя, не изменяет id
        if (this != &data) {
            name_ = data.name_;
            ++copy_assign;
        }
        return *this;
    }
    
    Tracer& operator=(Tracer&& data) {    // перемещает имя, не изменяет id
        if (this != &data) {
            name_ = std::move(other.name_);
            ++move_assign;
        }
        return *this;
    }

    // Деструктор
    ~Tracer() {
        ++dtor;
        --alive;
    }
    
    // Методы доступа
    size_t Id() const { return id_; }
    const std::string& Name() const { return name_; }
    const char* Data() const { return name_.c_str(); }

  static void ResetStats() {
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
  }


};


// Инициализация статических членов класса
size_t Tracer::count = 0;
size_t Tracer::default_ctor = 0;
size_t Tracer::str_ctor = 0;
size_t Tracer::copy_ctor = 0;
size_t Tracer::move_ctor = 0;
size_t Tracer::copy_assign = 0;
size_t Tracer::move_assign = 0;
size_t Tracer::dtor = 0;
size_t Tracer::alive = 0;

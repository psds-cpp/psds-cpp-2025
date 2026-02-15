#include <string>
//#include <iostream>   //Для отладки
/*
класс `Tracer`, должен считать вызовы своих конструкторов, операторов присваивания и деструктора.
В качестве данных внутри класса должна храниться имя `std::string` и идентификатор.
Идентификатор. Особенности изменения:
 1 присваивается при создании и **НЕ** меняется в течение жизни объекта
 2 каждый новый объект получает уникальный id (увеличивающийся счетчик)
 3 при использовании операторов не изменяется
 -Для начала обозначим все поля и методы, а затем перейдем к реализации
 -Для удобства отладки можно написать функции, выводящие на экран статистики
  и логирующие действия.
- Добавил static к счетчикам
-Также была проблема  в том что при вызове метода Id у объекта, не проходил тест по названию obj_n. Там лежал мусор, связано с тем что сначала инициализировался name_
А только потом id_, крч не в том порядке объявил и использовал, щас всё хорошо

*/

class Tracer {
private:
    int id_;
    std::string name_;
    static int nextId;              //СОздание уникальных id 
public:
//счетчики
    static int count;              // общее количество созданных объектов
    static int default_ctor;       // количество вызовов конструктора по умолчанию
    static int str_ctor;            // количество вызовов конструктора от строки
    static int copy_ctor;           // количество вызовов конструктора копирования
    static int move_ctor;           // количество вызовов конструктора перемещения
    static int copy_assign;         // количество вызовов оператора копирующего присваивания
    static int move_assign;         // количество вызовов оператора перемещающего присваивания
    static int dtor;                // количество вызовов деструктора
    static int alive;               // количество живых объектов в данный момент
  
//Конструкторский отдел
    Tracer();                              // Конструктор по умолчанию
    Tracer(std::string name);              // Конструктор от строки
    Tracer(const Tracer& other);           // Конструктор копирования
    Tracer(Tracer&& other) noexcept;       // Конструктор перемещения
    ~Tracer() {
    dtor++;
    alive--;
}
    Tracer& operator=(const Tracer& other); // Оператор копирующего присваивания
    Tracer& operator=(Tracer&& other) noexcept; // Оператор перемещающего присваивания. Используем изученные &&. Показываем что это временный объект, которого будем грабить                   
// Методы
    int Id() const { return id_; }                    // Возвращает идентификатор
    const std::string& Name() const { return name_; } // Возвращает константную ссылку на имя
    const char* Data() const { return name_.data(); } // Возвращает указатель на данные строки

//Дополнительно
    static void ResetStats();
};

//инициализируем счетчики
int Tracer::nextId = 1;
int Tracer::count = 0;
int Tracer::default_ctor = 0;
int Tracer::str_ctor = 0;
int Tracer::copy_ctor = 0;
int Tracer::move_ctor = 0;
int Tracer::copy_assign = 0;
int Tracer::move_assign = 0;
int Tracer::dtor = 0;
int Tracer::alive = 0;

//Реализации конструкторов
Tracer::Tracer() : 
    id_(nextId++), 
    name_("obj_" + std::to_string(id_))
{
    ++count;
    ++default_ctor;
    ++alive;    
}

Tracer::Tracer(std::string name) : 
    id_(nextId++),
    name_(name + "_" + std::to_string(id_))
{
    ++count;
    ++str_ctor;
    ++alive;
}

Tracer::Tracer(const Tracer& other) :
    id_(nextId++),
    name_(other.name_)  // Копируем имя
{
    ++count;
    ++copy_ctor;
    ++alive;
}

Tracer::Tracer(Tracer&& other) noexcept :
    id_(nextId++),
    name_(std::move(other.name_))  // Перемещаем имя
{
    ++count;
    ++move_ctor;
    ++alive;
    
    // После перемещения other.name_ становится пустым (гарантировано std::string)
}

//Реализации операторов присваивания
Tracer& Tracer::operator=(const Tracer& other) {
    if (this != &other) {  // Проверка на самоприсваивание
        name_ = other.name_;  // Копируем имя, id не меняется
        copy_assign++;
    }
    // При самоприсваивании ничего не делаем и не увеличиваем счетчик
    return *this;
}

Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_);  // Перемещаем имя, id не меняется
        move_assign++;
    }
    // При самоприсваивании ничего не делаем и не увеличиваем счетчик
    return *this;
}

//Метод сброса статистики
void Tracer::ResetStats() {
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0; 
    nextId = 1;
}



//////////////////////////////////////////////////ТипоОтладка///////////////////////////////////////////////////////////
// void TracerStats() {
//     std::cout << "Статистика" << std::endl;
//     std::cout << "Создали обхектов: " << Tracer::count << std::endl;
//     std::cout << "конс-р по умолчанию: " << Tracer::default_ctor << std::endl;
//     std::cout << "конс-р со строкой: " << Tracer::str_ctor << std::endl;
//     std::cout << "копирующий конс-р: " << Tracer::copy_ctor << std::endl;
//     std::cout << "конрс-р перемещ-я: " << Tracer::move_ctor << std::endl;
//     std::cout << "вызовы копирующ-го опера присв-я: " << Tracer::copy_assign << std::endl;
//     std::cout << "вызовы перемещающего опера присв-я:: " << Tracer::move_assign << std::endl;
//     std::cout << "Вызовов диструктора: " << Tracer::dtor << std::endl;
//     std::cout << "Осталось выживших после бури: " << Tracer::alive << std::endl;
// }

// int main() {
// // Для отладки 
// Tracer obj_1;
// Tracer obj_2;

// TracerStats();
// Tracer::ResetStats();
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
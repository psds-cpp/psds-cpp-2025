/*
  Коровья строка
Существуют разные подходы к управлению данными при копировании. Можно выделить следующие семантики:

value-семантика - при копировании объекта происходит глубокое копирование (deep copy), все значения полностью объекта полностью копируются (реализовано в большинстве классов стандартной библиотеки C++).
reference-семантика - при копировании объекта его содержимое не копируется, а разделяется между копиями посредством ссылки или указателя. Также существует подход, который называют поверхностное копирование (shallow copy), когда происходит копирование только верхнего уровня оригинального объекта, а ссылки на внутренние части объекта остаются общими (реализовано по умолчанию в некоторых других языках).
cow-семантика (copy-on-write) - при копировании объекта создается shallow copy, что позволяет использовать объект на чтение без дополнительных затрат ресурсов, но при изменении объекта создается настоящая глубокая копия и изменения вносятся уже в копию. Таким образом, копирование совершается только при внесении изменений, что в определенных сценариях использования объекта позволяет увеличить производительность и уменьшить затраты на ресурсы.
Cow-семантика применяется в реализации строк Яндекса и фреймворка Qt.

Необходимо реализовать класс CowString, который представляет собой упрощенную реализацию строки с copy-on-write семантикой.

Класс предоставляет следующий функционал:

Конструктор по умолчанию — создает пустую строку
Конструктор от const char*
Конструктор от std::string
Конструктор копирования — увеличивает счетчик ссылок, не копирует данные
Оператор присваивания копированием — увеличивает счетчик ссылок, не копирует данные
Конструктор перемещения
Оператор присваивания перемещением
Деструктор
Методы НЕ вызывающие копирования:

Метод Size - возвращает длину строки без учета терминирующего нуля \0
Метод ToCstr - возвращает указатель на данные
Метод ToString - возвращает std::string
Оператор [] - доступ к символу для чтения
Оператор неявного преобразования к C-строке
Методы, обеспечивающие модификацию на собственной копии данных:

Оператор [] - доступ к символу для записи
Метод Append - добавляет строку из C-строки или std::string
Метод Substr - принимает позицию и количество символов (по умолчанию от начала до конца строки), возвращает соответствующую подстроку. Если позиция начала превышает длину, то возвращаем пустую строку.
Метод Clear - очистка строки
Для реализации строки удобно вынести все необходимые поля в отдельную структуру и кроме этого хранить в ней счетчик ссылок ref_count.

Правильно поддерживая ref_count всегда будет известно, когда нужно удалять данные строки или когда нужно превращать shallow-copy в deep-copy.

Примечание
Запрещено использовать std::string в реализации и умные указатели
Рекомендуется определять методы вне класса
При необходимости вспомогательные методы реализуются в закрытой части класса
Тесты оператор [] не проверяют на индекс вне диапазона
Проблемы реализации
В предполагаемой реализации имеется следующая проблема: при использовании модифицирующей версии оператора [] пользователь может сохранить ссылку и модифицировать символ позже, что нарушит cow-семантику. Для упрощения решать её не требуется. В Qt используют QCharRef для решения этой проблемы.
*/
#include <cstring>
#include <algorithm>

class CowString {
private:
    struct StringData {
        char* data;   // указатель на данные
        size_t size;  // размер
        size_t capacity;    // емкость
        int ref_count;    //  // количество копий. int а не size_t т.к. проще отслеживать переход через 0

        StringData(const char* buf, size_t len) : size(len), capacity(len + 1), ref_count(1) {
            data = new char[capacity];      // выделение места для данных
            for(size_t i = 0; i < len; i++) data[i] = buf[i]; // копирование данных
            data[len] = '\0'; // последний символ
        }


        StringData(size_t cap) : size(0), capacity(cap), ref_count(1) {
            data = new char[capacity];
            data[0] = '\0'; // обнуление нулевого он же последний элемент
        }

        
        // Диструктор
        ~StringData() { delete[] data;}


        void release_ref() {
            if (--ref_count == 0) {
                delete this;
            }
        }
    };

    StringData* str_data;

    void detach() {
        if (str_data->ref_count > 1) {
            StringData* new_data = new StringData(str_data->data, str_data->size);
            str_data->release_ref();
            str_data = new_data;
        }
    }

    void ensure_unique() {
        if (str_data->ref_count > 1) {
            StringData* new_data = new StringData(str_data->data, str_data->size);
            str_data->release_ref();
            str_data = new_data;
        }
    }

public:
    inline static const size_t npos = -1;

    // Конструктор по умолчанию — создает пустую строку
    CowString() : str_data(new StringData(1)) {}


    // Конструктор от const char*
    CowString(const char* str) {
        size_t len = 1; // если nullptr то останится 1
        
        if (str != nullptr) len = std::strlen(str); // не nullptr значит задаем длину

        str_data = new StringData(str, len);
    }


    // Конструктор от std::string
    CowString(const std::string& str) : str_data(new StringData(str.c_str(), str.length())) {}

    // Конструктор копирования — увеличивает счетчик ссылок, не копирует данные
    CowString(const CowString& other) : str_data(other.str_data) {
        str_data->ref_count++;  // 
    }


    // Оператор присваивания копированием — увеличивает счетчик ссылок, не копирует данные
    CowString& operator=(const CowString& obj) {
        if (this != &obj){    // есть, что копирвать.
          str_data->release_ref() ;
          str_data = obj.str_data;
          str_data->ref_count++;
        }
        return *this;  
    }


    // Конструктор перемещения
    CowString(CowString&& other) noexcept : str_data(other.str_data) { other.str_data = new StringData(1); }  // новую структуру создали при заполнении полей, сейчас надо "освободить" перемещенную.



    // Оператор присваивания перемещением
    CowString& operator=(CowString&& obj) noexcept {
        if (this != &obj) { // перемещние обьекта, проверяем, что перемещаем не сами себя
            str_data->release_ref();
            str_data = obj.str_data;
            obj.str_data = new StringData(1);
        }
        return *this;
    }


    // Деструктор
    ~CowString() { str_data->release_ref();}




    //Оператор неявного преобразования к C-строке
// Оператор неявного преобразования к C-строке
// Методы, обеспечивающие модификацию на собственной копии данных:
    // Метод Size - возвращает длину строки без учета терминирующего нуля \0
    size_t Size() const { return str_data->size; }

    // Метод ToCstr - возвращает указатель на данные
    const char* ToCstr() const { return str_data->data; }

    // Метод ToString - возвращает std::string
    std::string ToString() const { return std::string(str_data->data, str_data->size); }

    // Оператор [] - доступ к символу для чтения
    const char& operator[](size_t i) const {  return str_data->data[i]; }

    // Оператор неявного преобразования к C-строке
    operator const char*() const { return str_data->data; }
    

// Методы, обеспечивающие модификацию на собственной копии данных:
    // Оператор [] - доступ к символу для записи
    char& operator[](size_t i) {
        ensure_unique();
        return str_data->data[i];
    }

    // Метод Append - добавляет строку из C-строки 
    CowString& Append(const char* obj) {
        if (obj == nullptr || *obj == '\0') return *this; // проверка на самого себя
        
        size_t len = std::strlen(obj);  // длина
        
        if (len == 0) return *this; // защита

        ensure_unique();
        
        size_t new_size = str_data->size + len; // расчет новой емкости буфера
        // возмоно емкостьисходного больше чем требуется для результирующей строки
        if (new_size + 1 > str_data->capacity) {// добавляем строку
            size_t new_capacity = new_size + 1; // 
            StringData* new_data = new StringData(new_capacity);  // выделение памяти под увеличенную строку
 //           for(size_t i = 0; i < str_data->size; i++)  new_data->data[i] = str_data->data[i];
 //           for(size_t i = 0; i < len; i++)  new_data->data[new_size - len + i] = obj->data[i];
            std::memcpy(new_data->data, str_data->data, str_data->size);  // перемещение первойчасти
            std::memcpy(new_data->data + str_data->size, obj, len);       // перемещение второй части
            new_data->data[new_size] = '\0';
            new_data->size = new_size;
            
            str_data->release_ref();
            str_data = new_data;
        } 
        else {
            std::memcpy(str_data->data + str_data->size, obj, len); // перемещение
            str_data->size = new_size;
            str_data->data[new_size] = '\0';
        }
        
        return *this;
    }

    // Метод Append для std::string
    CowString& Append(const std::string& str) { return Append(str.c_str()); }

    // Метод Substr - принимает позицию и количество символов (по умолчанию от начала до конца строки), возвращает соответствующую подстроку. Если позиция начала превышает длину, то возвращаем пустую строку.
    CowString Substr(size_t pos = 0, size_t count = npos) const {
        if (pos >= str_data->size) return CowString();  // проверкаб что позиция не больше размера 

        size_t start = pos;
        size_t len = ((count == npos) || (count > str_data->size - pos)) ? str_data->size - pos : count;

        char* buf = new char[len + 1];  // выделение места для данных
        std::memcpy(buf, str_data->data + start, len); // копирование данных
        buf[len] = '\0';             // последний символ
        
        CowString result(buf);       // формируем даныне
        delete[] buf;               // освобождение памяти
        
        return result;
    }

    // Метод Clear
    void Clear() {
        if (str_data->size == 0) return;  // данных нет

        if (str_data->ref_count > 1) {  // не первая копия. очищаем и удаляем
            str_data->release_ref();
            str_data = new StringData(1);
        } 
        else {  // первый экземпляр, просто очистка размера и данных
            str_data->size = 0;
            str_data->data[0] = '\0';
        }
    }

    // Метод Empty
    bool Empty() const { return str_data->size == 0; }  // Сокращаем размер до 0

    // Метод Find для символа
    size_t Find(char symbl, size_t i = 0) const {
        if (i >= str_data->size)  return npos;    // искомая позиция вне размера данных

        for (size_t j = i; j < str_data->size; ++j) 
            if (str_data->data[j] == symbl)  return j;  // Символ найден
        

        return npos;  // ничего не найдено
    }

    // Метод Find для C-строки
    size_t Find(const char* str, size_t pos = 0) const {
        if (str == nullptr) return npos;  // пустой указатель

        if (*str == '\0')  return 0; // оказались в конце строки

        if (pos >= str_data->size) return npos;   // начало поиска больше размера

        size_t len = std::strlen(str);
        
        if (len > str_data->size - pos)   return npos;

        for (size_t i = pos; i <= str_data->size - len; ++i) {
            if (std::memcmp(str_data->data + i, str, len) == 0) return i; // послеовательность обнаружен 
        }
        return npos;
    }
};

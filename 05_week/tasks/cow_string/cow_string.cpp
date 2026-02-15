#include <cstring>
#include <string>
#include <vector>

//Так называемая корова. copy on write-COW. Вместо немедленного копирования данных при их использовании несколькими программами,
// одни и те же данные используются совместно до тех пор, пока одна из программ не попытается их изменить. 
/*
Необходимо реализовать упрощенную версию cow. Телёнка по сути)
//Допустим у нас есть длинная строка, мы создаем пусть 10 копий. Тогда каждая копия будет весть очень много. Огромный расход рес-в зря. Нужна какая-то оптимизация
//Дак вот cow помогает в этом. Все копии используют одни и те же данные, память почти не расходуется, ну там пару байт на счётчики и другие приколы, помогающие в этом
//Просто увеличивая счётчик, мы можем работать с неколькими копиями, но не терзая память за зря. Копируем указатель по сути

---Для реализации строки удобно вынести все необходимые поля в отдельную структуру
и кроме этого хранить в ней счетчик ссылок `ref_count`.
---Нельзя использовать в решении std string и умные указатели
---Вспомогат. методы реализуются в закрытой части, ну в целом как и всегда
*/

class CowString {
public:
    static const int npos; 
//конструкторы
    CowString();                                   //Конструктор по умолчанию — создает пустую строку
    CowString(const char*);                        //Конструктор от `const char*`
    CowString(const std::string&);                 //Конструктор от `std::string` 
    CowString(const CowString& other);             //Конструктор копирования — увеличивает счетчик ссылок, не копирует данные      
    CowString(CowString&& other) noexcept;         // Конструктор перемещения

    ~CowString();

    CowString& operator=(const CowString& other); //Оператор присваивания копированием — увеличивает счетчик ссылок, не копирует данные
    CowString& operator=(CowString&& other) noexcept; //Оператор присваивания перемещением

//Методы **НЕ** вызывающие копирования:
    int Size() const;                             //Метод `Size` - возвращает длину строки 
    const char* ToCstr() const;                    //Метод `ToCstr` - возвращает указатель на данные 
    std::string ToString() const;                 //Метод `ToString` - возвращает `std::string`
    const char& operator[](size_t index) const;   //Оператор `[]` - доступ к символу для чтения
    operator const char*() const;                 //Оператор неявного преобразования к C-строке
    bool Empty() const;                           //Добавляем метод Empty для тестов

//Методы, обеспечивающие модификацию на собственной копии данных:
    char& operator[](size_t index);               //Оператор `[]` - доступ к символу для записи
    CowString& Append(const char* str);           //Метод `Append` - добавляет строку из C-строки
    CowString& Append(const std::string& str);    //Метод `Append` - добавляет строку из std::string
    CowString Substr(int pos = 0, int count = npos) const;  //Метод `Substr` - принимает позицию и количество символов
    void Clear();                                 //Метод `Clear` - очистка строки
    
    // Дополнительные методы для тестов
    int Find(const char* str) const;              //Поиск подстроки
    int Find(char c) const;                       //Поиск символа

private:
    //структура для хранения данных
    struct DataContainer {
        int ref_count;     //Чисто объектов, использующих эанные. Счётчик ссылок или число копий т
        int size;        
        char* data;     //Тк заранее мы не знаем размер строки, то массив делать не очень, пускай будет char       
    // Конструктор
        DataContainer(const char* str, int lenOfString) {
            ref_count = 1;
            size = lenOfString;
            data = new char[lenOfString + 1];  // +1 для терминатора.  new[] delete[]- так как для массива всё задумано, а не для одного символа. Из лекций

            if (str && lenOfString > 0) {
                for (int i = 0; i < lenOfString; ++i) {
                    data[i] = str[i];
                }
            }
            data[lenOfString] = '\0';  //Так как в ТЗ сказано чтоб и С-строки работали, то он нужен, ведь в С строки заканчиваются так
        }

        ~DataContainer() {
            delete[] data;
        }
    };
    
    DataContainer* commonBuf_;  // указатель на общие данные. Через него как раз и реализуется разделение данных. Можно было бы shared_ptr, но его нельзя
    
    //Функция separete.
    //Разделяет данные (то есть создает копии)
    void separete() {
        if (commonBuf_ && commonBuf_->ref_count > 1) {  //ПРоверка на то являемся ли мы одним владельцем, или есть еще?
            commonBuf_->ref_count--;
            commonBuf_ = new DataContainer(commonBuf_->data, commonBuf_->size); // создаем новый буфер с такими же данными
        }
    }

};

//Определение статической константы. 
const int CowString::npos = -1;

//Реализации конструкторов
CowString::CowString() : commonBuf_(nullptr) {}

CowString::CowString(const char* str) {
    if (str) {
        int lenOfString = std::strlen(str);
        commonBuf_ = new DataContainer(str, lenOfString);
    } else {
        commonBuf_ = nullptr;
    }
}

CowString::CowString(const std::string& str) {
    commonBuf_ = new DataContainer(str.c_str(), str.size());
}

CowString::CowString(const CowString& other) : commonBuf_(other.commonBuf_) {
    if (commonBuf_) {
        commonBuf_->ref_count++; 
    }
}

CowString::CowString(CowString&& other) noexcept : commonBuf_(other.commonBuf_) {
    other.commonBuf_ = nullptr; 
}

CowString::~CowString() {
    if (commonBuf_) {
        commonBuf_->ref_count--;  
        if (commonBuf_->ref_count == 0) {
            delete commonBuf_;    
        }
    }
}

// Операторы присваивания
CowString& CowString::operator=(const CowString& other) {
    if (this != &other) {
        // Удаляем старые данные
        if (commonBuf_) {
            commonBuf_->ref_count--;
            if (commonBuf_->ref_count == 0) {
                delete commonBuf_;
            }
        }
        // Берем данные other
        commonBuf_ = other.commonBuf_;
        if (commonBuf_) {
            commonBuf_->ref_count++;
        }
    }
    return *this;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        if (commonBuf_) {
            commonBuf_->ref_count--;
            if (commonBuf_->ref_count == 0) {
                delete commonBuf_;
            }
        }
        commonBuf_ = other.commonBuf_;
        other.commonBuf_ = nullptr;
    }
    return *this;
}

// Методы не вызывающие копирования
int CowString::Size() const {
    return commonBuf_ ? commonBuf_->size : 0;
}

const char* CowString::ToCstr() const {
    return commonBuf_ ? commonBuf_->data : "";
}

std::string CowString::ToString() const {
    if (!commonBuf_) return std::string();
    return std::string(commonBuf_->data, commonBuf_->size);
}

const char& CowString::operator[](size_t index) const {
    return commonBuf_->data[index];
}

CowString::operator const char*() const {
    return commonBuf_ ? commonBuf_->data : "";
}

bool CowString::Empty() const {
    return !commonBuf_ || commonBuf_->size == 0;
}

// Методы для модификации
char& CowString::operator[](size_t index) {
    separete();  // перед записью создаем свою копию
    return commonBuf_->data[index];
}

CowString& CowString::Append(const char* str) {
    if (!str) return *this;
    
    int add_lenOfString = std::strlen(str);
    if (add_lenOfString == 0) return *this;
    int old_size = commonBuf_ ? commonBuf_->size : 0;
    int new_size = old_size + add_lenOfString;
    char* temp = new char[new_size + 1];

    if (commonBuf_) {
        for (int i = 0; i < old_size; ++i) {
            temp[i] = commonBuf_->data[i];
        }
    }
    // Добавляем новую
    for (int i = 0; i < add_lenOfString; ++i) temp[old_size + i] = str[i];
    temp[new_size] = '\0';
    
    // Удаляем старый буфер если нужно
    if (commonBuf_) {
        commonBuf_->ref_count--;
        if (commonBuf_->ref_count == 0) delete commonBuf_;
    }
    
    // Создаем новый буфер
    commonBuf_ = new DataContainer(temp, new_size);
    delete[] temp;
    
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

CowString CowString::Substr(int pos, int count) const {
    if (!commonBuf_ || pos < 0 || pos >= commonBuf_->size) {
        return CowString();
    }
    
    int start = pos;
    int lenOfString;
    
    if (count == npos || start + count > commonBuf_->size) {
        lenOfString = commonBuf_->size - start;
    } else {
        lenOfString = count;
    }
    
    if (lenOfString <= 0) {
        return CowString();
    }
    
    // Создаем временную строку с подстрокой
    char* temp = new char[lenOfString + 1];
    for (int i = 0; i < lenOfString; ++i) {
        temp[i] = commonBuf_->data[start + i];
    }
    temp[lenOfString] = '\0';
    
    CowString result(temp);
    delete[] temp;
    
    return result;
}

void CowString::Clear() {
    if (commonBuf_) {
        commonBuf_->ref_count--;
        if (commonBuf_->ref_count == 0) {
            delete commonBuf_;
        }
        commonBuf_ = nullptr;
    }
}

// Доп методы
int CowString::Find(const char* str) const {
    if (!commonBuf_ || !str) return npos;
    
    int lenOfString = std::strlen(str);
    if (lenOfString == 0) return 0;
    if (lenOfString > commonBuf_->size) return npos;
    
    for (int i = 0; i <= commonBuf_->size - lenOfString; ++i) {
        bool found = true;
        for (int j = 0; j < lenOfString; ++j) {
            if (commonBuf_->data[i + j] != str[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    
    return npos;
}

int CowString::Find(char c) const {
    if (!commonBuf_) return npos;
    
    for (int i = 0; i < commonBuf_->size; ++i) {
        if (commonBuf_->data[i] == c) return i;
    }
    
    return npos;
}
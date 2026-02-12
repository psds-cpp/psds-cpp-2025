#include <cstring>
#include <limits>
#include <string>

struct CowStringData {
    char* data = nullptr;
    size_t size = 0;
    size_t refCount = 1;

    CowStringData() : data(new char[1]{'\0'}) {}

    CowStringData(const char* str) {
        size = strlen(str);
        data = new char[size + 1];
        std::strcpy(data, str);
        refCount = 1;
    }

    CowStringData(const std::string& str) {
        size = str.size();
        data = new char[size + 1];
        std::strcpy(data, str.c_str());
        refCount = 1;
    }

    ~CowStringData() {
        delete[] data;
    }
};

class CowString {
public:
    inline static size_t npos = std::numeric_limits<size_t>::max(); 
    
    CowString() : cowString_(new CowStringData) {}

    CowString(const char* str) : cowString_(new CowStringData(str)) {}

    CowString(const std::string& str) : cowString_(new CowStringData(str)) {}

    CowString(const CowString& other) : cowString_(other.cowString_){
        if (cowString_) {
            ++cowString_->refCount;
        }
    }

    CowString(CowString&& other) : cowString_(other.cowString_) {
        other.cowString_ = new CowStringData;        
    }

    ~CowString() {
        DecreaseRefCount();
    }

    CowString& operator=(const CowString& other) {
        if (this == &other) {
            return *this;
        }

        DecreaseRefCount();
        
        cowString_ = other.cowString_;
        if (cowString_) {
            ++cowString_->refCount;
        }
        
        return *this;
    }

    CowString& operator=(CowString&& other) {
        if (this == &other) {
            return *this;
        }

        DecreaseRefCount();

        cowString_ = other.cowString_;
        other.cowString_ = new CowStringData;

        return *this;
    }

    const char& operator[](size_t idx) const {
        return cowString_->data[idx];
    }

    operator const char*() const {
        return cowString_->data;
    }

    char& operator[](size_t idx) {
        if (cowString_->refCount > 1) {
            MakeDeepCopy();
        }

        return cowString_->data[idx]; 
    }

    size_t Size() const;
    bool Empty() const;
    const char* ToCstr() const;
    std::string ToString() const;
    size_t Find(char symbol, size_t start) const;
    size_t Find(const char* str, size_t start) const;
    CowString& Append(const char* str);
    CowString& Append(const std::string& str);
    CowString Substr(size_t start, size_t len);
    void Clear();
   
private:
    CowStringData* cowString_ = nullptr;

    void DecreaseRefCount();
    void MakeDeepCopy();
};

void CowString::DecreaseRefCount() {
    if (cowString_ && --cowString_->refCount == 0) {
        delete cowString_;
    }
}

void CowString::MakeDeepCopy() {
    CowStringData* deep_copy = new CowStringData(cowString_->data);
    DecreaseRefCount();
    cowString_ = deep_copy;
}

bool operator==(const CowString& lhs, const std::string& rhs) {
    return std::strcmp(lhs.ToCstr(), rhs.c_str()) == 0;
}

size_t CowString::Size() const {
    return cowString_->size;
}

bool CowString::Empty() const {
    return cowString_->size == 0;
}

const char* CowString::ToCstr() const {
    return cowString_->data;
}

std::string CowString::ToString() const {
    return std::string(cowString_->data, cowString_->size);
}

size_t CowString::Find(char symbol, size_t start = 0) const {
    if (start > Size() || Empty()) {
        return npos;
    }

    const char* pos = std::strchr(cowString_->data + start, symbol);

    if (!pos) {
        return npos;
    } 

    return pos - cowString_->data;
}

size_t CowString::Find(const char* str, size_t start = 0) const {
    if (start > Size() || std::strlen(str) > Size() || Empty()) {
        return npos;
    }

    const char* pos = std::strstr(cowString_->data + start, str);

    if (!pos) {
        return npos;
    }

    return pos - cowString_->data;
}

CowString& CowString::Append(const char* str) {
    if (!str || str[0] == '\0') {
        return *this;
    }

    if (!cowString_) {
        cowString_ = new CowStringData(str);
        return *this;
    }

    if (cowString_->refCount > 1) {
        MakeDeepCopy();
    }

    size_t newSize = cowString_->size + std::strlen(str);
    char* newData = new char[newSize + 1];

    if (cowString_->data) {
        std::strcpy(newData, cowString_->data);
    }
    std::strcat(newData, str);

    delete[] cowString_->data;
    cowString_->data = newData;
    cowString_->size = newSize;
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    if (str.empty()) {
        return *this;
    }

    if (!cowString_) {
        cowString_ = new CowStringData(str);
        return *this;
    }

    if (cowString_->refCount > 1) {
        MakeDeepCopy();
    }

    size_t newSize = cowString_->size + str.size();
    char* newData = new char[newSize + 1];

    if (cowString_->data) {
        std::strcpy(newData, cowString_->data);
    }
    std::strcat(newData, str.c_str());

    delete[] cowString_->data;
    cowString_->data = newData;
    cowString_->size = newSize;
    return *this;
}

CowString CowString::Substr(size_t start = 0, size_t len = npos) {
    if (start == 0 && len == npos) {
        return CowString(*this);
    }

    if (start > cowString_->size) {
        return CowString();
    }

    if (len > cowString_->size) {
        len = cowString_->size;
    }

    size_t substrSize = std::min(len, cowString_->size - start);

    char* subStr = new char[substrSize + 1];
    std::strncpy(subStr, cowString_->data + start, substrSize);
    subStr[substrSize] = '\0';

    CowString subCowStr;
    delete[] subCowStr.cowString_->data;
    subCowStr.cowString_->data = subStr;
    subCowStr.cowString_->size = substrSize;
    return subCowStr;
}

void CowString::Clear() {
    if (!cowString_) {
        cowString_ = new CowStringData;
        return;
    }

    if (cowString_->refCount == 1) {
        delete cowString_;
        cowString_ = new CowStringData;
        return; 
    }

    DecreaseRefCount();

    cowString_ = new CowStringData;
}

#include <cstring>
#include <limits>
#include <string>

namespace {
    // Не уверен, что определение структуры нужно заносить
    // в безымянный namespacе.   
    struct CowStringData {
        char* data = nullptr;
        size_t size = 0;
        size_t refCount = 1;

        CowStringData() = default;

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
}

class CowString {
public:
    CowString() : cowString_(new CowStringData) {}

    CowString(const char* str) : cowString_(new CowStringData(str)) {}

    CowString(const std::string& str) : cowString_(new CowStringData(str)) {}

    CowString(const CowString& other) {
        cowString_ = other.cowString_;
        if (cowString_) {
            ++cowString_->refCount;
        }
    }

    CowString(CowString&& other) {
        cowString_ = other.cowString_;
        other.cowString_ = nullptr;
    }

    ~CowString() {
        DecreaseRefCount();
    }

    CowString& operator=(CowString& other) {
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
        other.cowString_ = nullptr;

        return *this;
    }

    const char& operator[](size_t idx) const {
        return cowString_->data[idx];
    }

    char& operator[](size_t idx) {
        if (cowString_->refCount > 1) {
            MakeDeepCopy();
        }

        return cowString_->data[idx]; 
    }

    size_t Size() const;
    const char* ToStr() const;
    const std::string ToString() const;
    void Append();
    CowString Substr(size_t start = 0, size_t len = std::numeric_limits<size_t>::max());
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

size_t CowString::Size() const {
    return cowString_->size;
}

const char* CowString::ToStr() const {
}

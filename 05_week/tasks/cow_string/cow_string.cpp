#include <cstring>
#include <string>
#include <algorithm>

class CowString
{
private:
    struct CowStringMeta
    {
        size_t ref_count;
        size_t length;
        char* data;
    };

    CowStringMeta* m_metainfo;

    CowStringMeta* AllocateMetaData(const char* c_str, size_t length = npos);
    void DerefMetaData(CowStringMeta* metadata);
    void CloneMetaData();

public:
    static constexpr size_t npos = std::string::npos;

    CowString() : m_metainfo(nullptr) {}
    CowString(const char* c_str) { m_metainfo = AllocateMetaData(c_str, (c_str) ? std::strlen(c_str) : 0); }
    CowString(const std::string& str) { m_metainfo = AllocateMetaData(str.c_str(), str.length()); }
    CowString(const CowString& cow);
    CowString(CowString&& cow);
    ~CowString() { DerefMetaData(m_metainfo); }

    CowString& operator=(const CowString& cow);
    CowString& operator=(CowString&& cow);

    size_t Size() const { return (m_metainfo) ? m_metainfo->length : 0; }
    bool Empty() const { return !Size(); }
    size_t Find(char ch, size_t pos = 0) const;
    size_t Find(const CowString& cow, size_t pos = 0) const;

    const char* ToCstr() const { return (m_metainfo) ? ((m_metainfo->data) ? m_metainfo->data : "") : ""; }
    std::string ToString() const { return (m_metainfo) ? std::string(m_metainfo->data) : std::string(); }
    operator const char*() const { return ToCstr(); }
    char operator[](size_t n) const { return m_metainfo->data[n]; }

    char& operator[](size_t n);
    CowString& Append(const char* c_str);
    CowString& Append(const std::string& str) { return Append(str.c_str()); }
    CowString Substr(size_t pos = 0, size_t length = npos);
    void Clear();
};

CowString::CowStringMeta* CowString::AllocateMetaData(const char* c_str, size_t length)
{
    CowStringMeta* metadata = nullptr;

    if (!c_str || !length)
        return metadata;

    metadata = new CowStringMeta;
    metadata->ref_count = 1;
    metadata->length = length;
    metadata->data = new char[length + 1];
    
    std::memcpy(metadata->data, c_str, length);
    metadata->data[length] = '\0';

    return metadata;
}

void CowString::DerefMetaData(CowString::CowStringMeta* metadata)
{
    if (!metadata)
        return;
    
    --metadata->ref_count;

    if (!metadata->ref_count)
    {
        delete[] metadata->data;
        delete metadata;
    }
}

void CowString::CloneMetaData()
{
    if (!m_metainfo)
        return;

    if (m_metainfo->ref_count > 1)
    {
        CowStringMeta* copy = AllocateMetaData(m_metainfo->data, m_metainfo->length);
        --m_metainfo->ref_count;
        m_metainfo = copy;
    }
}

CowString::CowString(const CowString& cow)
{
    m_metainfo = cow.m_metainfo;

    if (m_metainfo)
        ++m_metainfo->ref_count;
}

CowString::CowString(CowString&& cow)
{
    m_metainfo = cow.m_metainfo;
    cow.m_metainfo = nullptr;
}

CowString& CowString::operator=(const CowString& cow)
{
    if (this == &cow)
        return *this;

    DerefMetaData(m_metainfo);
    m_metainfo = cow.m_metainfo;

    if (m_metainfo)
        ++m_metainfo->ref_count;
    
    return *this;
}

CowString& CowString::operator=(CowString&& cow)
{
    if (this == &cow)
        return *this;

    DerefMetaData(m_metainfo);
    m_metainfo = cow.m_metainfo;
    cow.m_metainfo = nullptr;

    return *this;
}

size_t CowString::Find(char ch, size_t pos) const
{
    if (!m_metainfo)
        return npos;

    if (pos >= m_metainfo->length)
        return npos;
    
    for (size_t i = pos; i <= m_metainfo->length; ++i)
        if (m_metainfo->data[i] == ch)
            return i;

    return npos;
}

size_t CowString::Find(const CowString& cow, size_t pos) const
{
    if (!m_metainfo)
        return npos;

    if (cow.Empty())
        return 0;

    if (pos >= m_metainfo->length)
        return npos;

    const char* it = std::search(m_metainfo->data + pos, m_metainfo->data + m_metainfo->length, cow.m_metainfo->data, cow.m_metainfo->data + cow.m_metainfo->length);

    if (it != (m_metainfo->data + m_metainfo->length))
        return it - m_metainfo->data;

    return npos;
}

char& CowString::operator[](size_t n)
{
    CloneMetaData();
    return m_metainfo->data[n];
}

CowString& CowString::Append(const char* c_str)
{
    if (!c_str)
        return *this;

    size_t length = std::strlen(c_str);
    if (!length)
        return *this;

    CloneMetaData();

    if (!m_metainfo)
    {
        m_metainfo = AllocateMetaData(c_str, length);
    }
    else
    {
        char* data = new char[m_metainfo->length + length + 1];
        std::strcpy(data, m_metainfo->data);
        std::strcat(data + m_metainfo->length, c_str);
        delete[] m_metainfo->data;
        m_metainfo->data = data;
        m_metainfo->length += length;
    }

    return *this;
}

CowString CowString::Substr(size_t pos, size_t length)
{
    CowString cow;

    if (!m_metainfo)
        return cow;

    if (pos >= m_metainfo->length)
        return cow;

    cow.m_metainfo = AllocateMetaData(m_metainfo->data + pos, std::min(m_metainfo->length - pos, length));
    return cow;
}

void CowString::Clear()
{
    DerefMetaData(m_metainfo);
    m_metainfo = nullptr;
}
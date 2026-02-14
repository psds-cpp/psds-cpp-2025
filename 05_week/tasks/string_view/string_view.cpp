#include <cstddef>
#include <cstring>
#include <string>
#include <limits>

class StringView
{
private:
  const char *str = nullptr;
  size_t size = 0;
  std::string storage;
public:
  inline static size_t npos = std::numeric_limits<size_t>::max();
  // конструкторы
  StringView() = default;
  StringView(const std::string &constr_str, size_t beginning = 0, size_t constr_size = npos)
  {
    if (beginning < constr_str.size()){
      str = constr_str.data() + beginning;
      if (constr_size == npos || constr_size > std::strlen(str)){
        size = std::strlen(str);
      }
      else{
        size = constr_size;
      }
    }
    else{
      size = 0;
      return;
    }
  }
  StringView(const std::string &&constr_str, size_t beginning = 0, size_t constr_size = npos) : storage(std::move(constr_str))
  {
    if (beginning < storage.size()){
      str = storage.data() + beginning;
      if (constr_size == npos || constr_size > std::strlen(str)){
        size = std::strlen(str);
      }
      else{
        size = constr_size;
      }
    }
    else{
      size = 0;
      return;
    }
  }
  StringView(const char *constr_str)
  {
    if (constr_str){
      size = std::strlen(constr_str);
      str = constr_str;
    }
  }
  StringView(const char *constr_str, size_t constr_size)
  {
    if (constr_str && constr_size != 0){
      str = constr_str;
      if (constr_size <= std::strlen(constr_str))
      {
        size = constr_size;
      }
      else
      {
        size = std::strlen(constr_str);
      }
      
    }
    else{
      str = constr_str;
      size = 0;
    }
  }
  // операторы
  const char &operator[](size_t pos) const { return str[pos]; }
  const char *Data() const;
  const char &Front() const;
  const char &Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  void RemovePrefix(size_t torm);
  void RemoveSuffix(size_t torm);
  StringView Substr(size_t pos, size_t num);
  size_t Find(char x, size_t begin) const;
  size_t Find(const StringView &x, size_t begin) const;
  std::string ToString();
};

const char *StringView::Data() const { return size == 0 ? nullptr : str; }

const char &StringView::Front() const { return *str; }

const char &StringView::Back() const { return *(str + size - 1); }

size_t StringView::Size() const { return size; }

size_t StringView::Length() const { return size; }

bool StringView::Empty() const { return size == 0; }

void StringView::RemovePrefix(size_t torm)
{
  str += torm;
  torm >= size ? (size = 0) : (size -= torm);
}

void StringView::RemoveSuffix(size_t torm) { torm >= size ? (size = 0) : (size -= torm); }

StringView StringView::Substr(size_t pos, size_t num = npos)
{
  if (pos >= size){
    return StringView(str + pos, 0);
  }
  else{
    size_t new_size;
    if (num == npos){
      new_size = (num == npos) ? size - pos : num;
    }
    else{
      new_size = num;
    }
    return StringView(str + pos, new_size);
  }
}

size_t StringView::Find(char x, size_t begin = 0) const
{
  for (size_t i = begin; i < size; ++i)
  {
    if (str[i] == x)
      return i;
  }
  return npos;
}

size_t StringView::Find(const StringView &x, size_t begin = 0) const
{
  if (x.size == 0){
    if (begin <= size)
      return begin;
    else
      return npos;
  }
  if (size == 0){
    return npos;
  }
  
  for (size_t i = begin; i < size; ++i)
  {
    if (str[i] == x[0])
    {
      size_t k = 0;
      bool is_eq = true;
      while (++i < size && ++k < x.size)
      {
        if (str[i] != x[k])
          is_eq = false;
      }
      if (is_eq)
        return x.size > i ? npos : i - x.size;
    }
  }
  return npos;
}


std::string StringView::ToString()
{
  if (!str)
    return "";
  return std::string(str, size);
}
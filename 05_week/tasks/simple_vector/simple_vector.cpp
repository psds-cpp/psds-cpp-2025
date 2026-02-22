#include <initializer_list>
#include <cstddef>

class SimpleVector
{
private:
    int *it_begin;
    size_t capacity;
    size_t size;

    void Realloc_Vector(size_t new_capacity)
    {
        int *it_begin_t = new int[new_capacity];
        if (it_begin)
        {
            if (new_capacity < size)
            {
                delete[] (it_begin + new_capacity);
                size = new_capacity;
            }
            for (size_t i = 0; i < size; ++i)
            {
                it_begin_t[i] = it_begin[i];
            }
        }
        delete[] it_begin;
        it_begin = it_begin_t;
        capacity = new_capacity;
    }

public:
    // конструктор по умолчанию
    SimpleVector() : it_begin(nullptr), capacity(0), size(0) {};
    // конструктор от размера
    SimpleVector(size_t size_init, int num = 0)
    {
        if (size_init > 0)
        {
            it_begin = new int[size_init];
            for (size_t i = 0; i < size_init; ++i)
            {
                it_begin[i] = num;
            }
            size = size_init;
            capacity = size_init;
        }
    }
    // конструктор от списка инициализации
    SimpleVector(std::initializer_list<int> list)
    {
        size_t size_init = list.size();
        it_begin = new int[size_init];
        for (size_t i = 0; i < size_init; ++i)
        {
            it_begin[i] = *(list.begin() + i);
        }
        size = size_init;
        capacity = size_init;
    }
    // конструктор от другого ветора
    SimpleVector(const SimpleVector &other)
    {
        it_begin = new int[other.Size()];
        for (size_t i = 0; i < other.Size(); ++i)
        {
            it_begin[i] = other[i];
        }
        size = other.size;
        capacity = other.size;
    }
    // конструктор перемещения
    SimpleVector(SimpleVector &&other) : it_begin(other.it_begin), capacity(other.capacity), size(other.size)
    {
        other.it_begin = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    // деструктор
    ~SimpleVector()
    {
        delete[] it_begin;
    }

    int &operator[](size_t i)
    {
        return it_begin[i];
    }
    const int &operator[](size_t i) const
    {
        return it_begin[i];
    }
    bool operator==(const SimpleVector &other) const
    {
        if (size == other.Size())
        {
            for (size_t i = 0; i < size; ++i)
            {
                if (it_begin[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(const SimpleVector &other) const
    {
        return !(*this == other);
    }
    // операторы для range-based for
    int *begin()
    {
        return it_begin;
    }

    int *end()
    {
        return it_begin + size;
    }

    // Для константных объектов (только чтение)
    const int *begin() const
    {
        return it_begin;
    }

    const int *end() const
    {
        return it_begin + size;
    }
    SimpleVector &operator=(const SimpleVector &other)
    {
        if (*this != other)
        {
            size = 0;
            for (size_t i = 0; i < other.size; ++i)
            {
                PushBack(other[i]);
            }
            if (this->capacity > this->size)
            {
                Realloc_Vector(size);
            }
        }
        return *this;
    }
    SimpleVector &operator=(SimpleVector &&other) noexcept
    {
        delete[] it_begin;
        it_begin = other.it_begin;
        size = other.size;
        capacity = other.capacity;

        other.it_begin = nullptr;
        other.capacity = 0;
        other.size = 0;
        return *this;
    }
    size_t Size() const
    {
        return size;
    }

    void Swap(SimpleVector &other)
    {
        int *it_t_begin = other.it_begin;
        size_t size_tmp = other.size;
        size_t capacity_t = other.capacity;

        other.it_begin = it_begin;
        other.size = size;
        other.capacity = capacity;

        it_begin = it_t_begin;
        size = size_tmp;
        capacity = capacity_t;

        return;
    }

    size_t Capacity()
    {
        return capacity;
    }

    bool Empty()
    {
        return size == 0;
    }
    const int *Data() const
    {
        return it_begin;
    }
    void PushBack(int x)
    {
        if (capacity <= size)
        {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            Realloc_Vector(new_capacity);
        }
        it_begin[size] = x;
        ++size;
    }

    void PopBack()
    {
        if (size)
        {
            --size;
        }
    }

    int *Insert(size_t pos, int x)
    {
        if (size >= pos)
        {
            if (capacity <= size)
            {
                size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
                Realloc_Vector(new_capacity);
            }
            for (size_t i = size; i > pos; --i)
            {
                it_begin[i] = it_begin[i - 1];
            }
            it_begin[pos] = x;
            ++size;
            return it_begin + pos;
        }
        else
        {
            return it_begin + size;
        }
    }

    int *Insert(const int *pos, int x)
    {
        if (size >= static_cast<size_t>(pos - it_begin) && pos >= it_begin)
        {
            return Insert(pos - it_begin, x);
        }
        else
        {
            return it_begin + size;
        }
    }
    int *Erase(size_t pos)
    {
        if (pos < size)
        {
            for (size_t i = pos; i < size - 1; ++i)
            {
                it_begin[i] = it_begin[i + 1];
            }
            --size;
            return it_begin + pos;
        }
        else
        {
            return it_begin + size;
        }
    }
    int *Erase(const int *pos)
    {
        if (pos < it_begin + size)
        {
            return Erase(pos - it_begin);
        }
        else
        {
            return it_begin + size;
        }
    }
    void Resize(size_t new_size, int emplacer = 0)
    {
        if (new_size > size)
        {
            if (new_size > capacity)
            {
                Realloc_Vector(new_size * 2);
            }
            for (; size < new_size; ++size)
            {
                it_begin[size] = emplacer;
            }
            size = new_size;
        }
        else
        {
            size = new_size;
        }
    }

    void Reserve(size_t new_capacity)
    {
        if (capacity < new_capacity)
        {
            Realloc_Vector(new_capacity);
            capacity = new_capacity;
        }
    }

    void Clear()
    {
        size = 0;
    }
};

void swap(SimpleVector &v1, SimpleVector &v2)
{
    v1.Swap(v2);
    return;
}
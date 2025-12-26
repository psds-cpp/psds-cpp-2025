#include <vector>
#include <stack>

class Queue
{
public:
    // конструкторы
    Queue(std::initializer_list<int> num)
    {
        auto it = num.begin();
        for (; it < num.end(); ++it)
        {
            this->Push(*it);
        }
    }

    Queue(size_t size)
    {
        this->in->reserve(size);
        this->out->reserve(size);
    };
    Queue(int size)
    {
        this->in->reserve(size);
        this->out->reserve(size);
    };
    Queue(long size)
    {
        this->in->reserve(size);
        this->out->reserve(size);
    };

    Queue() {};

    Queue(std::vector<int> &v)
    {
        auto size = v.size();
        for (size_t i = 0; i < size; ++i)
        {
            this->Push(v[i]);
        }
    }

    Queue(std::stack<int> s)
    {
        auto size = s.size();
        for (size_t i = 0; i < size; ++i)
        {
            this->out->push_back(s.top());
            s.pop();
        }
    }
    
    Queue(const Queue& other) 
    : in(new std::vector<int>(*other.in))
    , out(new std::vector<int>(*other.out)) {}

    ~Queue()
    {
        delete in;
        delete out;
    }

    // методы
    int &Front()
    {
        if (this->out->empty())
        {
            while (!in->empty())
            {
                out->push_back(in->back());
                in->pop_back();
            }
        }
        return this->out->back();
    }
    int &Back()
    {
        if (!in->empty())
            return this->in->back();
        else
            return this->out->front();
    }
    const int &Front() const
    {
        Queue* temp = const_cast<Queue*>(this);
        if (temp->out->empty())
        {
            while (!temp->in->empty())
            {
                temp->out->push_back(in->back());
                temp->in->pop_back();
            }
        }
        return temp->out->back();
    }

    const int &Back() const
    {
        Queue* temp = const_cast<Queue*>(this);
        if (temp->out->empty())
        {
            while (!temp->in->empty())
            {
                temp->out->push_back(in->back());
                temp->in->pop_back();
            }
        }
        if (!in->empty())
            return temp->in->back();
        else
            return temp->out->front();
    }

    size_t Size()
    {
        return this->in->size() + this->out->size();
    }
    size_t Size() const
    {
        return this->in->size() + this->out->size();
    }
    void Clear()
    {
        this->in->clear();
        this->out->clear();
    }
    void Push(int a)
    {
        in_s.push_back(a);
    }
    bool Pop()
    {
        if (out->empty())
        {
            while (!in->empty())
            {
                out->push_back(in->back());
                in->pop_back();
            }
        }
        if (out->empty())
        {
            return false;
        }
        out->pop_back();
        return true;
    }

    bool Empty()
    {
        return in->empty() && out->empty();
    }
    bool Empty() const
    {
        if (!in || !out) return true;
        return in->empty() && out->empty();
    }
    void Swap(Queue &q2)
    {
        std::vector<int> *new_in = q2.get_ptr_in();
        std::vector<int> *new_out = q2.get_ptr_out();
        
        q2.set_in(in);
        q2.set_out(out);
        this->in = new_in;
        this->out = new_out;
        return;
    }
    bool operator==(const Queue& other) const {
        if (Size() != other.Size()) return false;
        
        // Простое поэлементное сравнение
        Queue copy1 = *this;
        Queue copy2 = other;
        
        while (!copy1.Empty()) {
            if (copy1.Front() != copy2.Front()) return false;
            copy1.Pop();
            copy2.Pop();
        }
        return true;
    }

    bool operator!=(const Queue q2) const
    {
        return !(*this == q2);
    }

private:
    

    std::vector<int> *in = new std::vector<int>;
    std::vector<int> *out = new std::vector<int>;
    std::vector<int>& in_s = *in;
    std::vector<int>& out_s = *out;


    std::vector<int> *get_ptr_in() const
    {
        return this->in;
    }
    std::vector<int> *get_ptr_out() const
    {
        return this->out;
    }

    void set_in(std::vector<int> *x)
    {
        this->in = x;
    }
    void set_out(std::vector<int> *x)
    {
        this->out = x;
    }
};

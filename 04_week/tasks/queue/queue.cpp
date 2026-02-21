#include <vector>
#include <stack>
#include <algorithm>

class Queue {
private:
    std::vector<int> in;
    std::vector<int> out;

    void PrepareOut() {
        if (out.empty() && !in.empty()) {
            out.insert(out.end(), in.rbegin(), in.rend());
            in.clear();
        }
    }
    
public:
    // Конструкторы
    Queue() = default;
    
    explicit Queue(std::stack<int> st) {
        std::vector<int> temp;
        while (!st.empty()) {
            temp.push_back(st.top());
            st.pop();
        }
        in.insert(in.end(), temp.rbegin(), temp.rend());
    }
    
    explicit Queue(std::vector<int>& vec) : in(vec) {}
    
    Queue(std::initializer_list<int> ls) : in(ls) {}
    
    explicit Queue(size_t capacity) {
        in.reserve(capacity);
        out.reserve(capacity);
    }
    
    // Методы
    void Push(int value) {
        in.push_back(value);
    }
    
    bool Pop() {
        if (Empty()) return false;
        PrepareOut();
        out.pop_back();
        return true;
    }
    
    bool Empty() const {
        return in.empty() && out.empty();
    }
    
    int& Front() {
        PrepareOut();
        return out.back();
    }
    
    const int& Front() const {
        const_cast<Queue*>(this)->PrepareOut();
        return out.back();
    }
    
    int& Back() {
        if (!in.empty()) {
            return in.back();
        }
        PrepareOut();
        return out.front();
    }
    
    const int& Back() const {
        if (!in.empty()) {
            return in.back();
        }
        const_cast<Queue*>(this)->PrepareOut();
        return out.front(); 
    }
    
    size_t Size() const {
        return in.size() + out.size();
    }
    
    void Clear() {
        in.clear();
        out.clear();
    }
    
    void Swap(Queue& other) {
        in.swap(other.in);
        out.swap(other.out);
    }
    
    bool operator==(const Queue& other) const {
        if (Size() != other.Size()) return false;
        if (Empty()) return true;
        
        Queue q1 = *this;
        Queue q2 = other;
        
        q1.PrepareOut();
        q2.PrepareOut();
        
        auto it1 = q1.out.rbegin();
        auto it2 = q2.out.rbegin();
        
        while (it1 != q1.out.rend() && it2 != q2.out.rend()) {
            if (*it1 != *it2) return false;
            ++it1;
            ++it2;
        }
        
        return true;
    }
    
    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }
};

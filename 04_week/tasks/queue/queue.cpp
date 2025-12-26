#include <vector>
#include <stack>
#include <initializer_list>


class Queue {
public:
    Queue(std::stack<int>& stack);
    Queue(const std::vector<int>& vec);
    Queue(const std::initializer_list<int> list);
    Queue(size_t size);
    Queue() = default;
    void Push(int value);
    bool Pop();
    int& Front();
    int& Back();
    const int& Front() const;
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    bool operator==(const Queue& rhs) const;
    bool operator!=(const Queue& rhs) const;

private:
    std::vector<int> in;
    std::vector<int> out;
};


Queue::Queue(std::stack<int>& stack) {
    out.reserve(stack.size() * 1.2);
    while(!(stack.empty())){
        out.push_back(stack.top());
        stack.pop();
    }
}
Queue::Queue(const std::vector<int>& vec) {
    out.reserve(vec.size() * 1.5);
    out.insert(out.end(), vec.rbegin(), vec.rend());
}
Queue::Queue(std::initializer_list<int> list) {
    out.reserve(list.size() * 1.5);
    for(auto it = std::rbegin(list); it != std::rend(list); ++it){
        out.push_back(*it);
    }
}
Queue::Queue(size_t size) {
    out.reserve(size);
    in.reserve(size);
}

void Queue::Push(int value){
    in.push_back(value);
}
bool Queue::Pop(){
    if(in.empty() && out.empty()) return false;
    if(out.empty() && !(in.empty())){
        while(!(in.empty())){
            out.push_back(in.back());
            in.pop_back();
        }
    }
    out.pop_back();
    return true;
}
int& Queue::Front() {
    if(out.empty()) return in.front();
    return out.back();
}
int& Queue::Back() {
    if(in.empty()) return out.front();
    return in.back();
}
const int& Queue::Front() const {
    if(out.empty()) return in.front();
    return out.back();
}
const int& Queue::Back() const {
    if(in.empty()) return out.front();
    return in.back();
}
bool Queue::Empty() const {
    if(in.empty() && out.empty()) return true;
    return false;
}
size_t Queue::Size() const {
    return in.size() + out.size();
}
void Queue::Clear() {
    in.clear();
    out.clear();
}
void Queue::Swap(Queue& other) {
    in.swap(other.in);
    out.swap(other.out);
}

bool Queue::operator==(const Queue& rhs) const {
    std::vector<int> tmp_lhs(this->in.rbegin(), this->in.rend());
    tmp_lhs.insert(tmp_lhs.end(), this->out.begin(), this->out.end());
    std::vector<int> tmp_rhs(rhs.in.rbegin(), rhs.in.rend());
    tmp_rhs.insert(tmp_rhs.end(), rhs.out.begin(), rhs.out.end());

    return tmp_lhs == tmp_rhs;
}
bool Queue::operator!=(const Queue& rhs) const {
    return !(*this == rhs);
}
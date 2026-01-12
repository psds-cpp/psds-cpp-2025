#include <vector>
#include <stack>


class Queue {
    public:
        Queue() = default;
        Queue(std::vector<int>& vec);
        Queue(std::stack<int>& s);
        Queue(std::initializer_list<int> init_list);
        Queue(size_t size);

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

        bool operator==(const Queue& other) const;
        bool operator!=(const Queue& other) const;

    private:
        std::vector<int> vec_in;
        std::vector<int> vec_out;
};
Queue::Queue(std::vector<int>& vec) {
    for (auto it : vec) {
        vec_out.push_back(it);
    }
}
Queue::Queue(std::stack<int>& s) {
    std::stack<int> st = s;
    std::vector<int> vec;
    while (!st.empty()) {
        vec_out.push_back(st.top());
        st.pop();
    }
}   
Queue::Queue(std::initializer_list<int> init_list) {
    for (auto it : init_list) {
        vec_in.push_back(it);
    }
}

Queue::Queue(size_t size) {
    vec_in.reserve(size);
    vec_out.reserve(size);
}

void Queue::Push(int value) {
    vec_in.push_back(value);
}
bool Queue::Pop() {
    if (vec_out.empty()) {
        while (!vec_in.empty()) {
            vec_out.push_back(vec_in.back());
            vec_in.pop_back();
        }
    }
    if (vec_out.empty()) {
        return false;
    }
    vec_out.pop_back();
    return true;
}

int& Queue::Back() {
    if (!vec_in.empty()){
        return vec_in.back();
    }
    return vec_out.front();
    
}
int& Queue::Front() {
    if (vec_out.empty()) {
        return vec_in.back();
    }
    return vec_out.back();
}

const int& Queue::Back() const{
    if (!vec_in.empty()){
        return vec_in.back();
    }
    return vec_out.front();
    
}
const int& Queue::Front() const{
    if (vec_out.empty()) {
        return vec_in.back();
    }
    return vec_out.back();
}

bool Queue::Empty() const {
    return vec_in.empty() && vec_out.empty();
}

size_t Queue::Size() const{
    return vec_in.size() + vec_out.size();
}

void Queue::Clear() {
    vec_in.clear();
    vec_out.clear();
}

void Queue::Swap(Queue& other) {
    vec_in.swap(other.vec_in);
    vec_out.swap(other.vec_out);
}

bool Queue::operator==(const Queue& other_queue) const {
    return other_queue.vec_in == vec_in && other_queue.vec_out == vec_out;
}

bool Queue::operator!=(const Queue& other_queue) const {
    return !(*this == other_queue);
}


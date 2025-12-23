#include <initializer_list>
#include <stack>
#include <vector>

class Queue {
public:
    Queue() {};
    
    Queue(std::stack<int> s) {
        outputV_.reserve(s.size());
        while(!s.empty()) {
            outputV_.push_back(s.top());
            s.pop();
        }
    };
    
    Queue(std::vector<int> v) : outputV_(v.rbegin(), v.rend()){};

    Queue(std::initializer_list<int> list) : inputV_(list) {};

    Queue(const size_t size) {
        inputV_.reserve(size);
        outputV_.reserve(size);
    };
    
    Queue(const int size) {
        inputV_.reserve(size);
        outputV_.reserve(size);
    };
        
    inline void Push(int val);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);

    bool operator==(const Queue& other) const {
        if (Size() != other.Size()) {
            return false;
        }

        return this->GetQueueAsVector() == other.GetQueueAsVector();
    }

    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }
    
private:
    void CopyIfOutEmpty();
    std::vector<int> GetQueueAsVector() const;
    std::vector<int> inputV_{};
    std::vector<int> outputV_{};
};

void Queue::CopyIfOutEmpty() {    
    if (outputV_.empty()) {
        outputV_ = std::vector<int>(inputV_.rbegin(), inputV_.rend());
        inputV_.clear();
    }
}

std::vector<int> Queue::GetQueueAsVector() const {
    std::vector<int> result;
    
    std::copy(outputV_.rbegin(), outputV_.rend(), std::back_inserter(result));
    
    std::copy(inputV_.begin(), inputV_.end(), std::back_inserter(result));
    
    return result;
}

inline void Queue::Push(int val) {
    inputV_.push_back(val);
}

bool Queue::Pop() {
    if (outputV_.empty() && inputV_.empty()) {
        return false;    
    }

    CopyIfOutEmpty();

    outputV_.pop_back();

    return true;    
}

int& Queue::Front() {
    CopyIfOutEmpty();
    return outputV_.back();
}

const int& Queue::Front() const {
    if (outputV_.empty()) {
        return inputV_.front();
    }
    
    return outputV_.back();
}

int& Queue::Back() {
    if (!inputV_.empty()) {
        return inputV_.back();
    }
    
    return outputV_.front(); 
}

const int& Queue::Back() const {
    if (!inputV_.empty()) {
        return inputV_.back();
    }
    
    return outputV_.front(); 
}

bool Queue::Empty() const {
    return (inputV_.empty() && outputV_.empty());
}

size_t Queue::Size() const {
    return (inputV_.size() + outputV_.size());
}

void Queue::Clear() {
    inputV_.clear();
    outputV_.clear();
}

void Queue::Swap(Queue& other) {
    inputV_.swap(other.inputV_);
    outputV_.swap(other.outputV_);
}

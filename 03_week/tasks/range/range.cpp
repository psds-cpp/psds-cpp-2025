#include <vector>

// -11 -1 1   =  -11 -10 -9 -8 -7 -6 -5 -4 -3 -2
// -1 -11 -1
// 15 20 2    =  15 17 19
// 15 20 1    =  15 16 17 18 19


std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> res;

    // Определение валидности аргументов
    if(from > to && step > 0) return res;
    if(from < to && step < 0) return res;
    if(step == 0) return res;

    // Определение размера
    size_t size = std::abs(to - from) % std::abs(step) == 0 ? 
                        std::abs(to - from) / std::abs(step) : 
                        std::abs(to - from) / std::abs(step) + 1;
    res.reserve(size);

    if(from < to){
        for(int i = from; i < to; i += step){
            res.push_back(i);
        }
    }
    else{
        for(int i = from; i > to; i += step){
            res.push_back(i);
        }
    }


    return res;
}

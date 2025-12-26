#include <stdexcept>
#include <vector>

/*
Функция принимает std::vector<int>
и указатель на функцию предикат, и оставляет в контейнере элементы, 
удовлетворяющие предикату, в исходном порядке. 
Нельзя алгоритм
Алгоритм долэен проходить за O(n)
*/

using PredicatePtr = bool(*)(int);
void Filter(std::vector<int>& array, PredicatePtr predicate) {
    if (!predicate) return;

    
    size_t writeIndex = 0;
    
    for (size_t readIndex = 0; readIndex < array.size(); ++readIndex) {
        if (predicate(array[readIndex])) {
            if (writeIndex != readIndex) {
                array[writeIndex] = std::move(array[readIndex]);
            }
            ++writeIndex;
        }
    }
    
    array.resize(writeIndex);
}
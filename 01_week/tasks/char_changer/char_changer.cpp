#include <cstddef>
#include <stdexcept>
#include <cctype>

void ProcessOneSymbol(char* array, size_t& pos, char symbol, size_t count){
    array[pos] = symbol;
    if (count >= 10){
        ++pos;
        array[pos] = '0';
    }
    else if (count > 1){
        ++pos;
        array[pos] = count + '0';
    }
}

size_t Counter(char array[], size_t size, size_t startIdx){
    char symbol = array[startIdx];
    size_t count = 1;
    for (size_t i = startIdx + 1; i < size - 1; ++i) {
        if (array[i] == symbol) ++count;
        else break;
    }
    return count;
}

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t count = 0;
    size_t new_ar_pos = 0;
    for (size_t i=0; i<size-1;){
        count = Counter(array, size, i);

        if (std::isblank(array[i])){
            array[new_ar_pos] = delimiter;
        }
        else if (std::isdigit(array[i])){
            ProcessOneSymbol(array, new_ar_pos, '*', count);
        }
        else if (std::islower(array[i])){
            ProcessOneSymbol(array, new_ar_pos, std::toupper(array[i]), count);
        }
        else if (std::isupper(array[i])){
            ProcessOneSymbol(array, new_ar_pos, array[i], count);
        }
        else{
            ProcessOneSymbol(array, new_ar_pos, '_', count);
        }
        i += count;
        ++new_ar_pos;
    }

    array[std::min(new_ar_pos, size - 1)] = '\0';
    return new_ar_pos;
}
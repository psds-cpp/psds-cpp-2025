#include <cstddef>
#include <stdexcept>
#include <bits/stdc++.h>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t cntRepeat = 0;
    char res[size] = {0};
    size_t resInd = 0;

    auto parse = [&](size_t i, char symbol) {
        if (i > 0 && array[i] == array[i-1]) {
            if (cntRepeat != 1)
                --resInd;
            ++cntRepeat;
            res[resInd] = (cntRepeat > 9) ? '0' : '0' + cntRepeat;
        }
        else {
            res[resInd] = symbol;
            cntRepeat = 1;
        }
        ++resInd;
    };

    for (size_t i = 0; i < size; ++i) {
        if (isdigit(array[i])) {
            parse(i, '*');
        }
        else if (islower(array[i])) {
            parse(i, array[i] - ' ');
        }
        else if (isupper(array[i])) {
            parse(i, array[i]);
        }  
        else if (isspace(array[i])) {
            res[resInd] = delimiter;
            ++resInd;
            while (isspace(array[i])) {
                ++i;
            } 
            --i;
        }
        else if (array[i] != '\0')
            parse(i, '_');
    }
    
    for (size_t i = 0; i < size; ++i)
        array[i] = res[i];

    return resInd;
}

#include <cstddef>
#include <stdexcept>
#include <bits/stdc++.h>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t cntRepeat = 0;
    char* res = (char*)calloc(size, sizeof(char));
    size_t resInd = 0;

    auto parse = [&](size_t i, char cymbol) {
        if (array[i] == array[i-1]) {
            if (cntRepeat != 1)
                --resInd;
            ++cntRepeat;
            res[resInd] = (cntRepeat > 9) ? '0' : '0' + cntRepeat;
        }
        else {
            res[resInd] = cymbol;
            cntRepeat = 1;
        }
        ++resInd;
    };

    for (size_t i = 0; i < size; ++i) {
        if (48 <= array[i] && array[i] <= 57)
            parse(i, '*');
        else if (97 <= array[i] && array[i] <= 122)
            parse(i, array[i] - ' ');
        else if (65 <= array[i] && array[i] <= 90)
            parse(i, array[i]);
        else if (array[i] == 32) {
            res[resInd] = delimiter;
            ++resInd;
            while (array[i] == ' ')
                ++i;
            --i;
        }
        else if (array[i] != '\0')
            parse(i, '_');
    }
    
    for (size_t i = 0; i < size; ++i)
        array[i] = res[i];

    free(res);
    return resInd;
}

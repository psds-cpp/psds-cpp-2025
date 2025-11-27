#include <cstddef>
#include <cctype>
#include <string>
#include <cstring>

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    char prev_ch = array[0];
    int count_repeat = 1;

    std::string tmp;

    tmp.reserve(size);

    for (size_t i = 1; i < size - 1; ++i) {
        if (array[i] == prev_ch) {
            if (array[i] != ' ') {
                ++count_repeat;
            }
        }
        else {
            if (std::isdigit(prev_ch)) {
                tmp += '*';
            }
            else if (std::isalpha(prev_ch)) {
                tmp += std::toupper(prev_ch);
            }
            else if (prev_ch == ' ') {
                tmp += delimiter;
            }
            else {
                tmp += '_';
            }

            if ((count_repeat > 1) && (prev_ch != ' ')) {
                if (count_repeat < 10) {
                    tmp += std::to_string(count_repeat);
                }
                else {
                    tmp += '0';
                }
                count_repeat = 1;
            }
        }

        prev_ch = array[i];
    }

    if (std::isdigit(prev_ch)) {
        tmp += '*';
    }
    else if (std::isalpha(prev_ch)) {
        tmp += std::toupper(prev_ch);
    }
    else if (prev_ch == ' ') {
        tmp += delimiter;
    }
    else {
        tmp += '_';
    }

    if ((count_repeat > 1) && (prev_ch != ' ')) {
        if (count_repeat < 10) {
            tmp += std::to_string(count_repeat);
        }
        else {
            tmp += '0';
        }
    }

    std::strcpy(array, tmp.c_str());

    return std::strlen(array);
}
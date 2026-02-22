#include <cstddef>
#include <cctype>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    //Массив для подстановки кол-ва повторений
    char intToChar[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    size_t i = 0;                  
    size_t j = 1;
    size_t str_end = 0;

    int reps = 1;                  // кол-во повторений символа
    while (j < size) {
        if (array[i] == array[j]) {
            ++reps;
            ++j;           
            continue;
        }
        
        array[str_end] = array[i];
        if (reps != 1 && array[i] != ' ') {
            array[str_end+1] = reps < 10 ? intToChar[reps] : intToChar[0];
        }

        if (char c = array[str_end]; std::isalpha(c) && std::islower(c)) {
            array[str_end] = std::toupper(c);
        }
        else if (array[str_end] == ' ') {
            array[str_end] = delimiter;
            ++str_end;
            i = j++;
            reps = 1;
            continue;
        }
        else if (std::isdigit(array[str_end])) {
            array[str_end] = '*';
        }
        else if (!(std::isalpha(array[str_end]))) {
            array[str_end] = '_';
        }

        if (reps == 1) {
            ++str_end;
        }
        else {
            str_end+= 2;
            reps = 1;
        }
        i = j++;
    }
    array[str_end] = '\0';
    return str_end;
}

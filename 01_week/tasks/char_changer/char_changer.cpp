#include <cstddef>
#include <cctype>


size_t CharChanger(char array[], size_t, char delimiter = ' ') {
    int counterRepeatedSymbols = 1; // Счётчик повторяющихся символов
    int pos_write = 0;   // Индекс для записи обработанного символа
    char repeating_symbol = array[0]; // В процессе выполнения - предыдущий символ(отслеживаем повторения)

    for (char* ptr = array + 1; repeating_symbol != '\0'; ++ptr) {
        if (repeating_symbol == *ptr){
            ++counterRepeatedSymbols;
            continue;
        } 

        if (isalpha(repeating_symbol)){
            array[pos_write] = toupper(repeating_symbol);
        } else if (isdigit(repeating_symbol)){
            array[pos_write] = '*';
        } else if (repeating_symbol == ' '){
            array[pos_write] = delimiter;
        } else {
            array[pos_write] = '_';
        }
        ++pos_write;


        if (repeating_symbol == ' ') {
            counterRepeatedSymbols = 1;
        }

        if (counterRepeatedSymbols >= 10){
            counterRepeatedSymbols = 0;
        }

        if (counterRepeatedSymbols != 1){
            array[pos_write] = static_cast<char>(counterRepeatedSymbols + '0'); // Преобразуем число в символ
            counterRepeatedSymbols = 1;
            ++pos_write;
        }

        repeating_symbol = *ptr;
    }

    array[pos_write] = '\0';
    return pos_write;     
}

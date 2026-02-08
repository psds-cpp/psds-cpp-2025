#include <cstddef>
#include <cctype>


size_t CharChanger(char array[], size_t, char delimiter = ' ') {
    int counter = 0; // Счётчик повторяющихся символов
    int pos_write = 0;   // Индекс для записи обработанного символа
    int pos_read = 0;    // Индекс для чтения следующего элемента из массива
    char repeating_symbol = array[pos_read]; // В процессе выполнения - предыдущий символ после pos_read(отслеживаем повторения)

    while (repeating_symbol != '\0'){
        if (repeating_symbol == array[pos_read]){
            ++counter;
        } else {
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
                counter = 1;
            }

            if (counter >= 10){
                counter = 0;
            }

            if (counter != 1){
                array[pos_write] = static_cast<char>(counter + '0'); // Преобразуем число в символ
                counter = 1;
                ++pos_write;
            }

            repeating_symbol = array[pos_read];
        }

        ++pos_read;
    }

    array[pos_write] = '\0';
    return pos_write;     
}

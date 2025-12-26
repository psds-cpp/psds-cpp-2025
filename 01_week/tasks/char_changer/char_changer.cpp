#include <cstddef>
#include <locale>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    // k - указатель для массива array без дубликатов
    size_t k = 0;

    // size - размер массива с учётом '\0' в конце
    for (size_t i = 0; i < size - 1; ++i) {
        // сохраняем символ до его замены и приводим его к uint 
        // функции isdigit, islower и др. не работают с отрицательным кодами
        char old_symbol = static_cast<unsigned int>(array[i]);

        // определяем тип замены
        if (isdigit(old_symbol)) {
            array[k++] = '*';
        }
        else if (old_symbol == ' ') {
            array[k++] = delimiter;
        }
        else if (islower(old_symbol)) {
            array[k++] = toupper(old_symbol);
        }
        else if (isupper(old_symbol)) {
            array[k++] = old_symbol;
        }
        else {
            array[k++] = '_';
        }

        // поиск и подсчёт дубликатов
        size_t j = i + 1;
        while (j < size && array[j] == old_symbol) {
            ++j;
        }

        // если есть дубликаты
        if (size_t duplicates = j - i - 1; duplicates > 0) {
            // обновляем указатель i
            i += duplicates;

            // добавляем счётчик после повторяющегося символа (кроме ' ')
            if (old_symbol != ' ')
                array[k++] = duplicates + 1 >= 10 ? '0' : duplicates + 1 + '0';
        }
    }

    // устанавливаем новый конец массива
    array[k] = '\0';

    return k;
}

#include <cstddef>
#include <stdexcept>

size_t CharChanger(char* array, size_t size, char delimiter) {
    if (size == 0) return 0;

    size_t writePos = 0;     // куда пишем результат
    size_t readPos = 0;      // откуда читаем исходные символы

    while (readPos < size - 1) {    // последний символ — '\0'
        char currentChar = array[readPos];

        // Приведения текущего символа к определенным типам: пробел, число или ASCII символ
        bool isSpace = std::isspace(static_cast<unsigned char>(currentChar)) != 0;
        bool isDigit = std::isdigit(static_cast<unsigned char>(currentChar)) != 0;
        bool isAlpha = std::isalpha(static_cast<unsigned char>(currentChar)) != 0;

        // Подсчёт длины последовательности одинаковых символов
        size_t nextPos = readPos + 1;
        while (nextPos < size - 1 && array[nextPos] == currentChar) {
            nextPos++;
        }
        size_t runLength = nextPos - readPos;

        // Обработка пробелов
        if (isSpace) {
            array[writePos++] = delimiter;
        } else {
            char outChar;

            if (isDigit) {
                outChar = '*';
            } else if (isAlpha) {
                if (std::islower(static_cast<unsigned char>(currentChar))) {
                    outChar = std::toupper(static_cast<unsigned char>(currentChar));
                } else {
                    outChar = currentChar; // буква и так прописная
                }
            } else {
                outChar = '_';
            }

            array[writePos++] = outChar;

            // Добавление количества повторений
            if (runLength > 1) {
                if (runLength >= 10) {
                    array[writePos++] = '0';
                } else {
                    array[writePos++] = char('0' + runLength);
                }
            }
        }

        readPos = nextPos;
    }

    array[writePos] = '\0';
    return writePos;
}
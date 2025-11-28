#include <cstddef>
#include <stdexcept>

size_t CharChanger(char array[], size_t size, char delimiter = ' ')
{

    size_t temp_ptr = 0; // переменная для хранения текущего положения данных  в массиве

    for (size_t i = 0; i < size; ++i)
    {

        if (isalnum(array[i]))
        { // если это буква-цифра
            if (isalpha(array[i]))
            { // если это буква
                size_t temp = 1;
                if (i + 1 < size)
                    while (temp + i < size && array[i] == array[i + temp])
                        ++temp;
                array[temp_ptr] = array[i];
                if (islower(array[i]))
                { // если она низкая, делаем ее высокой
                    array[temp_ptr] = toupper(array[temp_ptr]);
                }
                ++temp_ptr;    // счетчик на конец преобразованного массива +1
                i += temp - 1; // смещаем счетчик рабочий

                if (temp > 1)
                {                                                                          // если у нас много повторяющихся букоф
                    temp >= 10 ? (array[temp_ptr] = '0') : (array[temp_ptr] = '0' + temp); // ставим число повторений, либо 0, если повторений больше 10
                    ++temp_ptr;                                                            // увеличиваем рабочий счетчик
                }
            }
            else
            { // обрабатываем цифры
                size_t temp = 1;
                while (temp + i < size && array[i] == array[i + temp])
                    ++temp;
                array[temp_ptr] = '*';
                ++temp_ptr;
                i += temp - 1;
                if (temp > 1)
                {                                                                          // если у нас много повторяющихся цифр
                    temp >= 10 ? (array[temp_ptr] = '0') : (array[temp_ptr] = '0' + temp); // ставим число повторений, либо 0, если повторений больше 10
                    ++temp_ptr;                                                            // увеличиваем рабочий счетчик
                }
            }
        }
        else
        {
            if (array[i] != ' ')
            {
                // обрабатываем символы..
                size_t temp = 1;
                while (temp + i < size && array[i] == array[i + temp])
                    ++temp;
                array[temp_ptr] = '_';
                ++temp_ptr;
                if (temp > 1)
                {                                                                          
                    temp >= 10 ? (array[temp_ptr] = '0') : (array[temp_ptr] = '0' + temp); 
                    ++temp_ptr;                                                            
                }
                i += temp - 1;
            }
            else
            { //...если это не пробел. если пробел, то все ок, меняем:
                size_t temp = 1;
                while (temp + i < size && array[i] == array[i + temp])
                    ++temp;
                i += temp - 1;
                array[temp_ptr] = delimiter;
                ++temp_ptr;
            }
        }
    }
    for (size_t i = temp_ptr; i < size; ++i)
    {
        array[i] = '\0'; // зануляем все оставшееся место в памяти
    }
    return temp_ptr;
}

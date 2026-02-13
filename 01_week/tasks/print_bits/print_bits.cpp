#include <cstddef>
#include <stdexcept>


void PrintBits(long long value, size_t bytes) {

// Защита от неверного значения размера в байтах. Размер в байтах должен быть от 1 до 8.
if(bytes == 0)  return;    
if(bytes > 8) return;

char buf[90] = {'\0'};    // Объявление и инициализация массива '\0'.

// !!!! Важно!!!!! 
// при отладке были проблемы, по ну установленной причине при переводе от 5 до 8 байт некорректно выводилось значение. Связано это было с некорректным смещением 0х01. Даже если 0х01 присваивалось 64 битной переменной при смещении на значение от 32 до 64, результат был не верный, в результате анализа добегу переменная смещалось на 32 и все. 
// Поэтом начались танцы с бубном и все переменные сделаны 8 битными.
unsigned long long count = 0;        // Счётчик проанализированных бит 
unsigned long long temp = 0;
unsigned long long sizeBit = bytes*8;    // количество бит для вывода
unsigned long long countFour = 0;
unsigned long long countBuf = 0;    // счетчик для элементов массива
unsigned long long countBit = 0;
char res;    //
unsigned long long tempBit = 0;
    
    buf[0] = '0';    // присвоение значения первому элементу массива
    buf[1] = 'b';    // присвоение значения второму элементу массива

    countBuf = 2;

    while( count < sizeBit)    // Проверка количество проанализированных бит совпала с требуемым?
    {    // Нет, анализируем.
        
        //Усложнённая конструкция но без нее работало не корректно.
        temp = (sizeBit-1 - count);
        countBit = 0;
        tempBit = 0x01;
        while(temp > countBit)
        {
            countBit ++;
            tempBit = tempBit << 1;
        }
        //Конец сложной конструкции. ее можно было свирнуть до temp = 0х01 << (sizeBit-1 - count); но так не работало при значении coun< 32.

        temp = tempBit & value;    // определение 0 или 1 для конкретного бита. 
        
        if(temp)    res = '1';
        else        res = '0';
        
        buf[countBuf + count] = res;    // Запись значения в массив.
        
        count++;    // Увеличиваема счетчик 

        if(countFour == 3)    // После 4х значении надо вывести символ ''' (номер 39 в таблице ASCII).
        {
            if(sizeBit != count)
            {
                buf[countBuf + count] = 39;
                countBuf++;
            }
            countFour = 0;
        }
        else countFour++;
        
    }
    buf[countBuf+count] = '\n';    // последний элемент массива '\n'
    
    
    std::cout << buf;    // Вывод результата.
}

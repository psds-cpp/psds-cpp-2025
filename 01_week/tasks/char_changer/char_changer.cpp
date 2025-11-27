#include <cstddef>
#include <cctype>


size_t CharChanger(char array[], size_t size, char delimiter = ' '){
    //Массив для подстановки кол-ва повторений
    char intToChar[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    //Индексы
    size_t i = 0;                  
    size_t j = 1;
    size_t k = 0;

    int reps = 1;                  // кол-во повторений символа
    while(j < size){
        // Если есть повторы, то сначала считаются они
        if(array[i] == array[j]){
            ++reps;
            j++;           
            continue;
        }
        
        array[k] = array[i];
        //Если повторы были, то записывается число
        if(reps != 1 && array[i] != ' '){
            array[k+1] = reps < 10 ? intToChar[reps] : intToChar[0];
        }

        //Проверка, что это символ алфавита и он в нижнем регистре
        if(char c = array[k]; std::isalpha(c) && std::islower(c)){
            array[k] = std::toupper(c);
        }
        //Отдельно обрабатываются пробелы
        else if(array[k] == ' '){
            array[k] = delimiter;
            ++k;
            i = j++;
            reps = 1;
            continue;
        }
        //Замена цифр
        else if(std::isdigit(array[k])){
            array[k] = '*';
        }
        //Замена остальных символов
        else if(!(std::isalpha(array[k]))){
            array[k] = '_';
        }

        //Сдвигаем индексы в зависимости от повторов
        if(reps == 1){
            ++k;
        }
        else if(reps != 1){
            k+= 2;
            reps = 1;
        }
        i = j++;
    }

    //В конце добавляется нуль-терминатор
    array[k] = '\0';
    
    return k;
}

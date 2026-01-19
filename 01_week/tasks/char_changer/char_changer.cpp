#include <cstddef>
#include <stdexcept>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    if (size == 0) return 0;
    
    char* pread = array;
    char* pwrite = array;
    
    while (*pread != '\0' && (pread - array) < static_cast<ptrdiff_t>(size - 1)) {
        char tek_char = *pread;
        int repeat_count = 1;
        
        // Ограничиваем подсчет повторений границами массива
        while (repeat_count < static_cast<int>(size - (pread - array)) && 
               pread[repeat_count] == tek_char) {
            repeat_count++;
        }
        
        if (tek_char == ' ') {
            *pwrite = delimiter;
            pwrite++;
            pread += repeat_count;
            continue;
        }
        
        char temp;
        if (std::isdigit(tek_char)) {
            temp = '*';
        } else if (std::isupper(tek_char)) {
            temp = tek_char;
        } else if (std::islower(tek_char)) {
            temp = std::toupper(tek_char);
        } else {
            temp = '_';
        }
        
        *pwrite = temp;
        pwrite++;
        
        if (repeat_count > 1) {
            if (repeat_count >= 10) {
                *pwrite = '0';
                pwrite++;
            } else {
                *pwrite = '0' + repeat_count;
                pwrite++;
            }
        }
        
        pread += repeat_count;
    }
    
    *pwrite = '\0';
    return pwrite - array;
}

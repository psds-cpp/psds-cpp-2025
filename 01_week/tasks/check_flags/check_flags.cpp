#include <cstdint>
#include <stdexcept>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    
    char buf[40] = {'\0'};
    uint8_t data = static_cast<uint8_t>(flags); // приведение типа к uint8_t т.к. CheckFlags типа uint8_t
    size_t i = 0;
    
    buf[0] = '[';
    i =1;
    // Проверка наличия "лишних флагов", ALL приводим к типу uint8_t
    // Если есть лишние флаги, выходим.
    if(data > static_cast<uint8_t>(CheckFlags::ALL))        return;
    if(data != 0) 
    {
            if(data & static_cast<uint8_t>(CheckFlags::TIME)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'T'; buf[i++] = 'I'; buf[i++] = 'M'; buf[i++] = 'E';
            }
            if(data & static_cast<uint8_t>(CheckFlags::DATE)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'D'; buf[i++] = 'A'; buf[i++] = 'T'; buf[i++] = 'E';
            } 
            if(data & static_cast<uint8_t>(CheckFlags::USER)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'U'; buf[i++] = 'S'; buf[i++] = 'E'; buf[i++] = 'R';
            }
            if(data & static_cast<uint8_t>(CheckFlags::CERT)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'C'; buf[i++] = 'E'; buf[i++] = 'R'; buf[i++] = 'T';
            }
            if(data & static_cast<uint8_t>(CheckFlags::KEYS)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'K'; buf[i++] = 'E'; buf[i++] = 'Y'; buf[i++] = 'S';
            } 
            if(data & static_cast<uint8_t>(CheckFlags::DEST)){
                if(buf[i-1] != '['){
                    buf[i] = ',';
                    i++;
                } 
                
                buf[i++] = 'D'; buf[i++] = 'E'; buf[i++] = 'S'; buf[i++] = 'T';
            } 
    }
    
    buf[i] = ']';
    std::cout << buf; 
}

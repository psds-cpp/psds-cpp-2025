#include <cstddef>
#include <stdexcept>
#include <string>

void PrintBits(long long value, size_t bytes) {
    std::string byteForm = "0b";
    // i < bytes * 8 сработает, потому что 0ULL - 1 переполняется в ULL_MAX
    for (size_t i = (bytes * 8 - 1); i < bytes * 8; --i) {
       byteForm += ((value >> i) & 0x01U) + '0';

       if (i != 0 && i % 4 == 0) {
            byteForm += "'";    
       }
    }

    std::cout << byteForm << std::endl;
}

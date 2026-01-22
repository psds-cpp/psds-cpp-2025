#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

void Print(unsigned char* byte_ptr, size_t bytes, bool shouldInverse){
    std::ostringstream oss;
    oss << "0x";
    
    for (size_t i = 0; i < bytes; ++i) {
        size_t index = shouldInverse ? (bytes - 1 - i) : i;
        oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte_ptr[index]);
    }
    
    oss << "\n";
    std::cout << oss.str();
}

void PrintMemory(int number, bool shouldInverse=false) {
    unsigned char* byte_ptr = reinterpret_cast<unsigned char*>(&number);
    Print(byte_ptr, sizeof(int), shouldInverse);
}

void PrintMemory(double number, bool shouldInverse=false) {
    unsigned  char* byte_ptr = reinterpret_cast<unsigned  char*>(&number);
    Print(byte_ptr, sizeof(double), shouldInverse);
}
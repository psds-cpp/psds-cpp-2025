#include <stdexcept>
#include <iostream>
#include <string>


void PrintMemory(int num, bool is_inverted = false)
{
    
        int size = sizeof(int);
        unsigned char *conv = reinterpret_cast<unsigned char *>(&num); // указатель на конкретный бит в инте
        std::string str;                                    // строка, которую мы выведем

        char dict[] = {"0123456789ABCDEF"}; // массив символов, в которые мы будем переводить

        if (is_inverted) //big endian
        {
            conv += size-1;
            for (; conv >= reinterpret_cast<unsigned char *>(&num); --conv)
            {
                str.push_back(dict[*conv >> 4]);
                str.push_back(dict[*conv & 0b00001111]);
            }
        }

        else // little endian
        {
            for (; conv - reinterpret_cast<unsigned char *>(&num) < size; ++conv)
            {
                str.push_back(dict[*conv >> 4]);
                str.push_back(dict[*conv & 0b00001111]);
            }
        }
        std::cout << "0x" << str << std::endl;
    
    
}

void PrintMemory(double num, bool is_inverted = false)
{
   
        int size = sizeof(double);
        unsigned char *conv = reinterpret_cast<unsigned char *>(&num); // указатель на конкретный бит в дабле
        std::string str;// строка, которую мы выведем

        char dict[] = {"0123456789ABCDEF"}; // массив символов, в которые мы будем переводить

        if (is_inverted) //big endian
        {
            conv += size-1;
            for (; conv >= reinterpret_cast<unsigned char *>(&num); --conv)
            {
                str.push_back(dict[*conv >> 4]);
                str.push_back(dict[*conv & 0b00001111]);
            }
        }

        else // little endian
        {
            for (; conv - reinterpret_cast<unsigned char *>(&num) < size; ++conv)
            {
                str.push_back(dict[*conv >> 4]);
                str.push_back(dict[*conv & 0b00001111]);
            }
        }


        std::cout << "0x" << str << std::endl;
    
    
}

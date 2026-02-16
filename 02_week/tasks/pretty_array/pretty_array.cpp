#include <stdexcept>
#include <iostream>



void PrintArray(const int* begin, const int* end, size_t ogr = 0) {
    /*if (begin == nullptr or end == nullptr){
        return;
    }*/
    
    size_t i_ogr = 1;
    std::cout <<"[";

    if (end >= begin){
        int* p = const_cast<int*>(begin);
        while (p < end){
            std::cout << *p;
            if (p + 1 != end){
                std::cout <<", ";
                if (ogr != 0 and i_ogr == ogr){
                    std::cout << "..." << std::endl << " ";
                    i_ogr = 0;
                }
            }

            p++;
            i_ogr++;
        }
    }
    else{
        int* p = const_cast<int*>(end);
        p--;
        while (p >= begin){
            std::cout << *p;
            if (p != begin){
                std::cout <<", ";
                if (ogr != 0 and i_ogr == ogr){
                    std::cout << "..." << std::endl << " ";
                    i_ogr = 0;
                }
            }

            p--;
            i_ogr++;
        }
    }


    std::cout << "]" << std::endl;
}
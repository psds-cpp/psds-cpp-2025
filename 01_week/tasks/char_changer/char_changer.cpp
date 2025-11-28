#include <cstddef>
#include <cctype>
#include <cstring>

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t w = 0; 
    auto map_char = [&](char ch) -> char {
        unsigned char uc = ch; //в этом месте возникала ошибка, решено использовать unsigner
        if (std::isspace(uc)) return delimiter;
        if (std::isdigit(uc)) return '*';
        if (std::isalpha(uc)) return (char)std::toupper(uc);
        return '_'; };
    size_t r = 0; 
    while (r < size && array[r] != '\0') {
        char current = array[r];
        char mapped = map_char(current);
        size_t count = 1;
        size_t next = r + 1;
        while (next < size && array[next] != '\0') {
            char next_char = array[next];
            char mapped_next = map_char(next_char);           
            if (mapped_next != mapped) break;
            if (mapped == '*' || mapped == '_') {
                if (current != next_char) break; 
            } else if (mapped >= 'A' && mapped <= 'Z') {
                unsigned char curr_uc = current;
                unsigned char next_uc = next_char;
                if (std::islower(curr_uc) != std::islower(next_uc)) break; }
            count++;
            next++;}
        unsigned char current_uc = current;
        bool is_space_seq = (mapped == delimiter) && std::isspace(current_uc);   
        if (is_space_seq) { 
            bool is_letter_delimiter = (delimiter >= 'A' && delimiter <= 'Z'); 
            if (is_letter_delimiter || w == 0 || array[w - 1] != delimiter) {
                array[w++] = delimiter;}
        } else { 
            array[w++] = mapped;
            if (count > 1) {
                char repeat_char = (count < 10) ? ('0' + count) : '0';
                array[w++] = repeat_char;}}
        r += count; }
    array[w] = '\0'; 
    return w;
}
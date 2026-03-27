#include "task2.hpp"

bool is_Russian_Letter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    // заглавные А-Я: 192-223, строчные а-я: 224-255, Ё: 168, ё: 184
    return (uc >= 192 && uc <= 255) || uc == 168 || uc == 184;
}

char to_Lower_Russian(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    if (uc >= 192 && uc <= 223) return static_cast<char>(uc + 32);   // заглавная -> строчная
    if (uc == 168) return static_cast<char>(184);                    // Ё -> ё
    return c;
}

bool is_Vowel(char c) {
    c = to_Lower_Russian(c);
    const char* vowels = "аеёиоуъыьэюя";
    while (*vowels) {
        if (*vowels == c) return true;
        ++vowels;
    }
    return false;
}

bool is_Consonant(char c) {
    c = to_Lower_Russian(c);
    const char* consonants = "бвгджзйклмнпрстфхцчшщ";
    while (*consonants) {
        if (*consonants == c) return true;
        ++consonants;
    }
    return false;
}

bool is_Letter_Or_Digit(char c) {
    return is_Russian_Letter(c) || (c >= '0' && c <= '9');
}

bool str_Equal(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i]) ++i;
    return a[i] == 0 && b[i] == 0;
}

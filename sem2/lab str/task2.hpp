#pragma once

// ========== Структура для хранения слова ==========
struct Word {
    char text[256];
    int length;
};

// ========== Вспомогательные функции для работы с русскими буквами (CP1251) ==========
bool is_Russian_Letter(char c);
char to_Lower_Russian(char c);
bool is_Vowel(char c);
bool is_Consonant(char c);
bool is_Letter_Or_Digit(char c);

// Сравнение двух C-строк
bool str_Equal(const char* a, const char* b);

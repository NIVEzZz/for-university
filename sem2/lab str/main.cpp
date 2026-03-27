#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <windows.h>   // для установки кодировки консоли

// ========== Вспомогательные функции для работы с русскими буквами (кодировка CP1251) ==========

bool isRussianLetter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    // заглавные А-Я: 192-223, строчные а-я: 224-255, Ё: 168, ё: 184
    return (uc >= 192 && uc <= 255) || uc == 168 || uc == 184;
}

char toLowerRussian(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    if (uc >= 192 && uc <= 223) return static_cast<char>(uc + 32);   // заглавная -> строчная
    if (uc == 168) return static_cast<char>(184);                    // Ё -> ё
    return c;
}

bool isVowel(char c) {
    c = toLowerRussian(c);
    const char* vowels = "аеёиоуъыьэюя";
    while (*vowels) {
        if (*vowels == c) return true;
        ++vowels;
    }
    return false;
}

bool isConsonant(char c) {
    c = toLowerRussian(c);
    const char* consonants = "бвгджзйклмнпрстфхцчшщ";
    while (*consonants) {
        if (*consonants == c) return true;
        ++consonants;
    }
    return false;
}

bool isLetterOrDigit(char c) {
    return isRussianLetter(c) || (c >= '0' && c <= '9');
}

bool strEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i]) ++i;
    return a[i] == 0 && b[i] == 0;
}

// ========== Структура для хранения слова ==========
struct Word {
    char text[256];   // слово в нижнем регистре
    int length;       // длина (количество символов)
};

// ========== Задача 1 ==========
void task1() {
    char str[101];
    std::cout << "Введите строку (не более 100 символов): ";
    std::cin.getline(str, 101);

    // Удаляем знаки препинания (перечисляем основные)
    int i = 0, j = 0;
    while (str[i]) {
        char c = str[i];
        if (c != '.' && c != ',' && c != '!' && c != '?' && c != ';' && c != ':' &&
            c != '-' && c != '(' && c != ')' && c != '[' && c != ']' &&
            c != '{' && c != '}' && c != '"' && c != '\'') {
            str[j++] = c;
        }
        ++i;
    }
    str[j] = '\0';

    std::cout << "Результат: " << str << std::endl;
}

// ========== Задача 2 ==========
void task2() {
    // Читаем N из файла input.txt
    FILE* fin = fopen("input.txt", "r");
    if (!fin) {
        std::cerr << "Ошибка: не удалось открыть input.txt" << std::endl;
        return;
    }
    int N;
    fscanf(fin, "%d", &N);
    fclose(fin);

    // Читаем весь текст из файла text.txt
    FILE* ftxt = fopen("text.txt", "rb");
    if (!ftxt) {
        std::cerr << "Ошибка: не удалось открыть text.txt" << std::endl;
        return;
    }
    fseek(ftxt, 0, SEEK_END);
    long fsize = ftell(ftxt);
    fseek(ftxt, 0, SEEK_SET);
    char* text = new char[fsize + 1];
    fread(text, 1, fsize, ftxt);
    text[fsize] = '\0';
    fclose(ftxt);

    // Динамический массив для уникальных слов
    Word* words = nullptr;
    int size = 0;
    int capacity = 0;

    int pos = 0;
    while (text[pos]) {
        // Пропускаем символы, не являющиеся буквами или цифрами (разделители)
        while (text[pos] && !isLetterOrDigit(text[pos])) ++pos;
        if (!text[pos]) break;

        // Собираем текущее слово в буфер (только буквы и цифры)
        char word[256];
        int wordLen = 0;
        while (text[pos]) {
            if (isLetterOrDigit(text[pos])) {
                word[wordLen++] = toLowerRussian(text[pos]);
                ++pos;
            }
            else {
                // Внутренний дефис (например, "что-то") – пропускаем, слово продолжается
                if (text[pos] == '-' && text[pos + 1] && isLetterOrDigit(text[pos + 1])) {
                    ++pos;
                    continue;
                }
                else {
                    break;   // любой другой символ – конец слова
                }
            }
        }

        // Обрабатываем слово: отбрасываем конечные цифры
        if (wordLen > 0) {
            int lastLetter = -1;
            for (int k = wordLen - 1; k >= 0; --k) {
                if (isRussianLetter(word[k])) {
                    lastLetter = k;
                    break;
                }
            }
            if (lastLetter >= 0) {
                wordLen = lastLetter + 1;
                word[wordLen] = '\0';

                // Подсчёт гласных и согласных
                int vowels = 0, consonants = 0;
                for (int k = 0; k < wordLen; ++k) {
                    if (isVowel(word[k])) ++vowels;
                    else if (isConsonant(word[k])) ++consonants;
                }

                if (vowels == consonants) {
                    // Проверка уникальности
                    bool already = false;
                    for (int k = 0; k < size; ++k) {
                        if (strEqual(words[k].text, word)) {
                            already = true;
                            break;
                        }
                    }
                    if (!already) {
                        // Добавляем слово
                        if (size == capacity) {
                            capacity = (capacity == 0) ? 10 : capacity * 2;
                            Word* newWords = new Word[capacity];
                            for (int k = 0; k < size; ++k)
                                newWords[k] = words[k];
                            delete[] words;
                            words = newWords;
                        }
                        for (int k = 0; k < wordLen; ++k)
                            words[size].text[k] = word[k];
                        words[size].text[wordLen] = '\0';
                        words[size].length = wordLen;
                        ++size;
                    }
                }
            }
        }
    }

    delete[] text;

    if (size == 0) {
        std::cout << "Нет подходящих слов." << std::endl;
        FILE* fout = fopen("result.txt", "w");
        fclose(fout);
        delete[] words;
        return;
    }

    // Сортировка по убыванию длины
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (words[j].length < words[j + 1].length) {
                Word tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }

    // Запись результата
    FILE* fout = fopen("result.txt", "w");
    int count = (N < size) ? N : size;
    for (int i = 0; i < count; ++i) {
        fprintf(fout, "%s\n", words[i].text);
    }
    fclose(fout);

    delete[] words;
    std::cout << "Результат записан в result.txt" << std::endl;
}

// ========== Главная функция ==========
int main() {
    // Устанавливаем кодировку консоли на 1251, чтобы русские буквы выводились корректно
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "=== Задача 1 ===" << std::endl;
    //task1();

    std::cout << "\n=== Задача 2 ===" << std::endl;
    task2();

    return 0;
}

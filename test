#include <iostream>
using namespace std;

// Функция для смены значения i-ого бита и нулевого бита в числе n
unsigned int swapZeroAndIBit(unsigned int n, unsigned int i) {
    // Извлекаем значения битов на позициях 0 и i
    unsigned int bit0 = n & 1;                     // Нулевой бит
    unsigned int bitI = (n >> i) & 1;               // i-ый бит
    
    // Если биты равны, ничего не меняем
    if (bit0 == bitI) return n;
    
    // Создаем маски для изменения битов
    unsigned int mask = (1 << i) | 1; // Маска для 0-ого и i-ого битов
    
    // Меняем биты с помощью XOR
    return n ^ mask;
}

int main() {
    unsigned int n = 28; // Пример числа (11100 в двоичном виде)
    unsigned int i = 2;  // Позиция бита, который будем менять с нулевым
    
    unsigned int result = swapZeroAndIBit(n, i);
    cout << "Результат: " << result << endl; // Вывод результата
    
    return 0;
}

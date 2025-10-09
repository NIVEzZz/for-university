#include <iostream>
#include <bitset>
using namespace std;

short bit_swap(short A, short i) {

    short bit_0 = A & 1; // Получить 0-й бит

    short bit_i = (A >> i) & 1; // Получить i-й бит

    if (bit_0 == bit_i) {
        return A; 
    }

    A ^= 1; // свапнуть 0-й бит
    A ^= (1 << i); // свапнуть i-й бит

    return A;
}

void task_1() {

    short A;
    short i;
    bool bit_i;

    cout << "Введите A" << endl;
    cin >> A;

    cout << "Введите i" << endl;
    cin >> i;

    bitset <8> b1 = A;

    if ((0 <= i) and (i <= 7)) {
        bit_i = b1.test(i); //Проверяет, присвоено ли биту в указанной позиции в bitset значение 1.
        if (bit_i == 0) {
            cout << A << " = " << bit_swap(A, i) << endl;
        }
        else {
            cout << "Введите 3 числа:" << endl;

        }
    }
    else {
        cout << "Неверный номер бита" << endl;
    }
}

void task_2() {

    unsigned short n;

    /*
    Нет смысла использовать unsigned int, т.к. unsigned short хвататет для данной задачи (В России на данный момент 799 - это наибольший номер региона),
    также есть большой запас в символах, т.к. максимальное число, которое можно записать в unsigned short - это 65535
    */

    cout << "Введите номер региона" << endl;
    cin >> n;

    switch (n) {
    case 102:
        cout << "Республика Башкортостан";
        break;
    case 11:
        cout << "Республика Коми";
        break;
    case 13:
        cout << "Республика Мордовия";
        break;
    case 15:
        cout << "Республика Северная Осетия — Алания";
        break;
    case 116:
    case 716:
        cout << "Республика Татарстан (Татарстан)";
        break;
    default:
        cout << "информация временно недоступна";
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    bool c;

    cout << "Выберите подпункт (0,1)" << endl;
    cin >> c;

    c ? task_2() : task_1(); //тернарный оператор

    return 0;
}

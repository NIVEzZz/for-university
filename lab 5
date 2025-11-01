#include <iostream>
#include <limits>
using namespace std;

float punkt_1(short a) {
    cout << "исп. функция возвращения обратного значения" << endl;

    float rev = a;
    return 1 / rev;
}

short punkt_1(short a, short b) {
    cout << "исп. функция квадрата суммы" << endl;

    return a * a + 2 * a * b + b * b;
}

void middle_interval(float a, float b) {
    cout << "исп. функция нахождения центра интервала" << endl;
    double c;
    c = (a + b) / 2.0;
    cout << c << " double" << endl;
}

void task_1() {
    const short NMax = 3;
    short arr[NMax]{0,-8,0};
    short arr_fill[NMax - 1]{0,0};
    short counter = 0;

    cout << "Введите 3 чисела" << endl;
    cout << endl;
    /*for (short j = 0; j < NMax; ++j) {
        cin >> arr[j];
    }
    */
    for (short i = 0; i < NMax; ++i) {
        if (arr[i] != 0) {
            arr_fill[counter] = arr[i];
            ++counter;
        }
    }
    switch (counter) {
    case(1):
        cout << punkt_1(arr_fill[0]) << endl;
        break;
    case(2):
        cout << punkt_1(arr_fill[0],arr_fill[1]) << endl;
        break;
    default:
        cout << "Программа работает с 1 и 2 числами" << endl;
        cout << "Вы ввели " << counter << endl;
        break;
    }

}

void task_2() {
    float a;
    float b;

    cout << "Минимальное значение float: " << numeric_limits<float>::lowest() << endl;
    cout << "Максимальное значение float: " << numeric_limits<float>::max() << endl;
    cout << "\n";
    cout << "Минимальное значение double: " << numeric_limits<double>::lowest() << endl;
    cout << "Минимальное значение double: " << numeric_limits<double>::max() << endl;

    cin >> a >> b;

    middle_interval(a, b);

}

int main() {

    setlocale(LC_ALL, "Russian");

    short c;

    cout << "Выберите подпункт (1,2)" << endl;
    cin >> c;

    switch (c){
    case(1):
        task_1();
        break;
    case(2):
        task_2();
        break;
    default:
        cout << "Такого пункта нет" << endl;
        break;
    }
    return 0;
}

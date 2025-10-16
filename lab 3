#include <iostream>
#include <limits>
using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    bool c;

    cout << "Выберите подпункт (0,1)" << endl;
    cin >> c;

    if (c == false) {
        short n;
        float a;
        float sum = 0;
        float min_number = numeric_limits<float>::max();
        short min_index = 0;
        bool flag_1 = false;

        cout << "Введите количество чисел" << endl;
        cin >> n;

        for (short i = 1; i <= n; ++i) {
            cout << "Введите число" << endl;
            cin >> a;
            if (a < 10.12) {
                flag_1 = true;
                sum += a;
                if (a < min_number) {
                    min_number = a;
                    min_index = i;
                }
            }
        }
        if (flag_1 = true) {
            cout << "Сумма: " << sum << endl;
            cout << "Наменьшее число: " << min_number << endl;
            cout << "Номер наименьшего числа: " << min_index << endl;
        }
        else {
            cout << "Все введенные числа больше 10.12" << endl;
        }
    }
    else {
        short x;
        bool flag_2 = false;
        short pose = 0;
        short pose_3 = 0;
        cout << "Введите X" << endl;
        cin >> x;
        x = abs(x);
        if (x < 1'000) {
            while (x > 0) {
                short d = x % 10;
                if (d == 3) {
                    flag_2 = true;
                    pose_3 = pose;
                    break;
                }
                ++pose;
                x /= 10;
            }
            if (flag_2 == true) {
                cout << "Индекс 3: " << pose_3 << endl;
            }
            else {
                cout << "3 нет" << endl;
            }
        }
        else {
            cout << "Неправельный X" << endl;
        }
    }

    return 0;
}

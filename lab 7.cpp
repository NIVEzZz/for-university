#include <iostream>
#include <vector>
#include <array>
#include <random>

using namespace std;

void print_vector(vector<int> &vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); ++i) {
        bool flag = true;
        cout << vec[i];
        if (i == vec.size() - 1) {
            flag = false;
        }
        if (flag) {
            cout << " ";
        }
    }

    cout << "]";
    cout << endl;
}

void print_arr(array<int, 10>& arr, const int NMax) {
    for (int i = 0; i < NMax; i++) {
        cout << arr[i] << " ";
    }
}

void find_element_in_arr(vector<int> &vec, int number) {
    cout << "[";
    int counter = 0;
    for (int i = 0; i < vec.size(); ++i) {
        bool flag = true;
        if (vec[i] == number) {
            counter++;
        }
    }
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == number) {
            bool flag = true;
            cout << i;
            counter--;
            if (counter <= 0) {
                flag = false;
            }
            if (flag) {
                cout << ",";
            }
        }
    }
    cout << "]";
    cout << endl;
}

bool K_check(int k, int &counter_ch, int &counter_nch, int &max_nch) {
    int i = 1;
    int sum = 0;
    while (sum < k) {
        if (i % 2 == 0) {
            counter_ch++;
        }
        else {
            max_nch = max(max_nch, i);
            counter_nch++;
        }
        sum += i;
        i += 1;
    }
    if ((sum == k) && (sum != 0)) {
        return 1;
    }
    else {
        return 0;
    }
}

void doublecate(vector<int> &vec) {
    int n = vec.size();
    for (int i = 0; i < n; i += 3) {
        vec.reserve(n + 1);
        vec.push_back(vec[n - 1]);
        for (int j = n - 1; j >= i; j--)
            vec[j + 1] = vec[j];

        ++n;
    }
}

void push_ch(vector<int> &vec, int k) {
    int counter = 0;
    for (int i = 2; counter < k; i += 2) {
        vec.reserve(vec.size() + 1);
        vec.push_back(i);
        counter++;
    }
}

void push_nch(vector<int> &vec, int max_nch) {
    for (int i = max_nch; i > 0; i -= 2) {
        vec.reserve(vec.size() + 1);
        vec.insert(vec.begin(),i);
    }

}

//При передаче по значению создается копия объекта.
void sort_arr_value(array<int, 10> arr, const int NMax) {
    for (short i = 0; i < NMax - 1; ++i) {
        for (short j = i + 1; j < NMax; ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
    print_arr(arr, NMax);
}

//При передаче по ссылке используется ссылка на оригинальный объект.
void sort_arr_link(array<int, 10> &arr, const int NMax) {
    for (short i = 0; i < NMax - 1; ++i) {
        for (short j = i + 1; j < NMax; ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

//При передаче по указателю передается адрес объекта.(нет копирования, как в ссылке)
void sort_arr_pointer(array<int, 10> *arr, const int NMax) {
    for (short i = 0; i < NMax - 1; ++i) {
        for (short j = i + 1; j < NMax; ++j) {
            if ((*arr)[i] > (*arr)[j]) {
                swap((*arr)[i], (*arr)[j]);
            }
        }
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    //Пункт 1
    bool key = true;
    int number;
    int size_vector;
    int counter_ch = 0;
    int counter_nch = 0;
    int max_nch = 0;

    vector<int> vec = { 0,0,0 };

    while (key) {
        int choice_func = 0;
        cout << "Выберите номер функции: ";
        cin >> choice_func;
        switch (choice_func) {
        case (0):
            key = 0;
            cout << "Выход" << endl;
            break;

        case (1):
            cout << "Просмотр массива:" << endl;
            print_vector(vec);
            break;

        case (2):
            cout << "Добавить элемент в начало: ";
            cin >> number;
            vec.reserve(vec.size() + 1);
            vec.insert(vec.begin(), number);
            break;

        case (3):
            cout << "Добавить элемент в конец: ";
            cin >> number;
            vec.reserve(vec.size() + 1);
            vec.push_back(number);
            break;

        case (4):
            cout << "Очистка всего массива" << endl;
            vec.clear();
            break;

        case (5):
            cout << "Поиск элемента в массиве." << endl;
            cout << "Ввелите элемент:";
            cin >> number;
            find_element_in_arr(vec,number);
            break;
        case (6):
            cout << "Задание варианта.(5 сложное)" << endl;
            print_vector(vec);
            cout << "Введите K:";
            cin >> number;
            if (K_check(number,counter_ch,counter_nch, max_nch)) {
                push_ch(vec, counter_ch);
                push_nch(vec, max_nch);
                print_vector(vec);
            }
            else {
                doublecate(vec);
                print_vector(vec);
            }
            break;
        default:
            cout << "Число вне диапазона" << endl;
        }
    }

    //Пункт 2
    const int NMax = 10;
    array<int, NMax> arr;
    random_device rd;
    uniform_int_distribution<int> dist(-10, 10);

    //Значение
    for (int i = 0; i < NMax; i++) {
        arr[i] = dist(rd);
    }
    sort_arr_value(arr, NMax);

    //Ссылка
    for (int i = 0; i < NMax; i++) {
        arr[i] = dist(rd);
    }
    sort_arr_link(arr, NMax);

    cout << endl;
    print_arr(arr, NMax);

    //Указатель
    for (int i = 0; i < NMax; i++) {
        arr[i] = dist(rd);
    }
    sort_arr_pointer(&arr, NMax);

    cout << endl;
    print_arr(arr, NMax);

    // Пункт 3
    /*
    1. В 1 пункте выбрал std::vector, потому что std::array это статичный массив.
    2. Выбра нет, т.к. нецелесообразно использовать ститический массив в задаче, где постоянно меняется размер массива.
    3. Т.к. std::vector может выполнять функции статичного массива.
    */
    return 0;
}

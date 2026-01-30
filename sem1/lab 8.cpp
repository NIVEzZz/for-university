#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct People {
    int age;
    string name;
    People* best_friend;
};

void ADD_BF(People* man, People bf) {
    People* p = &bf;
    p->best_friend = man->best_friend;
    man->best_friend = p;
}

People* MAKE(string name, int age, People* bf) {
    People* p = new People;
    p->name = name;
    p->age = age;
    p->best_friend = bf;
    return p;
}

People* MAKE(string name, int age) {
    People* p = new People;
    p->name = name;
    p->age = age;
    p->best_friend = nullptr;
    return p;
}

void PRINT(People man) {
    cout << man.name << " " << man.age << " ";
    if (man.best_friend != nullptr) {
        People* bf = man.best_friend;
        cout << bf->name << endl;
    }
    else {
        cout << "Нет ЛП'шки" << endl;
    }
}

void PRINT_JOURNAL(vector<People> journal) {
    for (int i = 0; i < size(journal); ++i) {
        PRINT(journal[i]);
    }
}

void PRINT_ELEMENT(vector<People> journal, int index) {
    PRINT(journal[index-1]);
}



int main() {

    setlocale(LC_ALL, "Russian");
    People tom{ 12, "Том", nullptr};//1
    People nika{ 9, "Ника", &tom};//2
    People vasya{ 16, "Вася", nullptr };//3
    People petya{ 5, "Петя", nullptr };//4
    People dasha{ 27, "Даша", nullptr };//5
    People angelina{ 35, "Ангелина", nullptr };//6
    People miroslava{ 15, "Мирослава", nullptr };//7
    People dima{ 41, "Дима", nullptr };//8
    vector<People> journal = {
        tom,
        nika,
        vasya,
        petya,
        dasha,
        angelina,
        miroslava,
        dima
    };
    ADD_BF(&tom, dima);
    bool key = true;
    int element;
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
            cout << "Вывод элемента:";
            cin >> element;
            PRINT_ELEMENT(journal, element);
            break;
        case (8):
            PRINT_JOURNAL(journal);
            break;
        default:
            cout << "Число вне диапазона" << endl;
        }
    }
    return 0;
}
//PRINT(journal[0]);
//PRINT(*(MAKE("я", 52, "Эщкере")));

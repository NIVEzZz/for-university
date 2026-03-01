#include <iostream>
#include "Product.hpp"
#include <forward_list>
#include <list>

int main() {

    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "Тесты" << std::endl;;
        std::cout << std::endl;
        mt::Product test1("A", "Описание1", 100, 50, "Адрес1", { {"а",5.0},{"б",5.0},{"в",5.0}, {"а",5.0} });
        test1.print();
        std::cout << std::endl;
        mt::Product test2("Б", "Описание2", 100, 30, "Адрес2", { {"а",5.0},{"м",5.0},{"н",5.0} });
        test2.print();
        std::cout << std::endl;
        mt::Product ans1 = test1 + test2;
        ans1.print();
        std::cout << std::endl;
       // mt::Product ans2 = test1 - test2;
       // ans2.print();
        std::cout << std::endl;
        //test1 -= test2;
        test1.print();
        std::cout << std::endl;
        lib::Ingredient a { "ааа",100 };
        a.print();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

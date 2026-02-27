#include <iostream>
#include "Product.hpp"
#include <algorithm>

int main() {

    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "Тесты" << std::endl;

        vec v = { "а","б","а", "в" };
        std::sort(v.begin(), v.end());
        auto last = std::unique(v.begin(), v.end());
        v.erase(last, v.end());
        print_vector(v);

        std::cout << std::endl;
        mt::Product test1("A", "Описание1", 100, 50, "Адрес1", { "а","б","в", "а"});
        test1.print();
        std::cout << std::endl;
        mt::Product test2("Б", "Описание2", 100, 30, "Адрес2", { "а","м","н" });
        test2.print();
        std::cout << std::endl;
        mt::Product ans1 = test1 + test2;
        ans1.print();
        std::cout << std::endl;
        mt::Product ans2 = test2 + test1;
        ans2.print();
        std::cout << std::endl;
        mt::Product ans3 = test1 - test2;
        ans3.print();
        std::cout << std::endl;
        test1 -= test2;
        test1.print();
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

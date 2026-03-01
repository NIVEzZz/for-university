#include <iostream>
#include "..\lib\Commission.hpp"

void otsenka_labi() {
    std::cout << "\n=== Оценка лабы ===" << std::endl;
    std::cout << "\033[1mИнтерес: 9/10.\033[0m" << std::endl;
    std::cout << "\033[3m" << "Было интересно работать с относительно большим проектом.По сути 1 лаба с 3 оценками, что - то новенькое" << "\033[0m" << std::endl;
    std::cout << "\033[1mНаполненность: 8/10.\033[0m" << std::endl;
    std::cout << "\033[3m" << "Лаба учит взаимодействию со структуами и классами(Product в котром помимо 'стандартных' переменных есть std::vector<Ingredient>). \nНу и подключению своей библиотеки(было несложно, мб с CMake сложнее было бы)" << "\033[0m" << std::endl;
    std::cout << "\033[1mСложность: 8/10.\033[0m" << std::endl;
    std::cout << "\033[3m" << "Суммарно большой объем лабы, достаточно сложное переопределение операторов" << "\033[0m" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "=== Создание товаров с ингредиентами ===" << std::endl;
        std::vector<Ingredient> comp1 = { {"мука", 2.0}, {"яйца", 3.0}, {"сахар", 1.5}, {"мука", 12.0} };
        std::vector<Ingredient> comp2 = { {"мука", 1.0}, {"молоко", 2.0}, {"дрожжи", 0.5} };

        mt::Product product1("Хлеб", "Свежий хлеб", 50.0, 5, "Пекарня №1", comp1);
        mt::Product product2("Булочка", "Сдобная булочка", 30.0, 3, "Пекарня №2", comp2);

        product1.print();
        std::cout << std::endl;
        product2.print();
        std::cout << std::endl;

        mt::Product ans1 = product1 + product2;
        ans1.print();
        std::cout << std::endl;

        mt::Product ans2 = product2 + product1;
        ans2.print();
        std::cout << std::endl;

        mt::Product ans3 = product1 - product2;
        ans3.print();
        std::cout << std::endl;

        product1 -= product2;
        product1.print();
        std::cout << std::endl;

        // Демонстрация работы Commission
        std::vector<std::string> forbidden = {"консервант Т1000" };
        mt::Commission commission("г. Калининград, ул. Проверочка, д.1", forbidden, 2);
        commission.print();

        std::cout << "\n=== Проверка товаров ===" << std::endl;
        std::cout << "product1 легален? " << (commission.check_product(product1) ? "да" : "нет") << std::endl;
        std::cout << "product2 легален? " << (commission.check_product(product2) ? "да" : "нет") << std::endl;
        otsenka_labi();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

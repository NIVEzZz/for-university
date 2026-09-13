#include <iostream>
#include <vector>

void radix_sort(std::vector<int>& data) {

    int max_number = data[0];
    for (short i = 1; i < data.size(); ++i) {
        if (data[i] > max_number) {
            max_number = data[i];
        }
    }
    // place_value - разряд
    for (short place_value = 1; max_number / place_value > 0; place_value *= 10) {
        std::vector<int> sort_arr(data.size());

        int counter_of_digits[10] = {0};
        for (short i = 0; i < data.size(); ++i) {
            short digit = (data[i] / place_value) % 10;
            counter_of_digits[digit]++;
        }
        // элементы массива хранят (индекс после максимальный индекс цифры в sort_arr / индекс после последнего элемента с i-ой цифрой)
        for (short i = 1; i < 10; ++i) {
            counter_of_digits[i] += counter_of_digits[i - 1];
        }
        // цикл в обратную сторону, т.к. реализована Устойчивая (стабильная) сортировка — сортировка, которая не меняет порядок одинаковых по сортируемому признаку элементов
        for (short i = data.size() - 1; i >= 0; --i) {
            short digit = (data[i] / place_value) % 10;

            sort_arr[counter_of_digits[digit] - 1] = data[i];
            counter_of_digits[digit]--;
        }

        for (short i = 0; i < data.size(); ++i) {
            data[i] = sort_arr[i];
        }
    }
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4 };
    for (int number : data) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    radix_sort(data);
    for (int number : data) {
        std::cout << number << " ";
    }
    return 0;
}

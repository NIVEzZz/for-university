#include <iostream>
#include <vector>

void selection_sort(std::vector<int>& data) {
    for (short i = 0; i < data.size() - 1; ++i) {
        short min_index = i;

        for (short j = i + 1; j < data.size(); ++j) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
        }

        std::swap(data[i], data[min_index]);
    }
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4 };
    for (int number : data) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    selection_sort(data);
    for (int number : data) {
        std::cout << number << " ";
    }
    return 0;
}

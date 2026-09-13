#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& data) {
    for (short i = 1; i < data.size(); ++i) {
        int x = data[i];
        short j = i-1;

        //перемещение элементов (паровозиком)
        while (j >= 0 && data[j] > x) {
            data[j+1] = data[j];
            j--;
        }

        data[j+1] = x;
    }
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4 };
    for (int number : data) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    insertion_sort(data);
    for (int number : data) {
        std::cout << number << " ";
    }

    return 0;
}

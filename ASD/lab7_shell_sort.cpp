#include <iostream>
#include <vector>

void shell_sort(std::vector<int>& data) {
    for (short d = data.size() / 2; d != 0; d /= 2) {
        //как в insertion_sort, только нужно поменять 1 на d
        for (short i = d; i < data.size(); ++i) {
            int x = data[i];
            short j = i-d;

            //перемещение элементов (паровозиком)
            while (j >= 0 && data[j] > x) {
                data[j+d] = data[j];
                j -= d;
            }
            data[j+d] = x;
        }
    }
}

int main() {
    std::vector<int> data = { 6, 5, 3, 1, 8, 7, 2, 4 };
    for (int number : data) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    shell_sort(data);
    for (int number : data) {
        std::cout << number << " ";
    }
    return 0;
}
